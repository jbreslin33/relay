#include "reader.h"

Reader::Reader()
{


        //std::thread reader (&Reader::readData);     
      //std::thread t5(&foo::bar, &f);
      	std::thread reader(&Reader::readData, this);
        
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


