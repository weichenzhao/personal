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

unsigned int hook_for_pkt(unsigned int hooknum,
		          struct sk_buff *skb,
		          const struct net_device *in,
		          const struct net_device *out,
		          int (*okfn)(struct sk_buff *)){
	struct iphdr *iph=ip_hdr(skb);
	struct sock *sk = skb->sk;
	__be32 sip,dip;
	sip = iph->saddr;  
	dip = iph->daddr;

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

static int init_filter_if()
{
	printk(KERN_INFO "initializing the hooks!\n");

	/* remember which hook you specified */
	nfho.hook = hook_for_pkt;
	nfho.hooknum = 0;			// NF_IP_PRE_ROUTING;
	nfho.pf = PF_INET;			// ipv4 protocols
	nfho.priority =NF_IP_PRI_FIRST;

	nf_register_hook(&nfho);

	return 0;
}

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello world!\n");
    init_filter_if();
    return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit hello_cleanup(void)
{
  nf_unregister_hook(&nfho);
  printk(KERN_INFO "Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

