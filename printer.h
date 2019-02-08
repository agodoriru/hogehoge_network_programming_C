int print_EtherHeader(struct ether_header *eh,FILE *fp);
char *MACaddress_int_to_str(u_char *hwaddr,char *buf,socklen_t size);
int print_ARP(struct ether_arp *arp,FILE *fp);
int print_ICMP(struct icmp *icmp,FILE *fp);
int print_IP_header(struct iphdr *iphdr, u_char *option, int oplen, FILE *fp);
int print_TCP(struct tcphdr *tcphdr,FILE *fp);
int print_UDP(struct udphdr *udphdr, FILE *fp);
void get_time(FILE *fp);
void usage(FILE *fp);
