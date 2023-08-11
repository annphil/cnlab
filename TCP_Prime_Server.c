#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

#define MAX 80
#define PORT 2000
#define SA struct sockaddr

void func(int connfd)
{
    char buff[MAX];
    int i, j, n, flag=1;
    
        bzero(buff, MAX);

        // read the number to be checked from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        
        n = atoi(buff);
        
        if(n%2==0)
        	flag = 0;
        else {
        	for(i=2; i<n; i++){
        		if (n%i ==0 ){
        			flag = 0;
        			break;
        		}        			
        	}
        }
        
        if (flag == 1)
        	write(connfd, "It is prime number\n", sizeof("It is a prime number"));
        else
        	write(connfd, "It is a non prime number\n", sizeof("It is a non prime number"));
        
}

// Driver function
int main()
{
    int sockfd, connfd, len;
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");

    // Function for chatting between client and server
    func(connfd);

    // After chatting close the socket
    close(sockfd);
}
