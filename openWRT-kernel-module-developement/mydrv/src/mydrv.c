//It is built on a Big Endian system

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/types.h>

#include <linux/udp.h>
#include <linux/ip.h>
#include <net/protocol.h>
#include <linux/if_ether.h>
#include <linux/net.h>
#include <linux/netfilter.h>
#include <linux/skbuff.h>
#include <net/ip.h>
#include <linux/netdevice.h>  
#include <linux/netfilter_ipv4.h>

#include <linux/sched.h>

static struct nf_hook_ops nfho;
unsigned char *payload;    // The pointer for the tcp payload.
char sourceAddr[20];
//char myAddr[20] = "192.168.10.154";
char destAddr[20];

unsigned int my_func(void *priv,
        struct sk_buff *skb,
        const struct nf_hook_state *state)
{   
    register struct iphdr *iph;
    register struct tcphdr *tcph;
    struct tls_hdr *tlsh;


    // check if it is TCP package here
    if(skb == 0)
        return NF_ACCEPT;
    iph = ip_hdr(skb);
    if(iph->protocol != IPPROTO_TCP)
        return NF_ACCEPT;
    
    tcph = tcp_hdr(skb);
    printk("TCP: [%u]-->[%u];\n", ntohs(tcph->source), ntohs(tcph->dest));

    return NF_ACCEPT;

}


static __init int mydrv_init(void)
{
        //printk("helloworld!\n");
    nfho.hook = my_func;
    nfho.pf = NFPROTO_IPV4;
    nfho.hooknum = NF_INET_FORWARD;
    nfho.priority = NF_IP_PRI_MANGLE;
    int ret = 0;
    struct net *n;
    for_each_net(n)
        ret += nf_register_net_hook(n, &nfho);

    printk("nf_register_hook returnd %d\n", ret);
    return 0;
}
 
static __exit void mydrv_exit(void)
{
struct net *n;
for_each_net(n)
    nf_unregister_net_hook(n, &nfho);
    printk("helloworld exit!\n");
}
 
module_init(mydrv_init);
module_exit(mydrv_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stone");
