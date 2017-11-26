#ifndef __capture__
#define __capture__

#include "array.h"
#include "report.h"
#include "process_packets.h"
#include "monitor_conn.h"
#include <signal.h>
#include <pcap.h>


CONN **conns = NULL;
pcap_t *glob_handle = NULL;
int size = BUFSIZ;

CONN **init_conns()  {

	if (conns) return conns;

	conns = calloc(size, sizeof(CONN));

	if (!conns) {

		err("Memory not allocated");
		return NULL;
	}

	return conns;

}


void finish_err(pcap_t *handle) {

		if (handle) pcap_close(handle);
                if (conns) free_all(conns, size);
                exit(1);
}

void handle_signal(int sig) {

	if (glob_handle) pcap_breakloop(glob_handle);

}

pcap_t *create_handle(const char *dev) {

	pcap_t *handle = NULL;
	char errbuff[PCAP_ERRBUF_SIZE];

	handle = pcap_open_live(dev, 500, 1, -1, errbuff);

	if (handle == NULL) {
	
		err(errbuff);
		return NULL;
	}


	return handle;

}

void handle_entry(CONN *conn, const unsigned char *pkt) {

	conn = copy_bit_flags(pkt, conn);
	char *src = num_to_ip(get_addr(pkt, SRC_ADDR));
	char *dst = num_to_ip(get_addr(pkt, DST_ADDR));

	if (!src || !dst) {

		err("IP numerical representation not converted");

	} else {

		if (conn->rst_bit == 1 && conn->ack_bit == 1) conn = rst_found(conn, src, dst);	

		free(src);
		free(dst);
	}
}

void handle_new_entry(CONN *conn, const uint32_t saddr, const uint32_t daddr, const unsigned char *pkt) {

	conn = new_conn(saddr, daddr);

	if (!conn) {

		err("Memory not allocated");

	} else {

		add_entry(conns, size, conn);
		handle_entry(conn, pkt);
	}

}

void handle_packets(u_char *user, const struct pcap_pkthdr *hdr, const u_char *pkt) {

	uint32_t saddr = 0;
	uint32_t daddr = 0;
	CONN *conn = NULL;

	if (pkt) {

		saddr = get_addr(pkt, SRC_ADDR);
		daddr = get_addr(pkt, DST_ADDR);

		conn = find_entry(conns, size, saddr, daddr);
		

		if (conn) 
			handle_entry(conn, pkt);
		else 	
			handle_new_entry(conn, saddr, daddr, pkt);

	}

}

void loop_forever(pcap_t *handle) {

	conns = init_conns();

	if (!conns) {

		err("Unable to allocate memory");
		finish_err(handle);
	}

	conns[0] = NULL;

	signal(SIGINT, handle_signal);
	glob_handle = handle;
	
	printf("Scanning...\n");

	int code = pcap_loop(handle, -1, handle_packets, NULL);

	if (code == -1) {

		pcap_perror(handle, "[ERR] Loop broken");
		finish_err(handle);

	} else if (code == -2) {

		printf("Finished...\n");
		report_stats(conns, size);
		if (handle) pcap_close(handle);
		if (conns) free_all(conns, size);
	}


}




#endif
