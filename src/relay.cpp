#include "relay.h"

#include <fstream>

Relay::Relay()
{
	//mListenSocket = new Socket(this,0);
	mListenPort = 0;

	//setup listen socket server
        //Berkeley Sockets

        memset(&sa, 0, sizeof sa);
        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = htonl(INADDR_ANY);
        sa.sin_port = htons(0);
        fromlen = sizeof sa;

        sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (bind(sock, (struct sockaddr *)&sa, sizeof sa) == -1)
        {
                perror("error bind failed");
                close(sock);
                exit(EXIT_FAILURE);
        }

        if (getsockname(sock, (struct sockaddr *)&sa, &fromlen) == -1)
        {
                log("error on getsockname");
        }
        else
        {
                log(std::to_string(ntohs(sa.sin_port)));
        }

}

void Relay::sendToServer(std::string s)
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

void Relay::readData()
{
        recsize = recvfrom(sock, (void*)buffer, sizeof buffer, 0, (struct sockaddr*)&sa, &fromlen);
        if (recsize < 0)
        {
                //fprintf(stderr, "%s\n", strerror(errno));
                log("message failed.");
                exit(EXIT_FAILURE);
        }
        else
        {
                log("received message");
        }
}

void Relay::log(std::string s)
{
	std::ofstream ofs;
  	ofs.open ("relay.log", std::ofstream::out | std::ofstream::app);
  	ofs << s << std::endl;
  	ofs.close();
}

