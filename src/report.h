#ifndef __report__
#define __report__

#include "convert.h"

void report_stats(CONN *array[], int size) {

	int i = 0;
	char *src = NULL, *dst = NULL;

	printf("\n\n\n\t\tREPORT\n\t\t------\n\n");

	for (i = 0; i < size; i++) {

		if (array[i]) {

			src = num_to_ip((uint32_t) array[i]->saddr);
			dst = num_to_ip((uint32_t) array[i]->daddr);

			if (array[i]->rsts_sent > 0) {

				if (array[i]->rsts_sent > 900) 
					printf("[...] RST ACKs sent (%s -> %s): %d (***%s IS THE SCANNER***)\n", src, dst, array[i]->rsts_sent, dst);
				else if (array[i]->rsts_sent > 10)
					printf("[...] RST ACKs sent (%s -> %s): %d (%s is a potential scanner?)\n", src, dst, array[i]->rsts_sent, dst);

			}
		

		}
	}

	printf("\n\n\n");

}


#endif
