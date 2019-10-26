ting
====
Little _tarceroute_ and _ping_ like thing, that is why it is a "**ting**"

--Last updated :- 5th, January 2018
-----------------------------------

**ting**(it pings, traces route and finds path-MTU). 
====================================================
You know what ping does, and what is a traceroute. 
This is my implementation of them. Written purely to study the the protocol headers of IP/ICMP and raw-sockets. I call it, the ting, the name ting makes sense to me as this program pings and traces route. ting is written in C++ish. ting can also be used to find the path-MTU(like I've never told you that before). I wrote this tool while reading chapter on ICMP protocol from book [TCP/IP Illustrated First Edition by, ](https://en.wikipedia.org/wiki/TCP/IP_Illustrated)[W. Richard Stevens](https://en.wikipedia.org/wiki/W._Richard_Stevens).

---------------------------------------------
| ting, command line options and arguments. |
---------------------------------------------
 [help]
   example :- ./ting help
   This option will generate a help screen.

 <src x.x.x.x dst x.x.x.x> [mtu <n>] [ttl <n>]
   The "x.x.x.x" are the source and destination IP addresses. The n is a number. 
   You'll use option ttl to trace the route. 
   You'll use the option mtu to find the path-MTU. 
   With option ttl, n could go upto 255. 
   With option mtu, n is the maximum size of datagram. 

 --If option ttl is not used/given at CLI then... 
      the ttl of the outgoing datagram is set to MAX_TTL(a macro defined in file stuff.h).
 --If option mtu is not used/given at CLI then... 
      the the size of outgoing datagram is the combined size of IP and ICMP headers.
 --If mtu is less than the combined size of IP and ICMP headers then... 
      the size of the outgoing datagram is the combined size of the IP and ICMP headers. 


Example session...
------------------
````
funtoo ting # ./ting src 192.168.1.110 dst 198.54.114.214 ttl 1
Reply....
Source=192.168.1.1 TTL=64
ICMP-type="TTL time expired" code="TTL become 0 during transit"

funtoo ting # ./ting src 192.168.1.110 dst 198.54.114.214 ttl 2
Reply....
Source=1.1.1.1 TTL=63
ICMP-type="TTL time expired" code="TTL become 0 during transit"

funtoo ting # ./ting src 192.168.1.110 dst 198.54.114.214 ttl 3
Reply....
Source=192.168.149.1 TTL=62
ICMP-type="TTL time expired" code="TTL become 0 during transit"

funtoo ting # ./ting src 192.168.1.110 dst 198.54.114.214 ttl 4

funtoo ting # ./ting src 192.168.1.110 dst 198.54.114.214 ttl 5

funtoo ting # ./ting src 192.168.1.110 dst 198.54.114.214 ttl 6
Reply....
Source=42.201.255.41 TTL=250
ICMP-type="TTL time expired" code="TTL become 0 during transit"

funtoo ting # ./ting src 192.168.1.110 dst 198.54.114.214 ttl 17
Reply....
Source=129.250.4.107 TTL=240
ICMP-type="TTL time expired" code="TTL become 0 during transit"

funtoo ting # ./ting src 192.168.1.110 dst 198.54.114.214 ttl 20
Reply....
Source=199.193.7.158 TTL=237
ICMP-type="TTL time expired" code="TTL become 0 during transit"

funtoo ting # ./ting src 192.168.1.110 dst 192.54.114.214 ttl 21
Reply....
Source=198.54.114.2 TTL=46
ICMP-type="Echo reply"

funtoo ting # ./ting src 192.168.1.110 dst 198.54.114.214
Reply....
Source=198.54.114.214 TTL=46
ICMP-type="Echo reply"
````

