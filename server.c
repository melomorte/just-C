//#pragma ws2_32.lib

#include <stdio.h>
#include <winsock2.h>

int main(int argc, char const *argv[])
{
	printf("\tSERVER\n");

	WSADATA wsa;
	WSAStartup(MAKEWORD(2,0), &wsa);

	char buff[257];
	int x;

	struct sockaddr_in caddr;
	struct sockaddr_in saddr = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = htonl(INADDR_ANY),
		.sin_port = htons(5000)
	};

	int server = socket(AF_INET, SOCK_STREAM, 0);
	int client;
	int csize = sizeof(caddr);

	bind(server, (struct sockaddr *) &saddr, sizeof(saddr));

	listen(server, 5);

	while(1)
	{
		client = accept(server, (struct sockaddr *) &caddr, &csize);
		x = recv(client, buff, sizeof(buff), 0);

		send(client, buff, x, 0);

		puts(buff);
		fflush(stdout);
	}

	closesocket(client);

	return 0;
}