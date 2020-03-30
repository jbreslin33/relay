#include "socket.h"
#include "relay.h"


Socket::Socket(Relay* relay, int port)
{
	mRelay = relay;

        mPort = port;

        memset(&mSocketAddressIn, 0, sizeof mSocketAddressIn);
        mSocketAddressIn.sin_family = AF_INET;
        mSocketAddressIn.sin_addr.s_addr = htonl(INADDR_ANY);
        mSocketAddressIn.sin_port = htons(mPort);
        mFromLength = sizeof mSocketAddressIn;

        mSocketId = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (bind(mSocketId, (struct sockaddr *)&mSocketAddressIn, sizeof mSocketAddressIn) == -1)
        {
                perror("error bind failed");
                close(mSocketId);
                exit(EXIT_FAILURE);
        }

}

void Socket::readData()
{
        mReceivedMessageSize = recvfrom(mSocketId, (void*)mBuffer, sizeof mBuffer, 0, (struct sockaddr*)&mRemoteSocketAddressIn, &mFromLength);
        if (mReceivedMessageSize < 0)
        {
                //fprintf(stderr, "%s\n", strerror(errno));
		mRelay->log("message failed.");
                exit(EXIT_FAILURE);
        }
	else
	{
		mRelay->log("received message");
	}
	//mRelay->log("calling readData()");

        //printf("recsize: %d\n ", (int)mReceivedMessageSize);
        //printf("datagram: %.*s\n", (int)mReceivedMessageSize, mBuffer);

        //mNetwork->mServer->processData(mBuffer, mRemoteSocketAddressIn);
        //sleep(1);
}



