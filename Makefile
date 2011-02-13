all:  defs.o udp_listen.o  udp_send.o chord.o 
	g++ chord.o udp_listen.o udp_send.o defs.o -o listener -g -lpthread
	
defs.o: defs.cpp
	g++ -c defs.cpp
        

udp_listen.o: udp_listen.cpp
	g++ -c udp_listen.cpp 

udp_send.o: udp_send.cpp
	g++ -c udp_send.cpp 

chord.o: chord.cpp
	g++ -c chord.cpp
	

clean:
	rm -rf *o listener

