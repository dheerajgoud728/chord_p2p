#include "chord_protocol.h"

/*
string get_successor(){
	return SUCCESSOR.ip;
}

void set_successor(string ip){
	SUCCESSOR.ip = ip;
	calc_id(ip, SUCCESSOR.id);
}

string get_predecessor(){
	return my_predecessor.ip;
}

void set_predecessor(string ip){
	my_predecessor.ip = ip;
	calc_id(ip, my_predecessor.id);
}

int closest_preceding_finger(char * id){
	for(int i=159; i >=1; i--){
		if(is_between(start[i], my_node.id, id, 0, 0)){
			return i;
		}
	}
	return 0;
}

string find_predecessor(char * id){
	node mnode=my_node;
	node snode=SUCCESSOR;
	while(!is_between( id, mnode.id, snode.id, 0, 1)){
		string receive=get_reply(mnode.ip , "CPF_"+char_to_str(id)+"_"+my_node.ip);
		convert_to_nodes(receive, &mnode, &snode);
	}
	return mnode.ip;
}

string find_successor(char * id){
	string p_ip=find_predecessor(id);
	char id1[20];
	calc_id(p_ip, id1);
	return get_reply(p_ip , "GS_"+char_to_str(id1)+"_"+my_node.ip);
}

void init(){
	for(int i = 0; i <= 159; i++){
		fingers[i].ip=my_node.ip;
		fingers[i].port=my_node.port;
		array_copy(fingers[i].id, my_node.id);
	}
	//start values

}

void init_finger_table(string ip){
	string receive = get_reply(ip , "FS_"+char_to_str(my_node.id)+"_"+my_node.ip);
	convert_to_node(receive,&SUCCESSOR);
	receive=get_reply(SUCCESSOR.ip, "GP_"+my_node.ip);
	convert_to_node(receive, &my_predecessor);
	udp_send_to(SUCCESSOR.ip, "SP_"+my_node.ip);
	for(int i = 0; i < 159; i++){
		if (is_between(start[i+1], my_node.id, fingers[i].id, 1, 0)){
			fingers[i+1] = fingers[i];
		}
		else{
			receive = get_reply(ip , "FS_"+char_to_str(start[i+1])+"_"+my_node.ip);
			convert_to_node(receive,&fingers[i+1]);
		}
	}
}

void update_others(){
	for(int i = 0; i < 160; i++){
		string ip = find_predecessor(add_id_to_2p(my_node.id, i-1));
		udp_send_to(ip, "UFT_"+ip+"_"+int_to_str(i));
	}
}

void update_finger_table(string ip, int i){
	char id[20];
	calc_id(ip, id);
	if(is_between(id, my_node.id, fingers[i].id, 1, 0)){
		fingers[i].ip = ip;
		calc_id(ip, fingers[i].id);
		udp_send_to(my_predecessor.ip, "UFT_"+ip+"_"+int_to_str(i));
	}
}

void join(string ip){
	init_finger_table(ip);
	update_others();
}

void stabilize(){
	string receive = get_reply(SUCCESSOR.ip, "GP_"+my_node.ip);
	node nnode;
	convert_to_node(receive, &nnode);
	if(is_between(nnode.id, my_node.id, SUCCESSOR.id, 0, 0)){
		SUCCESSOR = nnode;
	}
	udp_send_to(SUCCESSOR.ip, "NTF_"+my_node.ip);
}

void notify(string ip){
	char id[20];
	calc_id(ip, id);
	if(my_predecessor.ip == "" || is_between(id, my_predecessor.id, my_node.id, 0, 0)){
		my_predecessor.ip = ip;
		calc_id(ip, my_predecessor.id);
	}
}

void fix_fingers(){
	for(int i = 1; i < 160; i++){
		fingers[i].ip = find_successor(start[i]);
		calc_id(fingers[i].ip, fingers[i].id);
	}
}
*/
