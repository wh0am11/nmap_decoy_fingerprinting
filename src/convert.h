#ifndef __convert_stuff__
#define __convert_stuff__

#include "err.h"
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>

char *num_to_ip(uint32_t ip_addr) {

	char *str = malloc(sizeof(char) * INET_ADDRSTRLEN + 1);

	if (!str) {

		err("Memory not allocated.");
		return NULL;

	}

	struct sockaddr_in sa;
	sa.sin_addr.s_addr = htonl(ip_addr);

	inet_ntop(AF_INET, &sa.sin_addr, str, INET_ADDRSTRLEN);

	return str;
	

}

#endif
