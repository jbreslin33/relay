#ifndef CLIENT_H
#define CLIENT_H

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


class Client
{
	private:
  	
	int sock;
  	struct sockaddr_in sa;
  	int bytes_sent;

	public:
	
	char buffer[200];

	Client();

	//void sendToServer(std::string m)
	void sendToServer(std::string s);

};

#endif
