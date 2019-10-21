//
//stuff.h
//Written by, Sohail Qayum Malik
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <unistd.h>


#define		PING		"ping"
#define		TRACEROUTE	"traceroute"
#define		HELP		"help"
#define		TTL		"ttl"
#define		SRC		"src"
#define		DST		"dst"
#define		MTU		"mtu"
#define		MAX_TTL		64 

#define 	EXTRA		33

