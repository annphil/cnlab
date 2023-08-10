#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    FILE *fp;
    int csd, n, ser, s, cli, cport, newsd;
    char name[100], rcvmsg[100], rcvg[100];
    struct sockaddr_in servaddr;
    
    printf("Enter the port");
    scanf("%d", &cport);
    csd = socket(AF_INET, SOCK_STREAM, 0);
    if (csd < 0)
    {
        printf("Error....\n");
        exit(0);
    }
    else
        printf("Socket is created\n");
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr =inet_addr("127.0.0.1");
    servaddr.sin_port = htons(cport);
    if (connect(csd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        printf("Error in connection\n");
    else
        printf("connected\n");
        
    printf("Enter the name file whose content is to be fetched by server\t");
    scanf("%s", name);
    
    send(csd, name, sizeof(name), 0);
    while (1)
    {
        s = recv(csd, rcvg, 100, 0);

        rcvg[s] = '\0';
        if (strcmp(rcvg, "error") == 0)
            printf("File is not available\n");
        if (strcmp(rcvg, "completed") == 0)
        {
            printf("File is transferred........\n");
            close(csd);
            break;
        }
        else
            fputs(rcvg, stdout);
        
    }
    return 0;
    close(csd);
}
