#include "relay.h"

#include <fstream>

Relay::Relay()
{

}

void Relay::log(std::string s)
{
	std::ofstream ofs;
  	ofs.open ("relay.log", std::ofstream::out | std::ofstream::app);
  	ofs << s << std::endl;
  	ofs.close();
}

