#include <stdio.h>
#include <string.h>

#define MAX_EDGES 100
#define MAX_NODES 30

typedef struct{
    int source;   // Source node of the edge
    int destination;  // Destination node of the edge
    int weight;   // Weight (or cost) of the edge
} Edge ;

int main (void) {

    Edge edges[MAX_EDGES];

    int num_edges = 0;
    int start = 0;
    int end = 0;
    int length = 0;
    int s = 0;
        // Add directed edges with weights

    FILE *file = fopen("input", "r");

    while (s == 0) {
        fscanf(file, "%d %d %d", &start, &end, &length);
        if (start == -1) {
            s = 1;
        }
        else {
            edges[num_edges++] = (Edge){start, end, length}; 
        } 
    }

    fclose(file);
  
    // Print all edges
    printf("Edges of the graph:\n");
    for (int i = 0; i < num_edges; i++) {
        printf("Edge %d: %d -> %d (Weight: %d)\n", i, edges[i].source, edges[i].destination, edges[i].weight);
    }

    return 0;
}