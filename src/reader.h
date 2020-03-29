#ifndef READER_H
#define READER_H

#include <iostream>
#include <thread>

#include "relay.h"

class Reader 
{

	private:

		Relay* mRelay;

	public:
	
		Reader();

		void readData();
		void setRelay(Relay* relay);
};


#endif
