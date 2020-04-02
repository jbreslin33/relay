#include <iostream>    
#include <thread>        

#include "relay.h"       

void readWebSocketData(Relay* relay)
{
	while (true) 
	{
		//declare string
		std::string sin;

		//set any data coming in to var sin
    		std::cin >> sin;

		//check to see if this is a 2 first connection
	        if (sin.compare(0,1,"2") == 0)
		{
			//first connection so append listen port
			std::string port = std::to_string(relay->mListenPort); 
			while (port.size() < 5)
			{
				port.insert(0,"0");
			}

			sin.append(port);		
		}

		//set global msg var to sin
    		relay->mMessage = sin;
  	}
}

void writeSocketData(Relay* relay)
{
	while (true) 
	{
    		if (relay->mMessage.length() > 0) 
		{
			//berkeley client socket
  			int sock;
  			struct sockaddr_in sa;
  			int bytes_sent;
  			char buffer[200];
 
  			strcpy(buffer, relay->mMessage.c_str());
 
  			/* create an Internet, datagram, socket using UDP */
  			sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  			if (sock == -1) 
			{
      				/* if socket failed to initialize, exit */
      				printf("Error Creating Socket");
      				exit(EXIT_FAILURE);
  			}
 
  			/* Zero out socket address */
  			memset(&sa, 0, sizeof sa);
  
  			/* The address is IPv4 */
  			sa.sin_family = AF_INET;
 
   			/* IPv4 adresses is a uint32_t, convert a string representation of the octets to the appropriate value */
  			sa.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  			/* sockets are unsigned shorts, htons(x) ensures x is in network byte order, set the port to 7654 */
  			sa.sin_port = htons(7654);
 
  			bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
  			if (bytes_sent < 0) 
			{
    				printf("Error sending packet: %s\n", strerror(errno));
    				exit(EXIT_FAILURE);
  			}
 
  			close(sock); /* close the socket */


			//send to websocketd which will then forward to relay web browser
			//this needs to be done after processing by server....
      			//std::cout << relay->mMessage << std::endl;

			//send to server for processing
			//relay->sendToServer(relay->mMessage);

			//clear the msg for next time
      			relay->mMessage.clear();
    		}
  	}
}

void readSocketData(Relay* relay)
{
	int sock;
  	struct sockaddr_in sa;
  	char buffer[1024];
  	ssize_t recsize;
  	socklen_t fromlen;

  	memset(&sa, 0, sizeof sa);
  	sa.sin_family = AF_INET;
  	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	//relay->mListenPort = 8765;
  	//sa.sin_port = htons(relay->mListenPort);
        sa.sin_port = htons(0);
  	fromlen = sizeof sa;

  	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  	if (bind(sock, (struct sockaddr *)&sa, sizeof sa) == -1) 
	{
    		perror("error bind failed");
    		close(sock);
    		exit(EXIT_FAILURE);
  	}
	//relay->mListenPort = 8765;
	socklen_t len = sizeof(sa);
	if (getsockname(sock, (struct sockaddr *)&sa, &len) == -1)
	{
    		perror("getsockname");
	}
	else
	{
    		printf("port number %d\n", ntohs(sa.sin_port));
		relay->mListenPort = ntohs(sa.sin_port);
	}

  	for (;;) 
	{
    		recsize = recvfrom(sock, (void*)buffer, sizeof buffer, 0, (struct sockaddr*)&sa, &fromlen);
    		if (recsize < 0) 
		{
      			fprintf(stderr, "%s\n", strerror(errno));
      			exit(EXIT_FAILURE);
   		}
		relay->log(buffer);
    		printf("recsize: %d\n ", (int)recsize);
    		sleep(1);
    		printf("datagram: %.*s\n", (int)recsize, buffer);
  	}
}

int main(void)
{
	Relay relay;

	std::thread tReadWebSocketData (readWebSocketData, &relay);     

	std::thread tReadSocketData    (readSocketData, &relay);     
	std::thread tWriteSocketData   (writeSocketData, &relay);     
	
	tReadWebSocketData.join();
	tReadSocketData.join();
	tWriteSocketData.join();

  	return 0;
}
