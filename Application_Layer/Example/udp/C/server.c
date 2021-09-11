#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>

#define PORT 8080
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
	int server_fd;
	struct sockaddr_in address, client_address;
	int addrlen = sizeof(address);

	char buffer[BUFFER_LENGTH] = {0};
	char exit_str[BUFFER_LENGTH] = "exit";

	char *hello = "Hello from server";
	
	if ((server_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("socket failed!");
		exit(EXIT_FAILURE);
	}

	memset(&address, 0, sizeof(address));
	memset(&client_address, 0, sizeof(client_address));

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	while (1) {
		memset(buffer, 0, sizeof(buffer));
		int n, len;
		len = sizeof(client_address);
		n = recvfrom(server_fd, (char *)buffer, BUFFER_LENGTH, MSG_WAITALL, (struct sockaddr *)&client_address, &len);
		buffer[n] = '\0';

		printf("%s\n", buffer);
		
		if (compare(buffer, exit_str) == 0) {
			printf("\n GOODBYE !!! \n");		
			return 0;
		}

//		printf("%d", (sendto(server_fd, hello, strlen(hello), MSG_CONFIRM, (struct sockaddr *) &client_address, len)));

		if (sendto(server_fd, hello, strlen(hello), MSG_CONFIRM, (struct sockaddr *) &client_address, len) == 0) {
			printf("send error!");
		}
		
	}

	return 0;
}
