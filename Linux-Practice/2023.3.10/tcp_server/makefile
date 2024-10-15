.PHONY:all
all:sserver client
sserver:tcp_server.cc
	g++ -o $@ $^ -std=c++11 -lpthread -DDEBUG_NOTSHOW 
client:tcp_client.cc
	g++ -o $@ $^ -std=c++11 -DDEBUG_NOTSHOW
.PHONY:clean
clean:
	rm -f sserver client