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
#define PORT 8081
#define SA struct sockaddr

void func(int connfd)
{
    char buff[MAX];
    int i, j, n, flag=1;
    // infinite loop for chat
    
        bzero(buff, MAX);

        // read the string to be checked from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        
        n = strlen(buff);
        for(i=0; i<n; i++){
        	buff[i] = tolower(buff[i]);
        }
                
        n = strlen(buff);
        for (i=0, j=n-1 ; i<n/2; i++, j--){
        	if (buff[i] != buff[j]){
        		flag = 0;
        		break;
        	}        		
        }
        //Sending result to client
        if( flag == 1)
		write(connfd, "y", sizeof("y"));
	else 
		write(connfd, "n", sizeof("n"));
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
