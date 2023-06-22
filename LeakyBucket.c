#include<stdio.h>

void main(){
	int bucketSize, bucketStatus=0, n, outputRate, packetSize, input;
	printf("Enter bucket size: ");
	scanf("%d", &bucketSize);
	printf("Enter output rate: ");
	scanf("%d", &outputRate);
	printf("Enter no. of inputs: ");
	scanf("%d", &n);
	
	while(n!=0){
		printf("\n\nEnter incoming packet size: ");
		scanf("%d", &packetSize);
		int dropped = 0;
		input = packetSize;
		if (packetSize > (bucketSize - bucketStatus)){
			dropped = packetSize - (bucketSize - bucketStatus);
			input = packetSize - dropped;
		}
		printf("No of dropped packets: %d", dropped);
		bucketStatus += input - outputRate;	
		printf("\nBucket status after outgoing: %d", bucketStatus);
	}
}
