/*
 * defs.h
 *
 *  Created on: 12-Feb-2011
 *      Author: dheeraj
 */

#ifndef DEFS_H_
#define DEFS_H_

#include "includes.h"

struct cond_wait{
	pthread_cond_t * cond;
	pthread_mutex_t * mutex;
	unsigned int thread_id;
	time_t time;
	string return_val;
};

void *get_in_addr(struct sockaddr *sa);
string char_to_str(char * chr);
string int_to_str(int i);
string uint_to_str(unsigned int i);


#endif /* DEFS_H_ */
