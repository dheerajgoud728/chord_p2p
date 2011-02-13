all:  defs.o udp_listen.o chord.o 
	g++ chord.o udp_listen.o defs.o -o listener -lpthread
	
defs.o: defs.cpp
	g++ -c defs.cpp
        

udp_listen.o: udp_listen.cpp
	g++ -c udp_listen.cpp 

chord.o: chord.cpp
	g++ -c chord.cpp
	

clean:
	rm -rf *o listener

