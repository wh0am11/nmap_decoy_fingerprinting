# nmap_decoy_fingerprinting
A proof of concept for a passive fingerprinting technique that can be used to identify the "real" address from a bunch of decoy addresses.



# Purpose

This repository is a proof of concept for a passive fingerprinting technique that can be used to identify the "real" address when being scanned by someone using decoy addresses. For example, let's say a hacker runs an Nmap scan like the one portrayed below:

`h4ck3r@kiddie.com:~/dir$ nmap 1.2.3.4 -D 1.2.3.1,1.2.3.2,1.2.3.3`

Now, let's say you're a system administrator and you see this:


```
64418 11.397947201 1.2.3.4 → 1.2.3.5    TCP 58 40234 → 3827 [RST, ACK] Seq=0 Win=1024 Len=0 MSS=1460


64419 11.397956319 1.2.3.1 → 1.2.3.4    TCP 58 40234 → 3827 [SYN] Seq=0 Win=1024 Len=0 MSS=1460


64420 11.397968863 1.2.3.2 → 1.2.3.4    TCP 58 40234 → 3827 [SYN] Seq=0 Win=1024 Len=0 MSS=1460


64421 11.397979328 1.2.3.3 → 1.2.3.4    TCP 58 40234 → 3827 [SYN] Seq=0 Win=1024 Len=0 MSS=1460


64422 11.397990158 1.2.3.2 → 1.2.3.4    TCP 58 40234 → 3827 [SYN] Seq=0 Win=1024 Len=0 MSS=1460
```


*(sigh)*; how annoying. Someone is scanning my system and I don't know who it is. Well, take a closer look. Do you see that top packet? Our machine sent an `RST ACK` to one of the IP addresses scanning us. And if, in this hypothetical situation, we were to keep examining the packet stream, we would notice that this pattern recurrs: Our IP address (`1.2.3.4`) will occasionally send an `RST ACK` to `1.2.3.5`. Also, believe it or not, `1.2.3.5` is, in fact, our hacker's IP address.

*Woah, that sounds far-fetched*, you, the reader, may say. Well, this program's purpose is to show that it's not that far-fetched and that it's **really** easy to figure out someone's IP address among a group of IP addresses scanning you by using this method.

# Compilation

It's pretty simple. Just run the following:

`make all`

# Usage and Conditions

To run this program, type this:

`sudo ./main [interface]`

`interface` is the network interface to scan on.

This program, being a proof of concept, has specific requirements. This program should be, if you have the ability, run in an isolated environment, i.e, you should run it on a network with little traffic. Also, run this program with 2 computers. One of the computers will be the scanner and the other will be the one to run this program. 

On the scanner machine, run this:

`nmap x.x.x.x -D x.x.x.a,x.x.x.b,x.x.x.c`

where `x.x.x.x` is the IP of the computer being scanned and `x.x.x.a`, `x.x.x.b`, `x.x.x.c` are the decoy addresses.

On the machine being scanned, run the following:

`sudo ./main [interface]`

When the scanner computer is finished scanning, press Ctrl + C on the machine being scanned (the one that is running this program). You should see a report screen that will show you something like this: 

```
[!] 67.207.82.167 -> 50.82.60.178 [RST, ACK]
[!] 67.207.82.167 -> 50.82.60.178 [RST, ACK]
[!] 67.207.82.167 -> 50.82.60.178 [RST, ACK]
[!] 67.207.82.167 -> 50.82.60.178 [RST, ACK]
[!] 67.207.82.167 -> 50.82.60.178 [RST, ACK]
[!] 67.207.82.167 -> 50.82.60.178 [RST, ACK]
[!] 67.207.82.167 -> 50.82.60.178 [RST, ACK]
[!] 67.207.82.167 -> 50.82.60.178 [RST, ACK]
[!] 67.207.82.167 -> 50.82.60.178 [RST, ACK]
[!] 67.207.82.167 -> 50.82.60.178 [RST, ACK]
[!] 67.207.82.167 -> 50.82.60.178 [RST, ACK]
[!] 67.207.82.167 -> 50.82.60.178 [RST, ACK]
[!] 67.207.82.167 -> 95.215.1.37 [RST, ACK]
^CFinished...



                REPORT
                ------

[...] RST ACKs sent (67.207.82.167 -> 50.82.60.178): 1677 (***50.82.60.178 IS THE SCANNER***)
```
The output above the `^CFinished...` statement shows the TCP packets the program is capturing that have the `RST` and `ACK` flag set. The report section will show you the number of TCP packets with the `RST` and `ACK` flag set between 2 hosts. In this example output, It shows us that 1677 TCP packets with the `RST` and `ACK` flag set were sent from `67.207.82.167` to `50.82.60.178` and that `50.82.60.178` is the scanner. 

