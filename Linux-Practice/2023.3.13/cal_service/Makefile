.PHONY:all
all:client sserver
client:cal_client.cc
	g++ -o $@ $^ -std=c++11
sserver:cal_server.cc
	g++ -o $@ $^ -std=c++11 -lpthread
.PHONY:clean
clean:
	rm -f client sserver