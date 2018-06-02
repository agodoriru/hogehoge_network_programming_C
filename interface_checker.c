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

void interface_checker(){

	const int IF_NUM_MAX=100;

	struct ifreq ifr[IF_NUM_MAX];
 	struct ifconf ifc;
 	int soc;
 	int network_interface_numbers;


	soc=socket(AF_INET,SOCK_STREAM,0);


	//wakarann

	ifc.ifc_len=sizeof(ifr);

	ifc.ifc_ifcu.ifcu_buf=(void *)ifr;

	ioctl(soc, SIOCGIFCONF, &ifc);

	network_interface_numbers=ifc.ifc_len/sizeof(struct ifreq);

	// printf("ifc.ifc_len:%d\n",ifc.ifc_len);
	// printf("ifc.ifc_ifcu.ifcu_buf:%d\n",ifc.ifc_ifcu);
	// printf("nifs=ifc.ifc_len/sizeof(struct ifreq):%d\n",sizeof(struct ifreq));

	
	int i;
	for(i=0;i<network_interface_numbers;i++) {
		printf("%s\n",ifr[i].ifr_name);
	}


	close(soc);

}