//
//parse_args.h
//Written by, Sohail Qayum Malik
//

namespace parse{

struct parse_args{  
   int index;
   int previousIndex;
   const int parse(int argc, const char**, char*, int);    
   void parse(struct iphdr*, struct icmphdr*);
};

}; //namespace parse_args


void parse::parse_args::parse(struct iphdr* iphdr, struct icmphdr* icmphdr){        
   printf("Reply....\n");
   printf("Source=%u.%u.%u.%u TTL=%u\nICMP-type=",iphdr->saddr&0x000000ff, (iphdr->saddr&0x0000ff00)>>0x8,(iphdr->saddr&0x00ff0000)>>0x10,(iphdr->saddr&0xff000000)>>0x18, iphdr->ttl);  

   switch(icmphdr->type){
      case 0:
         printf("\"Echo reply\" ");
      break; 
      case 3:
         printf("\"destination unreachable\" "); 
              switch(icmphdr->code){
                 case 1:
                    printf("code=\"host unreachable\" ");
                 break; 
                 case 4:
                    printf("code=\"could'nt fragment, DF bit was set\" ");
                    printf("source-MTU=%u ",icmphdr->un.frag.mtu);
                 break;
              }
      break;
      case 11:
         printf("\"TTL time expired\" "); 
         if(icmphdr->code == 0)
            printf("code=\"TTL become 0 during transit\" ");
      break;
      default:
      break;
   }
   printf("\n");
}

const int parse::parse_args::parse(int argc, const char** argv, char* argument, int numberOfArgs){     

   int count;
     
   for(count=index; count<argc; count++)
      if(strcmp(argument, argv[count]) == 0)
         if((count + numberOfArgs + 1) <= argc){
	    if(previousIndex == 0)
               previousIndex=count;	 
            index = count;
            return 1;
         }
         else{
            printf("too few arguments for option \"%s\"\n", argument);
            printf("try `%s help' for more information.\n", *argv);
            count=argc;
	    exit(EXIT_FAILURE);	
         }             
   
   index = 0;
   return 0;   
}

 
