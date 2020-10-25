/*SERVER:
1 - Initialize Winsock.
2 - Create a socket.
3 - Bind the socket.
4 - Listen on the socket for a client.
5 - Accept a connection from a client.
6 - Receive and send data.
7 - Disconnect.
*/
#pragma comment(lib, "ws2_32.lib")

#include <stdio.h>
#include <Winsock2.h>
#include <Ws2tcpip.h>

#define DEFAULT_PORT "2000"

int main(int argc, char const *argv[])
{
	struct addrinfo *result = NULL,
		*ptr = NULL,
	     hints;

	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	WSADATA wsaData;
	int iResult;
	SOCKET ConnectSocket = INVALID_SOCKET;
	ptr = result;

	//inicialização do winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

	if(iResult != 0)
	{
		printf("error - WSAStartup!\n");
		return 1;
	}

	//resolve o endereço da porta e do servidor
	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if(iResult != 0)
	{
		printf("error - getaddrinfo!\n");
		WSACleanup();
		return 1;
	}

	//familia 
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)	
    {
    	printf("error - ConnectSocket!\n");
    	freeaddrinfo(result);
    	WSACleanup();
    	return 1;
	}

	return(0);
}