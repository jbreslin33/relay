#include <iostream>    
#include <thread>        

#include "relay.h"       

void readData(Relay* relay)
{
	while (true) 
	{
		//declare string
		std::string sin;

		//set any data coming in to var sin
    		std::cin >> sin;

		//check to see if this is a 2 first connection
		/*
	        if (sin.compare(0,1,"2") == 0)
		{
			//first connection so append listen port
			sin.append(relay->mListenPort);		
		}
		*/


		//set global msg var to sin
    		relay->mMessage = sin;
  	}
}

void writeData(Relay* relay)
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
 
  			strcpy(buffer, "hello to server from client!");
 
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
/*
void readSocketData(Relay* relay)
{
	while (true) 
	{
		//relay->mListenSocket->readData();
		//relay->readData();
		//relay->log("read Data");
	}
}
*/

int main(void)
{
	Relay relay;

	std::thread reader       (readData, &relay);     
	std::thread writer       (writeData, &relay);     
	//std::thread socketReader (readSocketData, &relay);     
	reader.join();
	writer.join();
	//socketReader.join();

  	return 0;
}
