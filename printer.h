int print_EtherHeader(struct ether_header *eh,FILE *fp);
char *MACaddress_int_to_str(u_char *hwaddr,char *buf,socklen_t size);
int print_Arp(struct ether_arp *arp,FILE *fp);
int print_ICMP(struct icmp *icmp,FILE *fp);
int print_IP_header(struct iphdr *iphdr,FILE *fp);
void get_time();
void usage();
