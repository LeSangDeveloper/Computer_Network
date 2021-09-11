#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>

#define PORT 5942
#define BUFFER_LENGTH 1024

int compare(char a[],char b[])
{
    int flag=0,i=0;  // integer variables declaration
    while(a[i]!='\0' &&b[i]!='\0')  // while loop
    {
       if(a[i]!=b[i])
       {
           flag=1;
           break;
       }
       i++;
    }
    if(flag==0)
   	 return 0;
    else
   	 return 1;
}


int main(int argc, char *argv[]) {
	int server_fd, new_socket = -2, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	char buffer[BUFFER_LENGTH] = {0};
	char exit_str[BUFFER_LENGTH] = "exit";
	char newline[BUFFER_LENGTH] = "\n";

	char *hello = "Hello from server\n";
	
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed!");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
	
	}

	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	
	int mark = 0;

	while (1) {
		memset(buffer, 0, sizeof(buffer));

//		if (new_socket == -2)
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}

		valread = read(new_socket, buffer, BUFFER_LENGTH);
		if (buffer[0] == '\n') {
			mark++;
		} else {
			printf("%s\n", buffer);
			mark = 0;
		}

		if (compare(buffer, exit_str) == 0) {
			printf("\n GOODBYE !!! \n");
			close(new_socket);
			return 0;
		}

		send(new_socket, hello, strlen(hello), 0);
//		printf("Hello message sent\n");

		close(new_socket);

	}

	return 0;
}
