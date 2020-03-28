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

#include "client.h"

Client::Client()
{

}

void Client::sendToServer(std::string s)
{
		char cstr[s.size() + 1];
		strcpy(this->buffer, s.c_str());	// or pass &s[0]

		sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  
		if (sock == -1) 
		{
      			printf("Error Creating Socket");
      			exit(EXIT_FAILURE);
		}

  		memset(&sa, 0, sizeof sa);
  
  		sa.sin_family = AF_INET;
 
  		sa.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  		sa.sin_port = htons(7654);
 
  		bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
  		if (bytes_sent < 0) 
		{
    			printf("Error sending packet: %s\n", strerror(errno));
    			exit(EXIT_FAILURE);
	  	}
 
  		close(sock); 
	}


