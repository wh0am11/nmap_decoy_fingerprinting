#ifndef __conn_array__
#define __conn_array__

#include "monitor_conn.h"

CONN *find_entry(CONN *array[], int size, uint32_t saddr, uint32_t daddr) {

	int i = 0;
	CONN *entry = NULL;

	for (i = 0; i < size; i++) {

		if (array[i]) {

			if (array[i]->saddr == saddr && array[i]->daddr == daddr) {

				entry = array[i];
				break;
			} 

		}
	}


	return entry;

}

void add_entry(CONN *array[], int size, CONN *conn) {

	int i = 0;

	while (i < size && array[i] != NULL) ++i;

	if (array[i] == NULL) 
		array[i] = conn;
	else 
		err("Too many connections");


}

void free_all(CONN *array[], int size) {

	int i = 0;

	for (i = 0; i < size; i++) {

		if (array[i]) 
			free(array[i]);
	}

	free(array);

}

#endif
