// build as:
// g++ writer.cpp ipc-shim.c -o writer -I/usr/local/include -L/usr/local/lib/ -lnanomsg
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include "ipc-shim.h"

using namespace std;

#define IPC_SHMEM "/tmp/testnano"

int main(){

	cout << "> creating publish socket..." << endl;
	int socket = ipc_setupBroadcasterSocket(IPC_SHMEM);
	// int socket = ipc_setupPubSinkSocket(IPC_SHMEM);

	cout << "> socket " << socket << endl;

	if (socket >= 0)
	{
		cout << "> start feeding data" << endl;

		int frameSize = 360*240*4;
		int frameNo = 0;
		void *frame = malloc(frameSize);

		while (1)
		{
			
			for (int i = 0; i < frameSize; ++i)
				((char*)frame)[i] = (char)i%255;

			int ret = ipc_sendFrame(socket, frameNo, frame, frameSize);
			
			if (ret > 0)
				cout << "> pushed frame "<< frameNo << endl;
			else
				cout << "> error pushing frame " << frameNo << ": " 
					<< ipc_lastError() << " (" << ipc_lastErrorCode() << ")" << endl;

			frameNo++;
			usleep(100000);

			std::cin.get();
		}
	}
	else
		cout << "> error creating socket: " << ipc_lastError() << " (" << ipc_lastErrorCode() << ")" << endl;

	return 0;
}