#include <stdio.h>
#include <winsock2.h>

int main(){
    char buffer[255];
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,0), &wsa);
    
    struct sockaddr_in caddr;
    struct sockaddr_in saddr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port = htons(5000)
    };

    int server = socket(AF_INET, SOCK_STREAM, 0);
    int client;
    int csize = sizeof caddr;

    bind(server, (struct sockaddr *) &saddr, sizeof saddr);

    listen(server, 5);

    while(1)
    {
        client = accept(server, (struct sockaddr *) &caddr, &csize);
        recv(client, buffer, sizeof buffer, 0);

        //send(client, buffer, x, 0);

        puts(buffer);
        fflush(stdout);
        
        closesocket(client);
    }


    return (0);
}
