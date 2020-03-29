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
			//send to websocketd which will then forward to relay web browser
			//this needs to be done after processing by server....
      			std::cout << relay->mMessage << std::endl;

			//send to server for processing
			relay->sendToServer(relay->mMessage);

			//clear the msg for next time
      			relay->mMessage.clear();
    		}
  	}
}

void readSocketData(Relay* relay)
{
	while (true) 
	{

	}
}

int main(void)
{
	Relay relay;

	std::thread reader       (readData, &relay);     
	std::thread writer       (writeData, &relay);     
	std::thread socketReader (readSocketData, &relay);     
	reader.join();
	writer.join();

  	return 0;
}
