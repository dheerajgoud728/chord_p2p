#ifndef UDP_SEND_H_
#define UDP_SEND_H_

#include "includes.h"

#define SERVERPORT "4950"	// the port users will be connecting to

void *udp_send_to(void* args);
string get_reply(string ip, string msg);
void call_send_to(string ip, string msg);
void udp_send(string ip, string msg);

#endif
