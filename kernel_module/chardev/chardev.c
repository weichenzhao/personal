/*
 *  chardev.c: Creates a read-only char device that says how many times
 *  you've read from the dev file
 */

#include <linux/fs.h>
#include <asm/uaccess.h>	/* for put_user */
#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/netfilter.h>
#include <linux/vmalloc.h>
#include <linux/types.h>     // included for __be32 type

#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>

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
#define DEVICE_NAME "chardev"	/* Dev name as it appears in /proc/devices   */
#define BUF_LEN 80		/* Max length of the message from the device */
__be32 sip,dip;

/* 
 * Global variables are declared as static, so are global within the file. 
 */

static int Major;		/* Major number assigned to our device driver */
static int Device_Open = 0;	/* Is device open?  
				 * Used to prevent multiple access to device */
static char msg[BUF_LEN];	/* The msg the device will give when asked */
static char *msg_Ptr;	/*pointer used to transfer to userspace*/
struct sk_buff *skb_copy_pkt = NULL;//pointer for copy of skb_buffer

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
        struct iphdr *iph=ip_hdr(skb);
        struct sock *sk = skb->sk;
        sip = iph->saddr;     
        dip = iph->daddr;
		/*first should use a filter/hash to do sampling*/

		int first = 0;
		if (!first){
		/*if decide to sample, copy the skb_buffer*/
			skb_copy_pkt = skb_copy(skb, GFP_KERNEL);//gfp_t -> kernel memory allocation, in /usr/src/linux-3.12.13/include/linux/gfp.h
			first += 1;
		}
		//defination of skb_copy: struct sk_buff *skb_copy(const struct sk_buff *skb, gfp_t gfp_mask)
        //iph=(*skb).network_header;
        if(iph->protocol == IPPROTO_TCP)
                printk("TCP packet from: %d.%d.%d.%d; to: %d.%d.%d.%d\n", NIPQUAD(sip), NIPQUAD(dip));
        else if(iph->protocol == IPPROTO_ICMP)
                printk("ICMP packet from: %d.%d.%d.%d; to: %d.%d.%d.%d\n", NIPQUAD(sip), NIPQUAD(dip));
        else if(iph->protocol == IPPROTO_UDP)
                printk("UDP packet from: %d.%d.%d.%d; to: %d.%d.%d.%d\n", NIPQUAD(sip), NIPQUAD(dip));
        else
                printk("ICMP packet received %d, %d\n", skb->data - skb->head, skb->len);
        //printk("Hello packet! %d, %d\n", skb->data - skb->head, skb->len);
        return NF_ACCEPT;
}   

/*
 * This function is called when the module is loaded
 */
int init_module(void)
{

	/* remember which hook you specified */
        nfho.hook = hook_for_pkt;
        nfho.hooknum = 0;                       // NF_IP_PRE_ROUTING;
        nfho.pf = PF_INET;                      // ipv4 protocols
        nfho.priority =NF_IP_PRI_FIRST;

        nf_register_hook(&nfho);

        Major = register_chrdev(0, DEVICE_NAME, &fops);

	if (Major < 0) {
	  printk(KERN_ALERT "Registering char device failed with %d\n", Major);
	  return Major;
	}

	printk(KERN_INFO "I was assigned major number %d. To talk to\n", Major);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done.\n");

	return SUCCESS;
}

/*
 * This function is called when the module is unloaded
 */
void cleanup_module(void)
{
	/* 
	 * Unregister the device 
	 */
	printk(KERN_INFO "Cleaning up module.\n");
	nf_unregister_hook(&nfho);
	int ret=0;
	unregister_chrdev(Major, DEVICE_NAME);
	if (ret < 0)
		printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);
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
	//if(skb_copy_pkt != NULL){
		unsigned int size = skb_copy_pkt->data_len;
		msg_Ptr = skb_copy_pkt;
		//copy_to_user(buffer, skb_copy_pkt->data, size);
		//return size;
	//}
	//return simple_read_from_buffer(filp, size, offset, skb_copy_pkt, size);
	/*
	 * Number of bytes actually written to the buffer 
	 */
	int bytes_read = 0;

	
	/*
	 * If we're at the end of the message, 
	 * return 0 signifying end of file 
	 */
	if (*msg_Ptr == 0)
		return 0;

	/* 
	 * Actually put the data into the buffer 
	 */
	while (length && *msg_Ptr) {

		/* 
		 * The buffer is in the user data segment, not the kernel 
		 * segment so "*" assignment won't work.  We have to use 
		 * put_user which copies data from the kernel data segment to
		 * the user data segment. 
		 */
		put_user(*(msg_Ptr++), buffer++);

		length--;
		bytes_read++;
	}

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
	printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
	return -EINVAL;
}
