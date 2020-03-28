#ifndef READER_H
#define READER_H

#include <iostream>
#include <thread>

class Reader 
{

	private:

		std::string msg;

	public:
	
		Reader();

		void readData();
};


#endif
