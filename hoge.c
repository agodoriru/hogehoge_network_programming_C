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

//self made
#include "analyzer.h"
#include "printer.h"
#include "interface_checker.h"

//prototype dec
int init_descriptor(char *network_interface_name);// 1:success 0:fail -1:error


// main func
int soc;
int	main(int argc, char *argv[])
{

	// int soc;
	int size=0;
	u_char buff[255];


	//no command line argument
	if(argc<=1){
		usage();		
		return 1;
	}
	

	// printf("no command line zone clear!\n");
	// printf("%s\n",argv[1]);
	
	if(strcmp(argv[1],"show")==0){

		// printf("in\n");

		interface_checker();
		return 0;
	}

	
	printf("clear\n");

	//error handring
	if(init_descriptor(argv[1])==-1){
		fprintf(stderr, "init_descriptor%s\n",argv[0] );

		return -1;
	}

	printf("initiating descriptor success!\n");


	printf("in while soc:%d\n",soc );
	printf("size:%d\n",read(soc,buff,sizeof(buff)));


	while(1){
		printf("\n");
		if ((size=read(soc,buff,sizeof(buff)))<=0){
			perror("read");
			printf("aaa\n");
			return -1;
		}else{
			printf("will do analyze packet\n");
			analyze_Packet(buff,size);
			printf("doing analyze packet\n");

		}
	}



	// printf("%s\n", );
	printf("argv[0]:%s\n",argv[0] );
	printf("argc:%d\n",argc);



	close(soc);
	return 0;
}

int init_descriptor(char *network_interface_name){
	
	int soc;

	
	//init socket
	soc=socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	printf("%d\n",soc );



	//if error in initiating socket
	if(soc<0){
		perror("socket");
		printf("initiating socket failed\n");
		return -1;
	}


	printf("initiating socket clear!\n");


	//bind to interface

	struct sockaddr_ll sll;
	struct ifreq ifreq;

	memset(&ifreq,0,sizeof(ifreq));
	strncpy(ifreq.ifr_name,network_interface_name,sizeof(ifreq.ifr_name));

	int interface_index=ioctl(soc,SIOCGIFINDEX,&ifreq);
	

	//if error in initiating socket
	if(interface_index<0){
		perror("ioctl");
		close(soc);
		return -1;
	}


	sll.sll_family=PF_PACKET;
	sll.sll_protocol=htons(ETH_P_ALL);
	sll.sll_ifindex=interface_index;

	if(bind(soc,(struct sockaddr *)&sll,sizeof(sll))<0){
		perror("bind");
		printf("bind to interface failed\n");
		close(soc);
		return -1;
	}

	printf("bind to interface clear!\n");

	printf("returned in init_descriptor soc:%u\n",soc );
	return(soc);
}


