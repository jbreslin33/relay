#include "reader.h"

Reader::Reader()
{

	//Relay relay;

        std::thread reader (this->readData);     
        reader.join();
}

void Reader::readData()
{
        while (true)
        {
                //declare string
                std::string sin;

                //set any data coming in to var sin
                std::cin >> sin;

                //set global msg var to sin
                this->msg = sin;
        }
}


