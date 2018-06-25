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


int print_Arp(struct ether_arp *arp,FILE *fp){

    printf("debug in print arp\n");


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
    printf("hardware_type=%u\n",ntohs(arp->arp_hrd));
    printf("debug array made\n");

    char buff[256];
    fprintf(fp,"=arp=");
    printf("debug char made\n");


    fprintf(fp,"=======================================================\n");
    fprintf(fp,"====================arp================================\n");
    fprintf(fp,"=======================================================\n");
//    fprintf(fp,arp);
//    printf(ntohs(arp->arp_hrd));
    fprintf(fp,"debug\n");
    fprintf(fp,"hardware_type=%u:",ntohs(arp->arp_hrd));

    if((ntohs(arp->arp_hrd))<25){
        fprintf(fp,"%s\n",hardware_type[ntohs(arp->arp_hrd)]);
    }else{
        fprintf(fp,"undifined\n");
    }
    fprintf(fp,"debug\n");
    sleep(5);
    fprintf(fp,"=======================arp end============================");


    fprintf(fp, "arp-protocol:%u\n",ntohs(arp->arp_pro) );

    fprintf(fp, "arp-headware-length:%u\n",arp->arp_hln);
    fprintf(fp, "arp-protocol-length:%u\n",  arp->arp_pln);

    if((ntohs(arp->arp_op)<=20)){
        fprintf(fp, "arp-operation:%u\n",operation_code[ntohs(arp->arp_op)] );
    }else{
        fprintf(fp, "undifined\n");
    }




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

    fprintf(fp, "version:%u\n", iphdr->version);
    fprintf(fp, "header length:%u\n",iphdr->ihl);
    fprintf(fp, "type of service:%u\n",iphdr->tos);
   
    fprintf(fp, "packet total size:%u\n",iphdr->tot_len);
    
    fprintf(fp, "protocol:%u ",iphdr->protocol);

    if((iphdr->protocol)<=25){
        fprintf(fp, "%s\n",protocol[iphdr->protocol]);
    }else{
        fprintf(fp, "undifined\n");
    }

    sleep(5);
    fprintf(fp, "============IP info=======================\n");

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
        "Timestamp  タイムスタンプ",
        "Timestamp Reply",
        "Information Request",
        "Information Reply",
        "Address Mask Request",
        "Address Mask Reply",
		
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

char *MACaddress_int_to_str(u_char *hwaddr,char *buff,socklen_t size){
	snprintf(buff,size,"%02x:%02x:%02x:%02x:%02x:%02x",
		hwaddr[0],hwaddr[1],hwaddr[2],hwaddr[3],hwaddr[4],hwaddr[5]);
	return(buff);
}

int print_EtherHeader(struct ether_header *eh,FILE *fp)
{
    char buf[80];
    fprintf(fp,"ether_header----------------------------\n");

    fprintf(fp,"ether_distination_host=%s\n",MACaddress_int_to_str(eh->ether_dhost,buf,sizeof(buf)));
    fprintf(fp,"ether_source_host=%s\n",MACaddress_int_to_str(eh->ether_shost,buf,sizeof(buf)));

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

void get_time(FILE *fp){
    char date[1023];
    time_t t;
    t=time(NULL);
    char *now=ctime(&t);
    fprintf(stderr,now);
    return;
}
void usage(FILE *fp){
	fprintf(stderr,"                      =========================================================\n");
	fprintf(stderr,"                    ||                                                         ||\n");
	fprintf(stderr,"                    ||          hogehoge network capture                       ||\n");
	fprintf(stderr,"                    ||                                                         ||\n");
	fprintf(stderr,"                    ||      !!! warning need sudo privileges to use !!!        ||\n");
	fprintf(stderr,"                    ||                                                         ||\n");
	fprintf(stderr,"                    ||          $ sudo ./hoge [network interface name]         ||\n");
	fprintf(stderr,"                    ||          -> show something                              ||\n");
	fprintf(stderr,"                    ||                                                         ||\n");
	fprintf(stderr,"                    ||          $ sudo ./a.out                                 ||\n");
	fprintf(stderr,"                    ||          -> show usage                                  ||\n");
	fprintf(stderr,"                    ||                                                         ||\n");
	fprintf(stderr,"                      =========================================================\n");
	fprintf(stderr,"\n");

}