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
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <sys/time.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/if_ether.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip6.h>

//self made
#include "printer.h"
#include "analyzer.h"
#include "interface_checker.h"

int init_descriptor(char *network_interface_name,int promiscuous_flag);

int main(int argc,char *argv[]){
    int soc,size;
    u_char buff[4096];

    //no command line argument
    if(argc <= 1){
        usage(stdout);
        return 1;
    }

    printf("%s\n", argv[1]);

    if(strcmp(argv[1], "show")==0){
        printf("activate interface_checker\n");
        interface_checker();
        return 1;
    }

    if((soc=init_descriptor(argv[1], 0)) == -1) {
        fprintf(stderr, "init_descriptor:error:%s\n", argv[1]);
        return -1;
    }

    while(1){

        if((size = read(soc, buff, sizeof(buff))) <= 0) {
            perror("read");
        } else {
            if(size >= sizeof(struct ether_header)) {
                printf("=====================================================\n");
                get_time(stdout);
                printf("------------------------------------------------\n");
                print_EtherHeader((struct ether_header *)buff, stdout);
                printf("------------------------------------------------\n\n\n");
                analyze_Packet(buff, size);
                printf("--------------------------------------------------\n");
                printf("=====================================================\n");
            } else {
                fprintf(stderr, "read size(%d) < %ld\n", size, sizeof(struct ether_header));
            }
        }
    }

    close(soc);

    return(0);
}


int init_descriptor(char *network_interface_name,int promiscuous_flag){

    struct ifreq ifreq;
    struct sockaddr_ll sll;
    int soc;

    soc = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    memset(&ifreq, 0, sizeof(struct ifreq));
    strncpy(ifreq.ifr_name,network_interface_name, sizeof(ifreq.ifr_name)-1);

    int interface_index=ioctl(soc,SIOCGIFINDEX,&ifreq);
    //if error in initiating socket

    if(interface_index < 0) {
        perror("ioctl");
        close(soc);
        return (-1);
    }

    sll.sll_family = PF_PACKET;
    sll.sll_protocol = htons(ETH_P_ALL);
    sll.sll_ifindex = ifreq.ifr_ifindex;

    if(bind(soc, (struct sockaddr *)&sll, sizeof(sll)) < 0) {
        perror("bind");
        close(soc);
        return (-1);
    }

    if(promiscuous_flag) {
        if(ioctl(soc, SIOCGIFFLAGS, &ifreq) < 0) {
            perror("ioctl");
            close(soc);
            return (-1);
        }

        ifreq.ifr_flags = ifreq.ifr_flags|IFF_PROMISC;

        if(ioctl(soc, SIOCSIFFLAGS, &ifreq) < 0) {
            perror("ioctl");
            close(soc);
            return (-1);
        }
    }
    return(soc);
}
