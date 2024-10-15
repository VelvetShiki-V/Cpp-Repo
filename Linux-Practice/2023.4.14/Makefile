.PHONY:all
all:sserver cclient
sserver:TCPServer.cc
	g++ -o $@ $^ -std=c++11
cclient:client.cc
	g++ -o $@ $^ -std=c++11
.PHONY:clean
clean:
	rm -f sserver cclient