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
#include "udp_send.h"

vector<int> rets;

int number = 1;

int main(int argc, char ** argv)
{
   string inp;
   cout<<"Enter ip:"<<endl;
   string ip;
   cin>>ip;
   call_listen();
   while(1){
	   cin>>inp;
	   call_send_to(ip, inp);
   }
   return 0;
}
