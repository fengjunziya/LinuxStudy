.PHONY:all
all:Client Server

Client:Client.cpp
	g++ -o $@ $^ -std=c++11
Server:Server.cpp
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm Client Server
	unlink fifo.ipc