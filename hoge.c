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


//prototype dec
void usage();
int init_descriptor(char *device_name);// 1:success 0:fail -1:error
// init_descriptor -> init_raw_socket



// main func
int	main(int argc, char *argv[])
{

	int soc;
	int size;
	char buff[255];


	//no command line argument
	if(argc<=1){
		usage();

		printf("%s\n",argv[0] );
		printf("%d\n",argc);
		
		return 1;
	}


	//error handring
	if(init_descriptor(argv[1])==-1){
		fprintf(stderr, "init_descriptor%s\n",argv[0] );

		// return -1;
	}




	while(1){

		if (read(soc,buff,sizeof(buff))<=0){
			perror("read");
		}else{
			printf("will do analyze packet\n");
			// AnalyzePacket(buff,size)
		}
	}



	// printf("%s\n", );
	printf("argv[0]:%s\n",argv[0] );
	printf("argc:%d\n",argc);



	close(soc);
	return 0;
}




void usage(){
	printf(" ---------------------------------------\n");
	printf("|will write  usage                      |\n");
	printf("|sudo ./a.out -> show usage             |\n");
	printf(" ---------------------------------------\n");
	printf("\n");
	printf("あとでprinter.hに移植\n");

}




int init_descriptor(char *device_name  /*  , type arp or ip or all*/){
	
	int soc;

	
	//init socket
	soc=socket(PF_INET, SOCK_RAW, htons(ETH_P_ALL));

	printf("%d\n",soc );



	//if error in initiating socket
	if(soc<0){
		perror("socket");
		return -1;
	}





	//bind to interface

	struct sockaddr_ll sll;
	struct ifreq ifreq;

	memset(&ifreq,0,sizeof(ifreq));
	strncpy(ifreq.ifr_name,device_name,sizeof(ifreq.ifr_name));

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

	if(bind(soc,(struct sockaddr *)&sll,sizeof(sll)<0)){
		perror("bind");
		close(soc);
		return -1;
	}


	return(soc);
}
