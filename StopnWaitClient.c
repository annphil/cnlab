#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct packet{
    char data[1024];
}Packet;

typedef struct frame{
    int frame_kind; //ACK:0, SEQ:1 FIN:2
    int sq_no;
    int ack;
    Packet packet;
}Frame;

int main(int argc, char *argv[]){
    	int port, sockfd, n;
	printf("\nEnter port no: ");
	scanf("%d", &port);
	printf("Enter no of frames to be sent: ");
	scanf("%d", &n);
	struct sockaddr_in serverAddr;
	char buffer[1024];
	socklen_t addr_size;


	int frame_id = 0;
	Frame frame_send;
	Frame frame_recv;
	int ack_recv = 1;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	char iterationValue[50];
	//int len = sizeof(serverAddr);
	sprintf(iterationValue, "%d", n);
	sendto(sockfd, iterationValue, strlen(iterationValue), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	while(n!=0){
		
		if(ack_recv == 1){
			frame_send.sq_no = frame_id;
			frame_send.frame_kind = 1;
			frame_send.ack = 0;		
			printf("Enter Data: ");
			scanf("%s", buffer);
			strcpy(frame_send.packet.data, buffer);
			
			sendto(sockfd, &frame_send, sizeof(Frame), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
			printf("[+]Frame Sent\n");
		}
		int addr_size = sizeof(serverAddr);
		int f_recv_size = recvfrom(sockfd, &frame_recv, sizeof(frame_recv), 0 ,(struct sockaddr*)&serverAddr, &addr_size);
		
		if( f_recv_size > 0 && frame_recv.sq_no == 0 && frame_recv.ack == frame_id+1){
			printf("[+]Ack Received\n");
			ack_recv = 1;
		}else{
			printf("[-]Ack Not Received\n");
			ack_recv = 0;
		}	
  			
		frame_id++;
		n--;		
	}
	
	close(sockfd);
	return 0;
}
