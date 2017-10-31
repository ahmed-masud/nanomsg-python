// build as:
// g++ reader.cpp ipc-shim.c -o reader -I/usr/local/include -L/usr/local/lib/ -lnanomsg
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "ipc-shim.h"

using namespace std;

#define IPC_SHMEM "/tmp/testnano"

int main(){

	cout << "> creating subscribe socket..." << endl;
	int socket = ipc_setupListenerSocket(IPC_SHMEM);
	// int socket = ipc_setupSubSourceSocket(IPC_SHMEM);

	cout << "> socket " << socket << endl;

	if (socket >= 0)
	{
		cout << "> start feeding data" << endl;

		unsigned int frameSize = 360*240*4;
		unsigned int frameNo = 0;
		void *frame = malloc(frameSize);

		while (1)
		{
			
			int ret = ipc_readFrame(socket, &frameNo, frame, frameSize);
			
			if (ret > 0)
				cout << "> received " << ret << " bytes. frame #" << frameNo << endl;
			else
				cout << "> error pushing frame " << frameNo << ": " 
					<< ipc_lastError() << " (" << ipc_lastErrorCode() << ")" << endl;
		}
	}
	else
		cout << "> error creating socket: " << ipc_lastError() << " (" << ipc_lastErrorCode() << ")" << endl;


	return 0;
}