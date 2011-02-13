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

int c_wait = 0;
int m_wait = 0;

vector<cond_wait> waiting_list;
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
	   if(inp == "GTID"){
		   cout<<get_reply(ip, "GTID");
	   }
	   else
		   call_send_to(ip, inp);
   }
   return 0;
}
