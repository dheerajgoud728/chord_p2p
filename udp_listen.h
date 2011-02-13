/*
 * udp_listen.h
 *
 *  Created on: 13-Feb-2011
 *      Author: dheeraj
 */

#ifndef UDP_LISTEN_H_
#define UDP_LISTEN_H_

#define MYPORT "4950"
#define MAX_PENDING 5
#define MAX_LINE 256
#define MAXBUFLEN 1000

void call_listen();
void UDP_message(string from_ip, string message);
void* listen(void* dummy);

#endif /* UDP_LISTEN_H_ */
