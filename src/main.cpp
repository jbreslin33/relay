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

#include "client.h"         // std::chrono::seconds


std::string msg;

void readData()
{
	while (true) 
	{
		//declare string
		std::string sin;

		//set any data coming in to var sin
    		std::cin >> sin;

		//set global msg var to sin
    		msg = sin;
  	}
}

void writeData(Client* client)
{
	while (true) 
	{
    		//std::lock_guard<std::mutex> lock{msg_mutex};
    		if (msg.length() > 0) 
		{
			//send to websocketd which will then forward to client web browser
			//this needs to be done after processing by server....
      			std::cout << msg << std::endl;

			//send to server for processing
			client->sendToServer(msg);

			//clear the msg for next time
      			msg.clear();
    		}
  	}
}

int main(void)
{
	Client client;

	std::thread reader (readData);     
	std::thread writer (writeData, &client);     
	reader.join();
	writer.join();

	//client->sendToServer();
  	return 0;
}
