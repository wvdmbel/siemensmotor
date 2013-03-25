/* Client code in C */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	struct sockaddr_in stSockAddr;
	int Res;
	int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (-1 == SocketFD)
	{
		perror("cannot create socket");
		exit(EXIT_FAILURE);
	}

	memset(&stSockAddr, 0, sizeof(stSockAddr));

	stSockAddr.sin_family = AF_INET;
	stSockAddr.sin_port = htons(1100);
	Res = inet_pton(AF_INET, "192.168.0.2", &stSockAddr.sin_addr);

	if (0 > Res)
	{
		perror("error: first parameter is not a valid address family");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}
	else if (0 == Res)
	{
		perror("char string (second parameter does not contain valid ipaddress)");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}

	printf("Attempting to connect to server\n");
	if (-1 == connect(SocketFD, (struct sockaddr *)&stSockAddr, sizeof(stSockAddr)))
	{
		perror("connect failed");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}

	printf("Calloc a buffer for the telegram\n");
	const int telegramBytes=1;
	uint8_t *payload = (uint8_t *) calloc(2,telegramBytes); // Two bytes
	payload[0] = 0xAB;
	payload[1] = 0xCD;
	
	printf("Writting the telegram\n");
	ssize_t foo = write(SocketFD,payload,telegramBytes);

	printf("Teardown\n");
	(void) shutdown(SocketFD, SHUT_RDWR);
	free(payload);
	close(SocketFD);
	return EXIT_SUCCESS;
}
