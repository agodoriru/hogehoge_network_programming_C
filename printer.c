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

int print_ICMP(struct icmp *icmp,FILE *fp){
	static char *icmp_type[]={

		"Echo Reply",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
		"hoge",//
	};

	fprintf(fp, "icmp-------------------------------------\n");
	fprintf(fp, "icmp_type=%u",icmp -> icmp_type);

	if(icmp->icmp_type<=18){
		fprintf(fp, "%s\n",icmp_type[icmp->icmp_type]);
	}else{
		fprintf(fp, "undifined\n");
	}

	fprintf(fp, "icmp_code=%u\n",icmp->icmp_code);
	// fprintf(fp, "icmp_seq=%u\n",ntohs(icmp->icmp_cksum) );



}