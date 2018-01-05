//
//local_connect.h
//Written by, sohail.github.io
//

namespace local_connect{
   struct connection{
      void connect(char*, void*, void*);
   };
};//namespace connection

void local_connect::connection::connect(char* dst, void* datagramOut, void* datagramIn){

   int sockfd;
   int options;
   unsigned int nread;
   struct sockaddr_in pcb;  
   struct iphdr* iphdr = reinterpret_cast<struct iphdr*>(datagramOut);
   
   sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
   if(sockfd < 0){
      perror("socket");
      exit(EXIT_FAILURE);
   }

   setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &options, sizeof(options)); 

   pcb.sin_family = PF_INET;
   pcb.sin_addr.s_addr = inet_addr(dst); 

   if(sendto(sockfd, datagramOut, iphdr->tot_len, 0, reinterpret_cast<struct sockaddr*>(&pcb), sizeof(struct sockaddr)) < 0){
      perror("sendto");
      exit(EXIT_FAILURE);
   }
   
   recvfrom(sockfd, datagramIn, sizeof(struct iphdr) + sizeof(struct icmphdr), 0, reinterpret_cast<struct sockaddr*>(&pcb), (socklen_t *)sizeof(pcb));

   close(sockfd);
  
}
