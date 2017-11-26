#ifndef __err__
#define __err__

#include <stdio.h>
#include <string.h>
#include <errno.h>

void err(const char *msg) {


	fprintf(stderr, "[ERR] %s: ", msg);
	
	if (errno) fprintf(stderr, "%s\n", strerror(errno));
	else fprintf(stderr, "None\n");

}

#endif
