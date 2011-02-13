#include "udp_send.h"
#include "defs.h"

struct strings{
	string s1;
	string s2;
};

void call_send_to(string ip, string msg){
	   pthread_t l_thread;
	   int l_ret;
	   strings args;
	   args.s1 = ip;
	   args.s2 = msg;
	   l_ret = pthread_create(&l_thread, NULL, udp_send_to, (void*)&args);
}

void *udp_send_to(void* args){
	strings *res = (strings *)args;
	string ip = res->s1 ;
	string msg = res->s2 ;
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(ip.c_str(), SERVERPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		goto end;
	}

	// loop through all the results and make a socket
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("talker: socket");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "talker: failed to bind socket\n");
	}

	if ((numbytes = sendto(sockfd, msg.c_str(), strlen(msg.c_str()), 0,
			 p->ai_addr, p->ai_addrlen)) == -1) {
		perror("talker: sendto");
	}
	freeaddrinfo(servinfo);
	printf("talker: sent %d bytes to %s\n", numbytes, ip.c_str());
	close(sockfd);
end:;
}

string get_reply(string ip, string msg){
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(ip.c_str(), SERVERPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return "";
	}

	// loop through all the results and make a socket
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("talker: socket");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "talker: failed to bind socket\n");
		return "";
	}

	if ((numbytes = sendto(sockfd, msg.c_str(), strlen(msg.c_str()), 0,
			 p->ai_addr, p->ai_addrlen)) == -1) {
		perror("talker: sendto");
		return "";
	}

	freeaddrinfo(servinfo);

	printf("talker: sent %d bytes to %s\n", numbytes, ip.c_str());
	close(sockfd);

	return "";
}
