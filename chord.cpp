//============================================================================
// Name        : chord.cpp
// Author      : Dheeraj
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "includes.h"
#include "defs.h"
#include "udp_listen.h"

vector<pthread_t> threads;
vector<int> rets;

int number = 1;

int main(int argc, char ** argv)
{
   string inp;
   call_listen();
   char t[10] = "hello!";
   cout<<char_to_str(t);
   while(1){
	   cin>>inp;
	   /*int ret;
	   ret = pthread_create(&tmp_t, NULL, (void*)&f_1);*/
   }
   return 0;
}
