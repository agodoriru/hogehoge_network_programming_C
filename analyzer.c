#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <asm/types.h>
#include <sys/types.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h> 
#include <linux/if_arcnet.h> 
#include <linux/version.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <signal.h>
#include <net/ethernet.h>
#include <linux/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <netinet/if_ether.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>


//self made
#include "printer.h"

int analyze_ICMP(u_char *data,int size) {

	u_char *ptr;
	int lest;
	struct icmp *icmp;

	ptr = data;
	lest = size;

	if(lest < sizeof(struct icmp)) {
		fprintf(stderr, "lest(%d)<sizeof(struct icmp)\n", lest);
		return (-1);
	}

	icmp = (struct icmp *)ptr;
	ptr += sizeof(struct icmp);
	lest -= sizeof(struct icmp);

	print_ICMP(icmp, stdout);

	return 0;
}

int analyze_TCP(u_char *data,int size){

	u_char *ptr;
    int lest;

    struct tcphdr *tcphdr;

    ptr=data;
    lest=size;

    if(lest<sizeof(struct tcphdr)){
        fprintf(stderr,"lest(%d)<sizeof(struct tcphdr)\n",lest);
        return (-1);
    }
    
    tcphdr=(struct tcphdr *)ptr;
    ptr+=sizeof(struct tcphdr);
    lest-=sizeof(struct tcphdr);

    print_TCP(tcphdr,stdout);

    return 0;
}

int analyze_UDP(u_char *data, int size) {

	u_char *ptr;
	int lest;

	struct udphdr *udphdr;

	ptr = data;
	lest = size;

	if(lest < sizeof(struct udphdr)) {
		fprintf(stderr, "lest(%d) < sizeof(struct udphdr)\n", lest);
		return (-1);
	}

	udphdr = (struct udphdr *)ptr;

	ptr += sizeof(struct udphdr);
	lest -= sizeof(struct udphdr);

	print_UDP(udphdr, stdout);

	return 0;
}

int analyze_IP(u_char *data, int size){

	u_char *ptr;
	int lest;

	struct iphdr *iphdr;

	u_char *option;
	int oplen;

	ptr = data;
	lest = size;

	if(lest<sizeof(struct iphdr)) {
		fprintf(stderr, "error\n");
		return (-1);
	}
	
	iphdr = (struct iphdr*)ptr;
	ptr += sizeof(struct iphdr);
	lest -= sizeof(struct iphdr);

	oplen = iphdr->ihl*4-sizeof(struct iphdr);

	if(oplen>0) {
		if(oplen>=1500) {
			fprintf(stderr, "IP oplen:%d\n",oplen);
			return (-1);
		}

		option = ptr;
		ptr += oplen;
		lest -= oplen;

	}

	// if(IP_checksum()){
	// 	fprintf(stderr, "bad checksum\n");
	// 	return (-1);
	// }

	print_IP_header(iphdr, option, oplen, stdout);

	if(iphdr->protocol==IPPROTO_ICMP){
		analyze_ICMP(ptr, lest);
	}else if(iphdr->protocol==IPPROTO_TCP){
		analyze_TCP(ptr, lest);
	}else if(iphdr->protocol==IPPROTO_UDP){
		analyze_UDP(ptr, lest);
	}

	return 0;
}


int analyze_ARP(u_char *data,int size){

    u_char *ptr;
    int lest;

    struct ether_arp *arp;

    ptr=data;
    lest=size;

    if(lest<sizeof(struct ether_arp)){
        fprintf(stderr,"lest(%d)<sizeof(struct ether_header)\n",lest);
        return (-1);
    }

    arp=(struct ether_arp *)ptr;
    ptr+=sizeof(struct ether_arp);
    lest-=sizeof(struct ether_arp);

    print_ARP(arp,stdout);

    return 0;

}

int analayze_IPv6(u_char *data,int size){
	// u_char *ptr;
	// int lest;
	return 0;
}

int analyze_Packet(u_char *data, int size){

	u_char *ptr;
	int lest;

	struct ether_header *eh;

	ptr=data;
	lest=size;

	if(lest < sizeof(struct ether_header)) {
		fprintf(stderr, "lest(%d)<sizeof(struct ether_header)\n", lest);
		return(-1);
	}

	eh = (struct ether_header *)ptr;
	ptr += sizeof(struct ether_header);
	lest -= sizeof(struct ether_header);

	if(ntohs(eh->ether_type) == ETHERTYPE_ARP) {
		fprintf(stdout, "packet[%dbytes]\n", size);
		print_EtherHeader(eh, stdout);
		analyze_ARP(ptr, lest);
	}else if(ntohs(eh->ether_type)==ETHERTYPE_IP){
		analyze_IP(ptr, lest);
	}else if(ntohs(eh->ether_type)==ETHERTYPE_IPV6){
		analayze_IPv6(ptr, lest);
	}

	return 0;
}

