#ifndef RELAY_H
#define RELAY_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

class Relay
{
	private:
  	
  	//int bytes_sent;

	public:
	
	Relay();
	void log(std::string s);
	void sendToServer(std::string s);
	void readData();
	

	//Berkeley Sockets all
	int sock;
        struct sockaddr_in sa;
        char buffer[1024];
        ssize_t recsize;
        socklen_t fromlen;
	
	//Berkeley Sockets send
	int bytes_sent;
	

	std::string mMessage;
	u_short mListenPort;

};

#endif
