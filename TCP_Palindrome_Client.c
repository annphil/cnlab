#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80
#define PORT 8081
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int connfd)
{
    char buff[MAX];
    
        bzero(buff, MAX);

	// read the message from client and copy it in buffer
	printf("Enter string to be checked: ");
	scanf("%s", buff);
	
        // and send that buffer to client
        write(connfd, buff, sizeof(buff));
        
        bzero(buff, MAX);
        
        //Get response from Server. Whether string sent is palindrome or not.
	read(connfd, buff, sizeof(buff));
        if( strncmp("y", buff, 1) == 0 )
            printf("String is palindrome\n" );
        else if( strncmp("n", buff, 1) == 0 )
            printf("String is not palindrome\n" );    
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
