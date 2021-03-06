#include <linux/fs.h>
#include <asm/uaccess.h>	/* for put_user */
#include <linux/module.h>   // included for all kernel modules
#include <linux/kernel.h>   // included for KERN_INFO
#include <linux/init.h>     // included for __init and __exit macros
#include <linux/netfilter.h>
#include <linux/vmalloc.h>
#include <linux/types.h>    // included for __be32 type

#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/if_ether.h>//for ether header
#include <linux/cdev.h>//for cdev_init/add

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Richard Zhao");
MODULE_DESCRIPTION("Simple Packet Filter");

#define NIPQUAD(addr) \
  ((unsigned char *)&addr)[0], \
  ((unsigned char *)&addr)[1], \
  ((unsigned char *)&addr)[2], \
  ((unsigned char *)&addr)[3]  

static struct nf_hook_ops nfho;

/*  
 *  Prototypes - this would normally go in a .h file
 */
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "filter"	/* Dev name as it appears in /proc/devices   */
#define BUF_LEN 80		/* Max length of the message from the device */
#define DEV_NUM 1		/* Number of devices */

/* 
 * Global variables are declared as static, so are global within the file. 
 */

//static int Major;		/* Major number assigned to our device driver */
static int Device_Open = 0;	/* Is device open?  
				 * Used to prevent multiple access to device */
static char msg[BUF_LEN];	/* The msg the device will give when asked */
static char *msg_Ptr;	/*pointer used to transfer to userspace*/
struct sk_buff *skb_copy_pkt = NULL;//pointer for copy of skb_buffer
struct sk_buff *skb_copy_pktin = NULL;//pointer for copy of skb_buffer
int first = 0; //test use, for copy packet
struct sk_buff_head head;//head of the linked list
__be32 sip,dip;
int sample_rate=0;
static DECLARE_WAIT_QUEUE_HEAD(wq);//declear wait queue for block I/O

/*
 * Variables for creating chardev automatically
 */

static struct class *dev_class = NULL;//class pointer
struct cdev cdev;
static dev_t chardev;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

/*
 * Packet handling function.
 */
unsigned int hook_for_pkt(unsigned int hooknum,
                          struct sk_buff *skb,
                          const struct net_device *in,
                          const struct net_device *out,
                          int (*okfn)(struct sk_buff *)){
		BUG_ON(skb==NULL);
        struct iphdr *iph=ip_hdr(skb);
		unsigned int rand;//for random number generator
        sip = iph->saddr;     
        dip = iph->daddr;
		/*first should use a filter/hash to do sampling*/

		
		get_random_bytes(&rand, sizeof(int));
		if((rand%100) < sample_rate){
			/*if decide to sample, copy the skb_buffer*/
			skb_copy_pktin = skb_copy(skb, GFP_KERNEL);//gfp_t -> kernel memory allocation, in /usr/src/linux-3.12.13/include/linux/gfp.h
			BUG_ON(skb_copy_pktin==NULL);
			//put the packet into queue
			//skb_queue_tail(&head, skb_copy_pktin);
	        	//printk("copy packet, list len: %d,data: %p, %p\n", head.qlen, skb->mac_header, skb_transport_header(skb));
		}
		kfree_skb(skb);
        return NF_STOP;
}   

/*
 * This function is called when the module is loaded
 */
int init_module(void)
{
	int err;
	struct device *device;
	err = 0;
	device=NULL;

	//init the linked list
	skb_queue_head_init(&head);
	
	//register the hook
	/* remember which hook you specified */
    nfho.hook = hook_for_pkt;
    nfho.hooknum = 0;                       // NF_IP_PRE_ROUTING; 3 for NF_IP_LOCAL_OUT
    nfho.pf = PF_INET;                      // ipv4 protocols
    nfho.priority =NF_IP_PRI_FIRST;

    nf_register_hook(&nfho);

	if (alloc_chrdev_region(&chardev, 0, 3, DEVICE_NAME) < 0)
	{
		return -1;
	}
	printk(KERN_INFO "<Major, Minor>: <%d, %d>\n", MAJOR(chardev), MINOR(chardev));

	dev_class = class_create(THIS_MODULE, DEVICE_NAME);
	device = device_create(dev_class, NULL, chardev, NULL, DEVICE_NAME);
	
	cdev_init(&cdev, &fops);
	if (cdev_add(&cdev, chardev, 1) == -1){
		cleanup_module();
	}

	return SUCCESS;
}

