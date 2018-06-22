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


//self made
#include "printer.h"

int analyze_ICMP(u_char *data,int size){
	
	u_char *ptr;
	int lest;

	struct icmp *icmp;

	if(lest<sizeof(struct icmp)){
		fprintf(stderr, "lest(%d)<sizeof(struct icmp)\n",lest );

		return -1;

	}

	icmp=(struct icmp *)ptr;
	ptr+=sizeof(struct icmp);
	lest-=sizeof(struct icmp);

	print_ICMP(icmp,stdout);

	return 0;
}


int analyze_Arp(u_char *data,int size){

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

    print_Arp(arp,stdout);

    return 0;

}


int analyze_Packet(u_char *data,int size){
	
	u_char *ptr;
	int lest;

	struct ether_header *eh;

	ptr=data;
	lest=size;

	fprintf(stderr,"lest:%d\n",lest);
	fprintf(stderr,"sizeof(struct ether_header)%d\n",sizeof(struct ether_header));

	if(lest<sizeof(struct ether_header)){
		fprintf(stderr, "lest(%d)<sizeof(struct ether_header)\n",lest );
		return(-1);

	}

	eh=(struct ether_header *)ptr;
	ptr+=sizeof(struct ether_header);
	lest-=sizeof(struct ether_header);



	if(ntohs(eh->ether_type)==ETHERTYPE_ARP){
		fprintf(stderr, "packet[%dbytes]\n", size);
		print_EtherHeader(eh,stdout);
		printf("debug\n");

		analyze_Arp(ptr,lest);

		printf("debug pritn arp end\n");

	}else if(ntohs(eh->ether_type)==ETHERTYPE_IP){
		//analyze IP
	}

	return 0;


}

int analyze_IP(u_char *data,int size){

	
}