/*CLIENT:
1 - Initialize Winsock.
2 - Create a socket.
3 - Connect to the server.
4 - Send and receive data.
5 - Disconnect.
*/
#include <stdio.h>
#include <Winsock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA wsaData;
	int iResult;

	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(iResult != 0)
	{
		printf("error - WSAStartup\n");
		return 1;
	}
	
	printf("\tHello client!\n");

	return(0);
}
