.PHONY:all
all:udp_client udp_server
udp_client:udp_client.cpp
	g++ -o $@ $^ -std=c++11 -DDEBUG_NOTSHOW
udp_server:udp_server.cpp
	g++ -o $@ $^ -std=c++11 -DDEBUG_NOTSHOW
.PHONY:clean
clean:
	rm -f udp_client udp_server