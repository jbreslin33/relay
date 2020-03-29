#ifndef SOCKET_H
#define SOCKET_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>


class Network;

class Socket
{
	public:
		Socket(Network* network, int port);
		void readData();

	private:
		Network* mNetwork;

		//Berkeley Sockets
        	int mSocketId;

        	struct sockaddr_in mSocketAddressIn;
        	struct sockaddr_in mRemoteSocketAddressIn;

        	char mBuffer[1024];
        	ssize_t mReceivedMessageSize;
        	socklen_t mFromLength;

        	int mPort;
};

#endif
