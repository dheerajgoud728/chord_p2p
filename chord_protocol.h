#ifndef CHORD_PROTOCOL_H_
#define CHORD_PROTOCOL_H_

#include "includes.h"
#include "udp_listen.h"
#include "udp_send.h"
#include "defs.h"

#define SUCCESSOR fingers[0]

class node{
public:
	string ip;
	unsigned int port;
	char id[20];
	node(){
		ip = "255.255.255.255";
	}
}my_node, my_predecessor;

node fingers[160];
char start[160][20];


void convert_to_nodes(string str, node * nd1, node * nd2);
void convert_to_node(string str, node *nd);

void calc_id(string str, char id[]);
bool is_greater(char * id1, char * id2);
bool is_lesser(char * id1, char * id2);
bool is_equal(char * id1, char * id2);
bool is_between(char * id, char * id1, char * id2, int ob=0, int cb=0);
char * get_start_at(int n);
string get_successor();
void set_successor(string ip);
string get_predecessor();
void set_predecessor(string ip);
int closest_preceding_finger(char * id);
string find_predecessor(char * id);
string find_successor(char * id);
void init();
void init_finger_table(string ip);
void update_others();
void update_finger_table(string ip, int i);
void join(string ip);
void stabilize();
void notify(string ip);
void fix_fingers();
char * add_id_to_2p(char id[], int n);
void array_copy(char arr1[], char arr2[]);


#endif
