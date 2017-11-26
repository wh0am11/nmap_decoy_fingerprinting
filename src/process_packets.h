#ifndef __process_pkts__
#define __process_pkts__


#include "monitor_conn.h"
#include <stdlib.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

#define SRC_ADDR 1
#define DST_ADDR 0

struct iphdr *get_iph_layer(const unsigned char *buffer) {

	struct iphdr *iph = (struct iphdr *) (buffer + sizeof(struct ether_header));

	return iph;

}

struct tcphdr *get_tcph_layer(const unsigned char *buffer) {

	struct tcphdr *tcph = (struct tcphdr *) (buffer + sizeof(struct iphdr) + sizeof(struct ether_header));

	return tcph;

}

uint32_t get_addr(const unsigned char *buffer, int type) {

	struct iphdr *iph = get_iph_layer(buffer);
	uint32_t addr = 0;

	if (type == SRC_ADDR) 
		addr = (uint32_t) ntohl(iph->saddr);

	else if (type == DST_ADDR)
		addr = (uint32_t) ntohl(iph->daddr);
	else
		addr = 0;

	return addr;

}

CONN *copy_bit_flags(const unsigned char *buffer, CONN *c) {

	struct tcphdr *tcph = get_tcph_layer(buffer);
	c = clear_bits(c);

	if (tcph->syn) c = set_bits(c, SYN_BIT);
	if (tcph->ack) c = set_bits(c, ACK_BIT);
	if (tcph->rst) c = set_bits(c, RST_BIT);

	return c;

}

#endif
