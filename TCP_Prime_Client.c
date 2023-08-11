#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80
#define PORT 2000
#define SA struct sockaddr

void func(int connfd)
{
    char buff[MAX];
    
        bzero(buff, MAX);

	// read the message from client and copy it in buffer
	printf("Enter number to be checked: ");
	scanf("%s", buff);
	
        // and send that buffer to client
        write(connfd, buff, sizeof(buff));
        printf("%s\n", buff);
        
        bzero(buff, MAX);
        
        //Get response from Server. Whether string sent is palindrome or not.
	read(connfd, buff, sizeof(buff));
        printf("%s", buff);
}

// Driver function
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) == -1)
    {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}
