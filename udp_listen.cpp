
#include "includes.h"
#include "defs.h"
#include "udp_listen.h"
#include "udp_send.h"

bool listening;

extern vector<cond_wait> waiting_list;

void call_listen(){
	   pthread_t l_thread;
	   int l_ret;
	   int dummy = 0;
	   l_ret = pthread_create(&l_thread, NULL, listen, (void *)dummy);
}

// action to be taken on receiving a message
bool UDP_message(string from_ip, string message){
	char * tok;
	tok = strtok(&message[0], "_");
	if(char_to_str(tok) == "GTID"){
		string rmsg = "gtid_"+uint_to_str((unsigned int)pthread_self());
		tok = strtok(NULL, "_");
		while(tok != NULL){
			rmsg += "_" + char_to_str(tok);
			tok = strtok(NULL, "_");
		}
		cout<<rmsg<<endl;
		udp_send(from_ip, rmsg);
	}
	else if(char_to_str(tok) == "gtid"){
		vector<string> args;
		tok = strtok(NULL, "_");
		while(tok != NULL){
			args.push_back(char_to_str(tok));
			tok = strtok(NULL, "_");
		}
		if(args.size() != 2)
			return false;
		string t_show = args[0];
		unsigned int tid = (unsigned int)atoi(args[1].c_str());
		stringstream ss;
		ss<<args[1];
		ss>>tid;



		for(int i = 0; i < waiting_list.size(); i++){
			if(waiting_list[i].thread_id == tid){
				cout<<"in if"<<endl;
				waiting_list[i].return_val = t_show;
				if (pthread_cond_broadcast(waiting_list[i].cond) != 0) {
					perror("pthread_cond_signal() error");
					goto end;
				}
				break;
			}
		}
		cout<<"end of for"<<endl;
	}
end:;
	return true;
}

void* listen(void* dummy){
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;
	char buf[MAXBUFLEN];
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		goto end;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("listener: bind");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		close(sockfd);
		exit(1);
	}

	freeaddrinfo(servinfo);

	printf("listener: waiting to recvfrom...\n");
	listening = true;
	addr_len = sizeof their_addr;
	if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) {
		perror("recvfrom");
		close(sockfd);
		exit(1);
	}

	inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
	//printf("listener: packet is %d bytes long\n", numbytes);
	buf[numbytes] = '\0';
	printf("%s:\"%s\"\n", s, buf);
end:
	close(sockfd);
	listening = false;
    call_listen();
    while(!listening);
    UDP_message(char_to_str(s), char_to_str(buf));
}

