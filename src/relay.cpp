#include "relay.h"
#include "reader.h"
#include "writer.h"

Relay::Relay()
{
	Reader reader;
	Writer writer;

	reader.setRelay(this);
	writer.setRelay(this);
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

