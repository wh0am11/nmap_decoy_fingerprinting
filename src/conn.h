#ifndef __conn_h__
#define __conn_h__

#include <stdio.h>
#include <stdint.h>

#define SYN_BIT 0x1
#define ACK_BIT 0x2
#define RST_BIT 0x4

typedef struct conn_ident {

	uint32_t saddr;
	uint32_t daddr;

	struct bits {

		uint8_t syn : 1;
		uint8_t ack : 1;
		uint8_t rst : 1;
	} bits;

	int rsts_sent;

} CONN;

#define syn_bit bits.syn
#define ack_bit bits.ack
#define rst_bit bits.rst

#endif
