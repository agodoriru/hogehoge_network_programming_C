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

char *MACaddress_int_to_str(u_char *hwaddr,char *buf,socklen_t size){
	snprintf(buf,size,"%02x:%02x:%02x:%02x:%02x:%02x",
		hwaddr[0],hwaddr[1],hwaddr[2],hwaddr[3],hwaddr[4],hwaddr[5]);
	return(buf);
}


int print_EtherHeader(struct ether_header *eh,FILE *fp){
	char buf[128];

	//show mac address distina & source
	fprintf(fp,"Ethernet_distination_host=%s\n",MACaddress_int_to_str(eh->ether_dhost,buf,sizeof(buf)));
	fprintf(fp,"Ethernet_source_host=%s\n",MACaddress_int_to_str(eh->ether_shost,buf,sizeof(buf)));

	//type
	fprintf(fp,"ether_type=%02X",ntohs(eh->ether_type));


	switch(ntohs(eh->ether_type)){
		case	ETH_P_IP:
			fprintf(fp,"(IP)\n");
			break;
		case	ETH_P_IPV6:
			fprintf(fp,"(IPv6)\n");
			break;
		case	ETH_P_ARP:
			fprintf(fp,"(ARP)\n");
			break;
		default:
			fprintf(fp,"(unknown)\n");
			break;
	}

	return(0);
}


void usage(){
	printf(" --------------------------------------------------------\n");
	printf("|hogehoge network capture\n");
	printf("|\n");
	printf("|warning !!! need sudo privileges to use !!!                     |\n");
	printf("|$ sudo ./a.out             |\n");
	printf("|-> show usage                      |\n");
	printf("|$ sudo ./hoge [network interface name]\n");
	printf("|-> show something                      |\n");
	printf("|will write  usage                      |\n");
	printf("|will write  usage                      |\n");
	printf("|will write  usage                      |\n");
	printf("|will write  usage                      |\n");
	printf("|will write  usage                      |\n");
	printf(" ---------------------------------------\n");
	printf(" --------------------------------------------------------\n");
	printf("\n");

}