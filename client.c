#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> /* close, write, read */
#include <arpa/inet.h>

#define	PORT		8080
#define	BUFFER_SIZE	30000


int
main(void)
{
	int sock;
	struct sockaddr_in serv_addr = {0};
	int servlen = sizeof(serv_addr);
	char *hello = "Hello from client";
	long valread;
	char buffer[BUFFER_SIZE] = {0};

	/* Create TCP socket */
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		printf("Cannot create socket\n"); 
		return (1);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("Invalid address or address not supported\n");
		return (1);
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, servlen) < 0) {
		printf("Connection failed\n");
		return (1);
	}

	send(sock , hello, strlen(hello), 0);
	printf("Hello message sent\n");
	valread = read(sock, buffer, 1024);
	printf("%s\n", buffer);

	return (0);
}
