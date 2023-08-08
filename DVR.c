#include <stdio.h>
#include <stdlib.h> 
#include <limits.h>

struct Link{			//Link
	int hop, dest, wt;
	};

struct Network{
	int H, L;
	struct Link* link;
	};

void main(){
	int H, L, S, i, j, dist[H];
	printf("Distance Vector Routing using Bellman Ford Algorithm : \nEnter number of hops\n"); 
	scanf("%d", &H);
	printf("Enter number of Links\n");
	scanf("%d",&L);
	printf("Enter the source \n");
	scanf("%d",&S);

	struct Network* n = (struct Network*) malloc(sizeof(struct Network)); // create network
	n->H = H;
	n->L = L; ;
	n->link= (struct Link*) malloc( n->L * sizeof(struct Link ) );
	for(i=0; i<L; i++){	// source, destination and weight
		printf("\nLink %d enter source, destination and weight \n", i+1);
		scanf("%d",&n->link[i].hop);
		scanf("%d",&n->link[i].dest);
		scanf("%d",&n->link[i].wt);
		}
	for (i = 0; i < H; i++)
		dist[i]= INT_MAX; 	// Initialize all distances to INT_MAX
	dist[S] = 0;		// distance from source to source is zero
	for (i = 1; i < H; i++){
		for (j = 0; j < L; j++){
			int u = n->link[j].hop;
			int v = n->link[j].dest;
			int wt = n->link[j].wt; 
			if (dist[u] + wt < dist[v]) 	// distance updation
				dist[v] = dist[u] + wt;
			}
	}

	for (j = 0; j < L; j++){
		int u = n->link[j].hop;
		int v = n->link[j].dest;
		int wt = n->link[j].wt; 
		if (dist[u] + wt < dist[v]) 	
			printf("Network contains negative weight cycle\n");
		}

	printf("\nHop\tDistance from source\n");
	for (i= 0; i < H; i++){
		printf("%d \t %d\n", i, dist[i]);
		}
	}
