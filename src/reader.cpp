#include "reader.h"

Reader::Reader()
{
	std::thread reader(&Reader::readData, this);
      	reader.join();
}


void Reader::setRelay(Relay* relay)
{
        this->mRelay = relay;
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
                this->mRelay->mMessage = sin;

                this->mRelay->sendToServer(this->mRelay->mMessage);
        }
}


