/* Client code in C */
#include <sys/types.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//void tryport(uint16_t port)
//{
   /* struct sockaddr_in addr;*/
	//int Res;
	//printf("Creating a socket...\n");
	//int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//if (-1 == fd)
	//{
		//perror("cannot create socket");
		//exit(EXIT_FAILURE);
	//}

	//memset(&addr, 0, sizeof(addr));

	//addr.sin_family = AF_INET;
	//addr.sin_port = htons(port);
	//Res = inet_pton(AF_INET, "192.168.0.2", &addr.sin_addr);

	//if (0 > Res)
	//{
		//perror("error: first parameter is not a valid address family");
		//close(fd);
		//exit(EXIT_FAILURE);
	//}
	//else if (0 == Res)
	//{
		//perror("char string (second parameter does not contain valid ipaddress)");
		//close(fd);
		//exit(EXIT_FAILURE);
	//}

	//printf("Attempting to connect to port %i...\n",port);
	//if (-1 == connect(fd, (struct sockaddr *)&addr, sizeof(addr)))
	//{
		//perror("connect failed");
		//close(fd);
		////exit(EXIT_FAILURE);
	//}
	//else
	//{
		//printf("Successfully connected to port %i\n",port);
		//exit(EXIT_SUCCESS);
	//}

	////printf("Calloc a buffer for the telegram...\n");
	////const int telegramBytes=1;
	////uint8_t *payload = (uint8_t *) calloc(2,telegramBytes); // Two bytes
	////payload[0] = 0xAB;
	////payload[1] = 0xCD;
	
	////printf("Writting the telegram\n");
	////ssize_t foo = write(fd,payload,telegramBytes);

	////printf("Teardown\n");
	//(void) shutdown(fd, SHUT_RDWR);
	////free(payload);
	//close(fd);
	/*//return EXIT_SUCCESS;*/
//}

//void dothereisnotry(uint16_t port)
//{
	//struct sockaddr_in addr;
	//int Res;
	//printf("Creating a socket...\n");
	//int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//if (-1 == fd)
	//{
		//perror("cannot create socket");
		//exit(EXIT_FAILURE);
	//}

	//memset(&addr, 0, sizeof(addr));

	//addr.sin_family = AF_INET;
	//addr.sin_port = htons(port);
	//Res = inet_pton(AF_INET, "192.168.0.2", &addr.sin_addr);

	//if (0 > Res)
	//{
		//perror("error: first parameter is not a valid address family");
		//close(fd);
		//exit(EXIT_FAILURE);
	//}
	//else if (0 == Res)
	//{
		//perror("char string (second parameter does not contain valid ipaddress)");
		//close(fd);
		//exit(EXIT_FAILURE);
	//}

	//printf("Attempting to connect to port %i...\n",port);
	//if (-1 == connect(fd, (struct sockaddr *)&addr, sizeof(addr)))
	//{
		//perror("connect failed");
		//close(fd);
		//exit(EXIT_FAILURE);
	//}
	//else
	//{
		//printf("Successfully connected to port %i\n",port);
	//}

	//printf("Calloc a buffer for the telegram...\n");
	//const int telegramBytes=100;
	//uint8_t *payload = (uint8_t *) calloc(1,telegramBytes);
	//for(int i=0; i<telegramBytes; i++)
	//{
		//payload[i] = 0xFF;
	//}
	//payload[0] = 0xAA;
	//payload[99] = 0xBB;
	////payload[0] = 0xFF;
	////payload[1] = 0xFF;
	////payload[2] = 0xFF;
	////payload[3] = 0xFF;

	//printf("Sending the telegram\n");
	//if ( send( fd, payload, telegramBytes, 0 )
			//!= telegramBytes )
	//{
		//printf( "TCP sending failed\n" );		
	//}

	//printf("Teardown\n");
	//(void) shutdown(fd, SHUT_RDWR);
	//free(payload);
	//close(fd);
	////return EXIT_SUCCESS;
//}

#define PROFINET 0x8892

void send_profinet(void)
{
	printf("Creating a socket...\n");
	int fd = socket(AF_PACKET, SOCK_DGRAM, PROFINET); // maybe this PROFINET is the recieve type?

	if (-1 == fd)
	{
		perror("cannot create socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_ll addr;
	memset(&addr, 0, sizeof(addr));
	addr.sll_family = AF_PACKET; // ALWAYS AF_PACKET
	//addr.sll_protocol = PROFINET; 
	addr.sll_ifindex = 0; // 0: any interface
	//addr.sll_hatype = ARPHRD_ETHER;
	//addr.sll_pkttype = PACKET_MULTICAST;
	addr.sll_halen = 6;
	addr.sll_addr[0] = 0x00; // MAC address of siemens destination
	addr.sll_addr[1] = 0x1F;
	addr.sll_addr[2] = 0xF8;
	addr.sll_addr[3] = 0x09;
	addr.sll_addr[4] = 0x93;
	addr.sll_addr[5] = 0xE0;

	printf("Attempting to connect...");
	if (-1 == connect(fd, (struct sockaddr *)&addr, sizeof(addr)))
	{
		perror("connect failed...\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully connected!\n");
	}

}


int main(void)
{
	//// Brute force port scanning
	//for(uint16_t port=5189; port<0xFFFF; port++)
	//{
		//tryport(port);
	//}
	while(1)
	{
		//dothereisnotry(102);
		send_profinet();
	}
	//dothereisnotry(3843);
	//dothereisnotry(5188);
	return EXIT_SUCCESS;
	
}
