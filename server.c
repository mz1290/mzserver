#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> /* close, write, read */

#define	PORT		8080
#define	BUFFER_SIZE	30000


int
main(void)
{
	int server_fd;
	struct sockaddr_in address = {0};
	int addrlen = sizeof(address);

	/*
	 * Create a TCP socket.
	 * Analogy: requesting a telephone line from phone company.
	 */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		printf("Cannot create socket\n"); 
		return (1);
	}

	/*
	 * Identify/name/bind the socket.
	 * Analogy: assigning a phone number to the requested line.
	 */
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = htonl(INADDR_ANY); 
	address.sin_port = htons(PORT); 
	if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
		printf("Bind failed\n"); 
		return (1); 
	}

	/* Wait for incoming connection */
	if (listen(server_fd, 10) < 0) {
		printf("Failed in listen\n"); 
		return (1);
	}

	while (1) {
		int new_socket;
		long valread;
		char buffer[BUFFER_SIZE] = {0};
		char *hello = "Hello from server";

		printf("\n+++++++ Waiting for new connection ++++++++\n\n");

		if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
		    (socklen_t*)&addrlen)) < 0) {
			printf("Failed in accept\n");
			return (1);
		}

		/* Send and receive messages */
		valread = read(new_socket, buffer, BUFFER_SIZE);
		printf("%s\n", buffer);

		write(new_socket , hello , strlen(hello));

		printf("------------------Hello message sent-------------------"
		    "\n");

		/* Close the socket */
		close(new_socket);
	}

	return (0);
}