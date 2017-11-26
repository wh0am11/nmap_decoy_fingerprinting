#ifndef __monitor_conn__
#define __monitor_conn__

#include "conn.h"
#include "err.h"
#include <stdlib.h>

CONN *clear_bits(CONN *c);


int start_of_connection(CONN *c) {

	int ret = (c->syn_bit && !c->ack_bit && !c->rst_bit) ? 1 : 0;

	return ret;

}

CONN *new_conn(const uint32_t src, const uint32_t dst) {

	CONN *c = malloc(sizeof(CONN));

	if (!c) {

		err("Memory not allocated");
		return NULL;
	}

	c->saddr = src;
	c->daddr = dst;
	c->rsts_sent = 0;
	c = clear_bits(c);

	return c;

}

CONN *clear_bits(CONN *c) {

	bzero(&c->bits, sizeof(c->bits));

	return c;

}

CONN *set_bits(CONN *c, uint8_t flags) {

	switch (flags) {

		case SYN_BIT:
			c->syn_bit = 1;
			break;
		case ACK_BIT:
			c->ack_bit = 1;
			break;
		case RST_BIT:
			c->rst_bit = 1;
			break;
	}

	return c;

}

CONN *rst_found(CONN *c, const char *src, const char *dst) {

	printf("[!] %s -> %s [RST, ACK]\n", src, dst);
	++c->rsts_sent;
	return c;

}

#endif
