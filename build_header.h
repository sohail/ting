//
//build_header.h
//Written by, sohail.github.io
//

namespace build{
struct build_header{
   unsigned short int mtu;
   unsigned char ttl;
   int partial;
   char* header;    
   void build(char*,char*);      
   unsigned short int checksum(unsigned short int *, int, int);
};
}; //namespace build_header

void build::build_header::build(char* src, char* dst){   
   
   header                  = new char(sizeof(struct iphdr) + sizeof(struct icmphdr) + mtu);   
   struct iphdr* iphdr     = reinterpret_cast<struct iphdr *>(header);
   struct icmphdr* icmphdr = reinterpret_cast<struct icmphdr *>(header + sizeof(struct iphdr));
	
   //////The IP header build/////////////////////////////////////////////
   iphdr->ihl         = 5;
   iphdr->version     = 4;
   iphdr->tos         = 0;
   iphdr->tot_len     = sizeof(struct iphdr) + sizeof(struct icmphdr) + mtu;
   iphdr->id          = 0;
   if(mtu > 0) 
      iphdr->frag_off = htons(0x4000);
   else
      iphdr->frag_off = 0;
   iphdr->ttl         = ttl;
   iphdr->protocol    = IPPROTO_ICMP;
   iphdr->check       = 0;  
   iphdr->saddr       = inet_addr(src);
   iphdr->daddr       = inet_addr(dst);
   iphdr->check       = checksum((unsigned short int*)iphdr, sizeof(struct iphdr), 0);
   ////////////////////////////////////////////////////////////////////
   /////The ICMP header build///////////////////////////////////////////
   icmphdr->type             = ICMP_ECHO;
   icmphdr->code             = 0;
   icmphdr->checksum         = 0;
   icmphdr->un.echo.id       = random();
   icmphdr->un.echo.sequence = 0;
   icmphdr->checksum         = checksum(reinterpret_cast<unsigned short int*>(icmphdr), sizeof(struct icmphdr) + mtu, 0);
              
}

unsigned short build::build_header::checksum(unsigned short int* header, int headerSize, int partial){
   
   int sumOf16BitWords; 

   if(partial==2)
      sumOf16BitWords = this->partial;
   else
      sumOf16BitWords = 0;
   
   while(headerSize > 1){ 
      sumOf16BitWords+=*header++; 
      if(sumOf16BitWords & 0x80000000)
         sumOf16BitWords = (sumOf16BitWords & 0xffff) + (sumOf16BitWords >> 16);
      headerSize-=2;                
   }   

   if(headerSize==1)
      sumOf16BitWords+=static_cast<unsigned short int>(*((unsigned char *)header));
      
   if(partial==1){
      this->partial = sumOf16BitWords;
      return 0;
   }
   
   if(sumOf16BitWords >> 16)
      sumOf16BitWords = (sumOf16BitWords & 0xffff) + (sumOf16BitWords >> 16);        

   return (~sumOf16BitWords);

}



 


