#include "udp_send.h"
#include "defs.h"

extern vector<cond_wait> waiting_list;

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

void udp_send(string ip, string msg){
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	cout<<msg<<endl;
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
	printf("talker2: sent %d bytes to %s\n", numbytes, ip.c_str());
	close(sockfd);
end:;
	cout<<"eof udp_send()"<<endl;
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
	//printf("talker: sent %d bytes to %s\n", numbytes, ip.c_str());
	close(sockfd);
end:;
}

string get_reply(string ip, string msg){
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;

	//add thread id to the end of message
	msg = msg + "_" + uint_to_str((unsigned int)pthread_self());
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
	close(sockfd);
	cond_wait cw;
	time(&cw.time);
	if (pthread_mutex_init(cw.mutex, NULL) != 0) {
		perror("pthread_mutex_init() error");
		return "";
	}
	if (pthread_cond_init(cw.cond, NULL) != 0) {
		perror("pthread_cond_init() error");
		return "";
	}
	if (pthread_mutex_lock(cw.mutex) != 0) {
		perror("pthread_mutex_lock() error");
		return "";
	}
	cw.thread_id = (unsigned int)pthread_self();
	waiting_list.push_back(cw);
	//cout<<"TID:"<<cw.thread_id<<","<<cw.cond<<","<<cw.mutex<<endl;
	if (pthread_cond_wait(cw.cond, cw.mutex) != 0) {
	    perror("pthread_cond_timedwait() error");
	    return "";
	}
	for(int i = 0; i < waiting_list.size(); i++){
		if(waiting_list[i].thread_id == cw.thread_id){
			waiting_list.erase(waiting_list.begin() + i);
			break;
		}
	}
	return cw.return_val;
}

