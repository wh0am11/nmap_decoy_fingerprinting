#include "capture.h"

#define MAX_DEVICE 300


void intro() {

	printf("This program is a proof of concept. It shows how Nmap's Decoy Address Feature (the '-D' option) can be fingerprinted quite easily.\n");
	printf("This fingerprinting allows for an individual to identify the IP address associated with the 'real' scanner. thereby nullifying the\n");
	printf("use of the decoy feature in Nmap.\n");
	printf("Press Ctrl^C to quit.\n\n");

}

int main(int argc, char *argv[]) {

	if (argc != 2) {

		fprintf(stderr, "[ERR] Exactly one argument required; Usage: ./main [interface]\n");
		return -1;
	}
	
	char device[MAX_DEVICE];

	strncpy(device, argv[1], MAX_DEVICE);

	pcap_t *handle = create_handle(device);

	if (handle) {

		intro();
		loop_forever(handle);

	} else { 

		return -1;
	}

	

	return 0;

}
