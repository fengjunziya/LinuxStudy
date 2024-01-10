.PHONY:all
all:client mutiServer

client:client.cxx
	g++ -o $@ $^ -std=c++11
mutiServer:server.cxx
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f client mutiServer