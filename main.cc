//
//main.cc
//Written by, Sohail Qayum Malik
//

#include "stuff.h"
#include "main.h"
#include "parse_args.h"
#include "build_header.h"
#include "local_connect.h"

using namespace::parse;
using namespace::build;
using namespace::local_connect;

int main(int argc, char *argv[]){

   struct parse_args args;
   struct build_header datagramOut;
   struct connection connection;
   char* datagramIn = new char(sizeof(struct iphdr) + sizeof(struct icmphdr));
   struct iphdr* iphdr;
   struct icmphdr* icmphdr; 
   
   INITIALIZE(args);
   PARSE_ARGSX(args,HELP,0);
   if(args.index > 0 || argc < 2){
      printf("usage : %s <src x.x.x.x> <dst x.x.x.x> [mtu <n>] [ttl <n>]\n",argv[0]);
      return 0;
   }
 
   //Lets see if ttl command line option is used.
   INITIALIZE(args);
   PARSE_ARGSX(args,TTL,1);
   if(args.index > 0)
      datagramOut.ttl = atoi(argv[args.index + 1]);
   else
      datagramOut.ttl = MAX_TTL;

   //Lets see if MTU command line option is used.
   //the value of MTU should atleast be greater than the combined size of.... 
   //IP and the size of the ICMP headers.
   INITIALIZE(args);  
   PARSE_ARGSX(args,MTU,1);
   if(args.index > 0 && atoi(argv[args.index + 1]) > (sizeof(struct iphdr) + sizeof(struct icmphdr))) 
      datagramOut.mtu = atoi(argv[args.index + 1]) - (sizeof(struct iphdr) + sizeof(struct icmphdr));      
   else
      datagramOut.mtu = 0;
     
   //Lets look for the source and destination addresses.
   //and then as a final step build headers....
   INITIALIZE(args);
   PARSE_ARGSX(args,SRC,1);
   args.index=0;
   PARSE_ARGSX(args,DST,1);
   //lets go and build the headers.
   //the function "build" expects the source and destination addresses.
   datagramOut.build(argv[args.previousIndex + 1], argv[args.index + 1]);
   //Lets finally connect, and hopefully get the reply.
   //the function connect expects the destination address and the datagram to send and to receive.
   connection.connect(argv[args.index + 1], datagramOut.header, datagramIn); 
   INITIALIZE(args);

   iphdr  = reinterpret_cast<struct iphdr*>(datagramIn);
   icmphdr = reinterpret_cast<struct icmphdr*>(datagramIn + (iphdr->ihl * 4));

   if(iphdr->protocol == IPPROTO_ICMP)
      args.parse(iphdr, icmphdr);
   else
      printf("Protocol is not ICMP.\n"); 
            
   return 0;
}

