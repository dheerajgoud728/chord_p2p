#include "includes.h"
#include "defs.h"

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

string char_to_str(char * chr){
	stringstream ss;
	string ret;
	ss<<chr;
	ss>>ret;
	return ret;
}

string int_to_str(int i){
	stringstream ss;
	string ret;
	ss<<i;
	ret=ss.str();
	return ret;
}