/*
 * This function is called when the module is unloaded
 */
void cleanup_module(void)
{
	skb_copy_pkt = NULL;//preprocessing
	while(!skb_queue_empty(&head)){
		skb_copy_pkt = skb_dequeue_tail(&head);//if not empty, dequeue a socket with buffer
		kfree_skb(skb_copy_pkt);
	}
	printk(KERN_INFO "Cleaning up module.\n");
	printk(KERN_INFO "Unregister hook.\n");
	nf_unregister_hook(&nfho);

	/* 
	 * Unregister the device 
	 */
	cdev_del(&cdev);
	printk(KERN_INFO "Destroy device.\n");
	device_destroy(dev_class, chardev);
	printk(KERN_INFO "Clean device class.\n");
	if(dev_class)
		class_destroy(dev_class);
	printk(KERN_INFO "Unregister device number.\n");
	unregister_chrdev_region(chardev, 1);
	printk(KERN_INFO "Exit.\n");
}

/*
 * Methods
 */

/* 
 * Called when a process tries to open the device file, like
 * "cat /dev/mycharfile"
 */
static int device_open(struct inode *inode, struct file *file)
{
	static int counter = 0;

	if (Device_Open)
		return -EBUSY;

	Device_Open++;
	sprintf(msg, "%d times request, the most recent packet from: %d.%d.%d.%d; to: %d.%d.%d.%d\n", counter++, NIPQUAD(sip), NIPQUAD(dip));
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

/* 
 * Called when a process closes the device file.
 */
static int device_release(struct inode *inode, struct file *file)
{
	Device_Open--;		/* We're now ready for our next caller */

	/* 
	 * Decrement the usage count, or else once you opened the file, you'll
	 * never get get rid of the module. 
	 */
	module_put(THIS_MODULE);

	return 0;
}

/* 
 * Called when a process, which already opened the dev file, attempts to
 * read from it.
 */
static ssize_t device_read(struct file *filp,	/* see include/linux/fs.h   */
			   char *buffer,	/* buffer to fill with data */
			   size_t length,	/* length of the buffer     */
			   loff_t * offset)
{
	BUG_ON(buffer==NULL);
	/*
	 * Number of bytes actually written to the buffer 
	 */
	int bytes_read;
	unsigned int size = 0;
	bytes_read = 0;
	printk("init skb_copy_pkt pointer to NULL\n");
	skb_copy_pkt = NULL;//preprocessing
	msg_Ptr = NULL;

	if(!skb_queue_empty(&head)){
		skb_copy_pkt = skb_dequeue_tail(&head);//if not empty, dequeue a socket with buffer
	    printk("list len: %d\n", head.qlen);
		printk("Received read request from user space, now have skb data length: %d\n", skb_copy_pkt->len);
		size = skb_copy_pkt->len;
		msg_Ptr = eth_hdr(skb_copy_pkt);//mac_header;
	}
	else{
		size = 0; //NULL pointer, size must be 0
		return 0;//return EOF
	}
	
	BUG_ON(skb_copy_pkt==NULL);
	/* 
	 * Actually put the data into the buffer 
	 */
	while (length && size) {
		/* 
		 * The buffer is in the user data segment, not the kernel 
		 * segment so "*" assignment won't work.  We have to use 
		 * put_user which copies data from the kernel data segment to
		 * the user data segment. 
		 */
		put_user(*(msg_Ptr++), buffer++);

		length--;
		size--;
		bytes_read++;
	}
	//when finished, free the sk_buffer
	BUG_ON(skb_copy_pkt==NULL);
	kfree_skb(skb_copy_pkt);

	/* 
	 * Most read functions return the number of bytes put into the buffer
	 */
	return bytes_read;
}

/*  
 * Called when a process writes to dev file: echo "hi" > /dev/hello 
 */
static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	BUG_ON(buff==NULL);
	char input[len+1];
	//char *parsed;
	unsigned long count;
	int  coun, in=0;

	//init for input array
	for(coun=0;coun<len+1;coun++)
		input[coun]='\0';

	//get input from user
	count = copy_from_user(&input, buff, len);
	//printk(KERN_ALERT "Recived: %d, %s\n", len, input);
	
	if(!strncasecmp(input,"sample",6)){//compare first 6 bytes
		kstrtouint(&input[7], 10, &in);//go over 'sample '
		printk(KERN_ALERT "setting sample rate to: %d%\n", in);
		sample_rate=in;
	}
	return len - count;
}
