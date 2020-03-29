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
  	
	int sock;
  	struct sockaddr_in sa;
  	int bytes_sent;




	public:
	
	char buffer[200];

	Relay();

	void sendToServer(std::string s);
        
	std::string mMessage;

};

#endif
