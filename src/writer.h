#ifndef WRITER_H
#define WRITER_H

#include <iostream>
#include <thread>

#include "relay.h"

class Writer 
{

	private:
		Relay* mRelay;

	public:
	
		Writer();

		void writeData();
		void setRelay(Relay* relay);
};



#endif
