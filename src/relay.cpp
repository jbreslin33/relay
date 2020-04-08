#include "relay.h"

#include <fstream>

Relay::Relay()
{


}

std::vector<std::string> Relay::split(std::string s, std::string delim)
{
        std::vector<std::string> stringVector;

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delim)) != std::string::npos)
        {
                token = s.substr(0, pos);
                stringVector.push_back(token);
                s.erase(0, pos + delim.length());
                //printf("e:%s\n",token.c_str());
        }

        return stringVector;
}


void Relay::log(std::string s)
{
	std::ofstream ofs;
  	ofs.open ("relay.log", std::ofstream::out | std::ofstream::app);
  	ofs << s << std::endl;
  	ofs.close();
}

