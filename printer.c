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
#include <time.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/route.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <netinet/ether.h>
#include <netinet/tcp.h>

char *MACaddress_int_to_str(u_char *hwaddr,char *buff,socklen_t size){
	snprintf(buff,size,"%02x:%02x:%02x:%02x:%02x:%02x",
		hwaddr[0],hwaddr[1],hwaddr[2],hwaddr[3],hwaddr[4],hwaddr[5]);
	return(buff);
}

static char *ip_int_to_str(u_int32_t ip, char *buff, socklen_t size) {
	struct in_addr *addr;
	addr = (struct in_addr *)&ip;
	inet_ntop(AF_INET, addr, buff, size);
	return(buff);
}

static char *arp_ip_int_to_str(u_int8_t *ip, char *buff, socklen_t size) {
	snprintf(buff, size, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
	return(buff);
}

int print_ARP(struct ether_arp *arp,FILE *fp){

    static char *hardware_type[]={

        //====================================================================================
        //ref-url: https://www.iana.org/assignments/arp-parameters/arp-parameters.xhtml#arp-parameters-2
        //====================================================================================

        "Reserved",
        "Ethernet (10Mb)",
        "Experimental Ethernet (3Mb)",
        "Amateur Radio AX.25",
        "Proteon ProNET Token Ring",
        "Chaos",
        "IEEE 802 Networks",
        "ARCNET",
        "Hyperchannel",
        "Lanstar",
        "Autonet Short Address",
        "LocalTalk",
        "LocalNet (IBM PCNet or SYTEK LocalNET)",
        "Ultra link",
        "MDS",
        "Frame Relay",
        "Asynchronous Transmission Mode (ATM)",
        "HDLC",
        "Fibre Channel",
        "Asynchronous Transmission Mode (ATM)",
        "Serial Line",
        "Asynchronous Transmission Mode (ATM)",
        "MIL-STD-188-220",
        "Metricom",
        "IEEE 1394.1995",
        "MAPOS",
        "Twinaxial",
        "EUI-64",
        "HIPARP",
        "IP and ARP over ISO 7816-3",
        "ARPSec",
        "IPsec tunnel",
        "nfiniBand (TM)",
        "TIA-102 Project 25 Common Air Interface (CAI)",
        "Wiegand Interface",
        "Pure IP",
        "HW_EXP1",
        "HFI",
        "Unassigned",

    };

    static char *operation_code[]={

        //====================================================================================
        //ref-url:https://www.iana.org/assignments/arp-parameters/arp-parameters.xhtml
        //====================================================================================

        "Undefine",
        "REQUEST",
        "REPLY",
        "request Reverse",
        "reply Reverse",
        "DRARP-Request",
        "DRARP-Reply",
        "DRARP-Error",
        "InARP-Request",
        "InARP-Reply",
        "ARP-NAK",
        "MARS-Request",
        "MARS-Multi",
        "MARS-MServ",
        "MARS-Join",
        "MARS-Leave",
        "MARS-NAK",
        "MARS-Unserv",
        "MARS-SJoin",
        "MARS-SLeave",
        "MARS-Grouplist-Request",
        "MARS-Grouplist-Reply",
        "MARS-Redirect-Map",
        "MAPOS-UNARP",
        "OP_EXP1",
        "OP_EXP2",
        "Unassigned",
        "Reserved",


    };
    fprintf(fp, "============================ARP info==============================\n");
    
    char buff[256];

    fprintf(fp,"hardware_type=%u ", ntohs(arp->arp_hrd));

    if((ntohs(arp->arp_hrd)) < 25) {
        fprintf(fp, "%s\n", hardware_type[ntohs(arp->arp_hrd)]);
    } else {
        fprintf(fp, "undifined\n");
    }
    
    fprintf(fp, "arp-protocol:%u\n", ntohs(arp->arp_pro) );
    fprintf(fp, "arp-headware-length:%u\n", arp->arp_hln);
    fprintf(fp, "arp-protocol-length:%u\n", arp->arp_pln);

    if((ntohs(arp->arp_op) <= 20)){
        fprintf(fp, "arp-operation:%s\n", operation_code[ntohs(arp->arp_op)]);
    } else {
        fprintf(fp, "undifined\n");
    }

    fprintf(fp, "source mac address:%s\n", MACaddress_int_to_str(arp->arp_sha, buff, sizeof(buff)));
    fprintf(fp, "dest mac address:%s\n", MACaddress_int_to_str(arp->arp_tha, buff, sizeof(buff)));
    fprintf(fp, "sourse address:%s\n", arp_ip_int_to_str(arp->arp_spa, buff, sizeof(buff)));
    fprintf(fp, "dest address:%s\n", arp_ip_int_to_str(arp->arp_tpa, buff, sizeof(buff)));
    fprintf(fp, "============================ARP info end==============================\n");

	return 0;
}

int print_TCP(struct tcphdr *tcphdr,FILE *fp){
    fprintf(fp, "============TCP info=======================\n");
    fprintf(fp, "source port:%u\n", ntohs(tcphdr->source));
    fprintf(fp, "target port:%u\n", ntohs(tcphdr->dest));
    fprintf(fp, "sequence number:%u\n", ntohl(tcphdr->seq));
    fprintf(fp, "acknowledgement number:%u\n", ntohl(tcphdr->ack_seq));
    fprintf(fp, "reserved 1:%u\n", tcphdr->res1);
    fprintf(fp, "data offset:%u\n", tcphdr->doff);
    fprintf(fp, "urg bit:%u\n", tcphdr->urg);
    fprintf(fp, "ack bit:%u\n", tcphdr->ack);
    fprintf(fp, "psh bit:%u\n", tcphdr->psh);
    fprintf(fp, "rst bit:%u\n", tcphdr->rst);
    fprintf(fp, "syn bit:%u\n", tcphdr->syn);
    fprintf(fp, "fin bit:%u\n", tcphdr->fin);
    fprintf(fp, "window:%u\n", ntohs(tcphdr->window));
    fprintf(fp, "check sum:%u\n", ntohs(tcphdr->check));
    fprintf(fp, "urgent pointer:%u\n", ntohs(tcphdr->urg_ptr));
    fprintf(fp, "reserved 2:%u\n", tcphdr->res2);
    fprintf(fp, "============TCP info end=======================\n");

	return 0;
}


int print_IP_header(struct iphdr *iphdr,FILE *fp){
    fprintf(fp, "============IP info=======================\n");
    static char *protocol[]={
        "undifined",
        "ICMP",
        "IGMP",
        "undifined",
        "IP",
        "undifined",
        "TCP",
        "CBT",
        "EGP",
        "IGP",
        "undifined",
        "undifined",
        "undifined",
        "undifined",
        "undifined",
        "undifined",
        "undifined",
        "UDP",

    };
    char buff[256];

    fprintf(fp, "version:%u\n", iphdr->version);
    fprintf(fp, "header length:%u\n", iphdr->ihl);
    fprintf(fp, "type of service:%u\n", iphdr->tos);
    fprintf(fp, "packet total size:%u\n", iphdr->tot_len);
    fprintf(fp, "protocol:%u ", iphdr->protocol);

    if((iphdr->protocol) <= 25) {
        fprintf(fp, "%s\n", protocol[iphdr->protocol]);
    } else {
        fprintf(fp, "undifined\n");
    }
    fprintf(fp, "sourse address:%s\n", ip_int_to_str(iphdr->saddr, buff, sizeof(buff)));
    fprintf(fp, "dest address:%s\n", ip_int_to_str(iphdr->daddr, buff, sizeof(buff)));
    fprintf(fp, "============IP info end=======================\n");

	return 0;
}

int print_ICMP(struct icmp *icmp,FILE *fp){
	static char *icmp_type[]={

		"Echo Reply",//
        "undefined",
        "undifined",
        "Destination Unreachable",
        "Source Quench",
        "Redirect",
        "undifined",
        "undifined",
        "Echo Request",
        "Router Advertisement",
        "Router Solicitation",
        "Time Exceeded",
        "Parameter Proble",
        "Timestamp",
        "Timestamp Reply",
        "Information Request",
        "Information Reply",
        "Address Mask Request",
        "Address Mask Reply",
	};

	fprintf(fp, "===============ICMP info=================\n");
	fprintf(fp, "icmp type=%u:", icmp -> icmp_type);

	if(icmp->icmp_type<=18){
		fprintf(fp, "%s\n", icmp_type[icmp->icmp_type]);
	}else{
		fprintf(fp, "undifined\n");
	}

	fprintf(fp, "icmp code=%u\n", icmp->icmp_code);
	fprintf(fp, "icmp_seq=%u\n", ntohs(icmp->icmp_cksum));
    fprintf(fp, "===============ICMP info end=================\n");

	return 0;
}


int print_EtherHeader(struct ether_header *eh, FILE *fp)
{
    char buf[2048];
    fprintf(fp,"ether_header----------------------------\n");
    fprintf(fp,"ether_distination_host=%s\n", MACaddress_int_to_str(eh->ether_dhost, buf, sizeof(buf)));
    fprintf(fp,"ether_source_host=%s\n", MACaddress_int_to_str(eh->ether_shost,buf, sizeof(buf)));
    fprintf(fp,"ether_type=%02X",ntohs(eh->ether_type));

    switch(ntohs(eh->ether_type)){
        case	ETH_P_IP:
            fprintf(fp, "(IP)\n");
            break;
        case	ETH_P_IPV6:
            fprintf(fp, "(IPv6)\n");
            break;
        case	ETH_P_ARP:
            fprintf(fp, "(ARP)\n");
            break;
        default:
            fprintf(fp, "(unknown)\n");
            break;
    }
    return(0);
}

void get_time(FILE *fp){
    char date[4096];
    time_t t = time(NULL);
	strftime(date, sizeof(date), "%Y/%M/%d %a %H:%M:%S", localtime(&t));
	printf("%s\n", date);
    return;
}

void usage(FILE *fp){
	fprintf(stderr,"  =========================================================\n");
	fprintf(stderr,"||                                                         ||\n");
	fprintf(stderr,"||          hogehoge network capture                       ||\n");
	fprintf(stderr,"||                                                         ||\n");
	fprintf(stderr,"||      !!! warning need sudo privileges to use !!!        ||\n");
	fprintf(stderr,"||                                                         ||\n");
	fprintf(stderr,"||          $ sudo ./main [network interface name]         ||\n");
	fprintf(stderr,"||          -> show something                              ||\n");
	fprintf(stderr,"||                                                         ||\n");
	fprintf(stderr,"||          $ sudo ./main                                  ||\n");
	fprintf(stderr,"||          -> show usage                                  ||\n");
	fprintf(stderr,"||                                                         ||\n");
	fprintf(stderr,"  =========================================================\n");

}
