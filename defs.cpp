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
	return string(chr);
}

string int_to_str(int i){
	stringstream ss;
	string ret;
	ss<<i;
	ret=ss.str();
	return ret;
}

string uint_to_str(unsigned int i){
	stringstream ss;
	string ret;
	ss<<i;
	ret=ss.str();
	return ret;
}
