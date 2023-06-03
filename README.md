ting
====
Little _tarceroute_ and _ping_ like thing, that is why it is a "**ting**"

--Last updated :- 3rd, June 2023
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


A session with ting...
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
### History of our session with ting
In this session with the program "ting," the objective was to trace the route from the source IP address (192.168.1.110) to the destination IP address (198.54.114.214) using different TTL (Time-to-Live) values. The TTL value represents the maximum number of hops (routers) a packet can traverse before being discarded.

### What happened in each step of our previous session:

- With TTL set to 1, the packet reached the first hop (192.168.1.1) before the TTL expired. The router at this hop sent an ICMP (Internet Control Message Protocol) message with the type "TTL time expired" and code "TTL become 0 during transit" back to the source.

- With TTL set to 2, the packet reached another hop (1.1.1.1) before the TTL expired. Again, an ICMP message was received indicating TTL expiration.

- With TTL set to 3, the packet reached the third hop (192.168.149.1) before TTL expiration, and an ICMP message was received.

- No reply was received when TTL was set to 4, indicating that the TTL value was not sufficient to reach the destination.

- The same situation occurred with TTL set to 5, and no reply was received.

- With TTL set to 6, the packet reached a different hop (42.201.255.41) before TTL expiration. An ICMP message was received indicating TTL expiration.

- Increasing the TTL to 17, the packet reached a further hop (129.250.4.107) before TTL expiration, and an ICMP message was received.

- Increasing the TTL to 20, the packet reached another hop (199.193.7.158) before TTL expiration, and an ICMP message was received.

- Setting the TTL to 21, the packet finally reached the destination (198.54.114.214), and an ICMP "Echo reply" message was received. This indicates that the destination responded to the packet.

### Summary
In this session, ting was able to trace the route by progressively increasing the TTL value. The TTL field in the IP header was used to control the maximum number of hops the packet could traverse. Each router decremented the TTL value by one when forwarding the packet. When the TTL reached 0, the router discarded the packet and sent an ICMP message back to the source. By incrementally increasing the TTL, ting was able to discover the sequence of hops between the source and destination and determine the route.


