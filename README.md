# nmap_decoy_fingerprinting
A proof of concept for a passive fingerprinting technique that can be used to identify the "real" address from a bunch of decoy addresses.



# Purpose

This repository is a proof of concept for a passive fingerprinting technique that can be used to identify the "real" address when being scanned by someone using decoy addresses. For example, let's say a hacker runs an Nmap scan like the one portrayed below:

`h4ck3r@kiddie.com:~/dir$ nmap 1.2.3.4 -D 1.2.3.1,1.2.3.2,1.2.3.3`

Now, let's say you're a system administrator and you see this:

`
64418 11.397947201 1.2.3.4 → 1.2.3.5    TCP 58 40234 → 3827 [RST, ACK] Seq=0 Win=1024 Len=0 MSS=1460
64419 11.397956319 1.2.3.1 → 1.2.3.4    TCP 58 40234 → 3827 [SYN] Seq=0 Win=1024 Len=0 MSS=1460
64420 11.397968863 1.2.3.2 → 1.2.3.4    TCP 58 40234 → 3827 [SYN] Seq=0 Win=1024 Len=0 MSS=1460
64421 11.397979328 1.2.3.3 → 1.2.3.4    TCP 58 40234 → 3827 [SYN] Seq=0 Win=1024 Len=0 MSS=1460
64422 11.397990158 1.2.3.2 → 1.2.3.4    TCP 58 40234 → 3827 [SYN] Seq=0 Win=1024 Len=0 MSS=1460`


*(sigh)*; how annoying. Someone is scanning my system and I don't know who it is. Well, look a bit closely. Do you see that top packet? Our machine sent an `RST ACK` to one of the IP addresses apparently scanning us. And, in fact, if, in this hypothetical situation, if we were to keep examining the packet stream, we would notice that this pattern recurrs: Our IP address (`1.2.3.4`) will occasionally send an `RST ACK` to `1.2.3.5` and, in fact, that `1.2.3.5` would be our hacker's IP address.

*Woah, that sounds far-fetched*, you, the reader, may say. Well, this program's purpose is to show that it's not that far-fetched and that it's **really** easy to figure out someone's IP address among a group of IP addresses scanning you by using this method.

# Usage

To run this program, type this:

`sudo ./main [interface]`

`interface` is the network interface to scan on.
This program, being a proof of concept, should be run in an isolated environment, i.e, you should run it on a network with little traffic. However, if you aren't able to use an isolated network, you can simply just run this on any network and it will work just fine. Also, if you have the ability, run this program with 2 computers. One of the computers will be the scanner and the other will be the one to run this program.
