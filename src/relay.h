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

class Socket;

class Relay
{
	private:
  	
	int sock;
  	struct sockaddr_in sa;
  	int bytes_sent;

	public:
	
	Relay();
	void log(std::string s);
	void sendToServer(std::string s);
	
	char buffer[200];
	std::string mMessage;

	Socket* mListenSocket;

};

#endif
