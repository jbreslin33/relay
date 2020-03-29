#include "writer.h"

Writer::Writer()
{

        std::thread writer(&Writer::writeData, this);
        writer.join();
}

void Writer::setRelay(Relay* relay)
{
	this->mRelay = relay;
}

void Writer::writeData()
{
        while (true)
        {
                if (this->mRelay->mMessage.length() > 0)
                {
                        //send to websocketd which will then forward to relay web browser
                        //this needs to be done after processing by server....
                        std::cout << this->mRelay->mMessage << std::endl;

                        //send to server for processing
                        //relay->sendToServer(msg);
                        this->mRelay->sendToServer(this->mRelay->mMessage);


                        //clear the msg for next time
                        this->mRelay->mMessage.clear();
                }
        }
}




