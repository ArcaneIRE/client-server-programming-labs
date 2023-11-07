#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"

int main (int argc, char *argv[]) {
	char recvBuffer[BUFSIZE]; // I/O buffer
	int numBytes = 0;

	if (argc < 3) { // test for correct num of arguments
		DieWithUserMessage("Parameter(s)", "<Server Address> <Server Port>");
	}

	char *servIP = argv[1];

	in_port_t servPort = atoi(argv[2]); // First arg: server IP (dotted quad)


	// Create a reliable, stream socket using TCP
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INET = IPv4, IPPROTO_TCP = TCP
	// socket is identified by an integer

	// Construct the server address structure
	struct sockaddr_in servAddr; // Server address
	memset(&servAddr, 0, sizeof(servAddr)); // Zero out struct
	servAddr.sin_family = AF_INET; // Use IPv4 address format
	// Convert address
	inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr); // convert IPv4 into binary
	// pton = presentation to number or something
	servAddr.sin_port = htons(servPort); // Server port to use. htons = Host to network
	// Checks if your processor is little endian or big endian and uses the little 
	// endian format which is networking standard

	// Establish the connection to the echo server
	connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr));

	// OS has received the info and is now waiting for the program to receive it
	numBytes = recv(sock, recvBuffer, BUFSIZE - 1, 0); //  put the info in a buffer of 
	// certain size
	recvBuffer[numBytes] = '\0'; // Terminate the string
	fputs(recvBuffer, stdout); // Print the receive buffer to stdout

	fputc('\n', stdout); // Print a final linefeed

	close(sock);

	exit(0);
}
