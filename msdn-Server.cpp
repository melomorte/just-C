// Server.
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Passos para criar um socket-server.
// - Inicializar winsock.
// - Criar um socket.
// - Bind o socket.
// - Escutar o socket do client.
// - Aceitar a conexao do client.
// - Receber e enviar dados.
// - Disconectar.
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Diretivas.
#ifndef WIN32_LEAN_AND_MEAN			// Esta diretiva e necessaria pois o header windows.h contem a winsock2,
#define WIN32_LEAN_AND_MEAN			// fazendo com que os dois headers entrem em conflito caso windows.h seja,
#endif 								// definido como um header.
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Declaracao dos headers.
#include <stdio.h> 					// header para manipular I/O.
#include <winsock2.h> 				// header para criacao e manipulacao de sockets.
#include <ws2tcpip.h>				// Este header deve ser declarado obrigatoriamente apos winsock2.h.
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Linkagem da DLL ws2_32.lib.
#pragma comment(lib, "Ws2_32.lib")	// Pragma e ultilizado para linkagens externa.
									// a lib Ws2_32.lib e uma dll essencial para a criacao.
									// e manipulacao de sockets no ambiente windows.
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Definindo macros.
#define DEFAULT_BUFLEN 512			// Vai guardar a quantidade de bytes suportada pelo buffer.
#define DEFAULT_PORT 27015			// Defini o numero da porta a ser usada.
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Declaracao das funcoes.
void createSock();
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcao main.
int main(){
	puts("...Server Inicializando...\n");

	createSock();

	puts("...socket encerrado...");

	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcao createSock.
void createSock(){
	// Declaracao de variaveis.
	WSADATA wsaData;					// Cotem informacoes sobre a implementacao, do windows socket.

	int iResult = 0;					// Guarda o valor de WSAStartup e realiza o teste de erros.

	SOCKET sock = INVALID_SOCKET;		// Cria uma variavel para o socket com o valor de erro, se o socket for,
										// criado com sucesso o valor sera reescrito.

	int closeSock = 0;					// Cria uma variavel para guardar o valor de closesocket().

	struct sockaddr_in saServer;		// Estrutura utilizada em bind().

	hostent* localHost;					// Especifica o localhost que sera utilizado.

	char* localIP;						// Especifica um ponteiro com o endereco IP que sera usado.

	//int iListen = 0;					// listem e utilzado para escutar as requisicoes e conectar o client ao server.

	SOCKET acceptSock;

	//int recvbuflen = DEFAULT_BUFLEN;	// Especifica o tamanho em bytes que a funcao espera.
	const char *sendData = "Hello world!";	// Envia esses dados ao client.
	//char recvData[DEFAULT_BUFLEN] = "";	// Espera retorno de dados do client.

	// Parametros da funcao socket.
	// iremos colocar os parametros aqui para facilitar a alteracao dos mesmos caso seja necessario.
	int iAf = 2;			// 2 = AF_INET.
	int iType = 1;			// 1 = SOCK_STREAM.
	int iProtocol = 6;		// 6 = IPPROTO_TCP.

	// Inicializando o socket.
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData); 	// Inicia o uso da Ws2_32.dll, para comecar a comunicacao.
													// Makeword realiza a requisicao para a versao 2.2
													//da winsock no sistema.
	if(iResult != 0){								// Realiza um teste de erros, se a funcao retornar,
		puts("Erro - WSAStartup()\n");				// um valor diferente de 0, e porque houve um erro.
		//return 1;
	}

	// Criando o socket.
	sock = socket(iAf, iType, iProtocol);			// Cria o socket.
	if(sock == INVALID_SOCKET){						// Caso a funcao de errado, o valor nao sera sobre escrito.
		puts("Erro - socket()\n");
		//return 1;
	}

	// Obtem as infrmacoes do local host.
	localHost = gethostbyname("");
	localIP = inet_ntoa(*(struct in_addr *)*localHost->h_addr_list);

	// Define a estrutura sockaddr.
	//sockaddr_in saServer;
	saServer.sin_family = AF_INET;							// Define qual sera o protocolo usado.
	saServer.sin_addr.s_addr = inet_addr("127.0.0.1");		// Especifica o IP.
	saServer.sin_port = htons(2000); 						// Espefcifica a porta que sera usada.

	// Criando o bind.
	iResult = bind(sock, (SOCKADDR *) &saServer, sizeof (saServer));		// O bind associa um local de endereco ao socket.
	if(iResult != 0){														// Faz o teste de erros.
		puts("Erro - bind()\n");
		//return 1;
	}

	// Criando a funcao listen.
	if(listen(sock, SOMAXCONN) == SOCKET_ERROR){			// Coloca o socket em modo de escuta e aguarda requisicoes.
		puts("Erro - listen()\n");							// SOMAXCONN - e usado para definir o comprimento da fila de conexoes pendentes.
		//return 1;
	}

	// Criando a funcao connect.
	iResult = connect(sock, (SOCKADDR*) &saServer, sizeof(saServer));	// Realiza a conexao de acordo com a struct.
	if(iResult != 0){													// Realiza o teste de erros.
		puts("Erro - connect()\n");
		//return 1;
	}

	// Criando a funcao accept.
	acceptSock = accept(sock, NULL, NULL);	// Aceita a requisicao para conexao que estiver pendente.
	if(acceptSock == INVALID_SOCKET){
		puts("Erro - accept()\n");
		//return 1;
	}

	puts("Conectado com sucesso!\n");	// Se a conexao for feita com sucesso esta menssagem e exibida na tela.

	// Funcao send.
	// Esta funcao vai enviar uma menssagem para o client caso a conexao tenha ocorrido com sucesso.
	iResult = send(sock, sendData, (int)strlen(sendData), 0);
	if(iResult == SOCKET_ERROR){
		puts("Erro - send()\n");
		//return 1;
	}

	printf("bytes enviados %d\n", iResult);

	// Funcao shutdown.
	// a funcao shutdown desliga a coneccao pois nao tera mais dados a ser enviados.
	iResult = shutdown(sock, SD_SEND);
	if(iResult == SOCKET_ERROR){
		puts("Erro - shutdown()\n");
		//return 0;
	}

	// Finalizando o socket.

	closeSock = closesocket(sock);			// Finaliza a conexao do socket.
	if(closeSock != 0){						// Realiza o teste de erros.
		puts("Erro - closesocket()\n");
		//return 1;
	}

	iResult = WSACleanup();					// Esta funcao e utilizada para finalizar o WSAStartup e deve ser usada sempre que a mesma for inicializada.

	if(iResult != 0){						// Realiza o teste de erros.
		puts("Erro - WSACleanup()\n");
		//return 1;
	}

}
//------------------------------------------------------------------------------------------------------------------------------------------------------
