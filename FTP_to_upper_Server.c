#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main()
{
    FILE *fp;
    int sd, newsd, ser, n, a, cli, pid, bd, port, clilen, i;
    char name[100], fileread[100], fname[100], ch, file[100], rcv[100];
    char temp[30];
    struct sockaddr_in servaddr, cliaddr;
    printf("Enter the port address\n");
    scanf("%d", &port);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
        printf("Cant create\n");
    else
        printf("Socket is created\n");
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    a = sizeof(servaddr);
    bd = bind(sd, (struct sockaddr *)&servaddr, a);
    if (bd < 0)
        printf("Cant bind\n");
    else
        printf("Binded\n");
    listen(sd, 5);
    clilen = sizeof(cliaddr);
    newsd = accept(sd, (struct sockaddr *)&cliaddr, &clilen);
    if (newsd < 0)
    {
        printf("Cant accept\n");
    }
    else
        printf("Accepted\n");
    n = recv(newsd, rcv, 100, 0);
    rcv[n] = '\0';
    fp = fopen(rcv, "r");
    if (fp == NULL)
    {
        send(newsd, "error", 5, 0);
        close(newsd);
    }
    else
    {
        while (fgets(fileread, sizeof(fileread), fp))
        {
            //Include <ctype.h> among header files
            char temp[30];
            for(i=0; i<strlen(fileread); i++) {
            	temp[i] = toupper(fileread[i]);
            }
            
            /*OR 
            Declare char temp[30]; outside the func with every other declaration but do 
            bzero(temp, sizeof()temp); in place of char temp[30]; like this
            //Include <ctype.h> among header files
            
            bzero(temp, sizeof(temp));
            for(i=0; i<strlen(fileread); i++) {
            	temp[i] = toupper(fileread[i]);
            }*/
            
            	
            if (send(newsd, temp, sizeof(fileread), 0) < 0)
            {
                printf("Can’t send file contents\n");
            }
        }
        if (!fgets(fileread, sizeof(fileread), fp))
        {
            // when file pointer reaches end of file, file transfer “completed” message is send to accepted client connection using newsd, socket file descriptor.                       
            send(newsd, "completed", sizeof("completed"), 0);
        }
        return (0);
    }
    close(sd);
    close(newsd);
}
