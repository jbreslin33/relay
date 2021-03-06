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

		std::string delimiter = ",";

		std::vector<std::string> stringVector = relay->split(sin,delimiter);		

		if (stringVector.at(1).compare(0,1,"j") == 0)
		{
			std::string port = std::to_string(relay->mListenPort); 
			sin.append(port);		
			sin.append(",");
		}

		if (stringVector.at(1).compare(0,1,"p") == 0)
		{
			std::string port = std::to_string(relay->mListenPort); 
			sin.append(port);		
			sin.append(",");
		}

		//set global msg var to sin
    		relay->mWebSocketMessage = sin;
  	}
}

void writeSocketData(Relay* relay)
{
	while (true) 
	{
    		if (relay->mWebSocketMessage.length() > 0) 
		{
			//berkeley client socket
  			int sock;
  			struct sockaddr_in sa;
  			int bytes_sent;
  			char buffer[200];
 
  			strcpy(buffer, relay->mWebSocketMessage.c_str());
 
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

      			relay->mWebSocketMessage.clear();
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
        sa.sin_port = htons(0);
  	fromlen = sizeof sa;

  	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  	if (bind(sock, (struct sockaddr *)&sa, sizeof sa) == -1) 
	{
    		perror("error bind failed");
    		close(sock);
    		exit(EXIT_FAILURE);
  	}
	
	socklen_t len = sizeof(sa);

	if (getsockname(sock, (struct sockaddr *)&sa, &len) == -1)
	{
    		perror("getsockname");
	}
	else
	{
		relay->mListenPort = ntohs(sa.sin_port);
	}

  	for (;;) 
	{
    		recsize = recvfrom(sock, (void*)buffer, sizeof buffer, 0, (struct sockaddr*)&sa, &fromlen);
               	if (recsize > 0)
                {
			//end buffer with cap
                        buffer[recsize] = 0;
				
			//after processing above this needs to be sent to web via cout actually before when its a move to increase speed
			//Just straight up relay this to websocket i dont even know why we are setting mSocketMessage...
                       	relay->mSocketMessage = buffer;

                        //send to web browser
                       	std::cout << relay->mSocketMessage << std::endl;
                }
		//old stuff
    		if (recsize < 0) 
		{
      			//relay->(stderr, "%s\n", strerror(errno));
      			exit(EXIT_FAILURE);
   		}

		//relay->log(buffer);
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
