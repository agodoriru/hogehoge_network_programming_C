ethernet packet  


 --------------------------------------------------------------
|プリアンブル   SFD    宛先mac address   送信元mac address type  dete   fcs
|   7byte      1byte     6byte           6byte           2byte  46-1500byte  4byte
|
 ----------------------------------------------------------------


 プリアンブル
 SFD




---

### hoge.c

* main
* init_descriptor

main()
command line arg 0 -> usage()  
command line arg[1] show -> interface_checker()  

init_descriptor() ->loop  



init_discriptor()  


---

### interface_checker.c


socket()
ソケット生成



---

### analuzer.c

* analyze_ICMP
* analyze_Packet
* analyze_Arp


---

### printer.c



