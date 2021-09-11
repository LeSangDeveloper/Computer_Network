#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define PORT 5942
#define BUFFER_LENGTH 1024

int main(int argc, char *argv[]) {
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "hello from the client";
	char buffer[BUFFER_LENGTH] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\n Invalid address/ Address not supported \n");
		return -1;
	}
	
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("Connection failed \n");
		return -1;
	}

	send(sock, hello, strlen(hello), 0);
	printf("Hello message sent\n");
	valread = read(sock, buffer, BUFFER_LENGTH);
	printf("%s\n", buffer);
	return 0;
}
