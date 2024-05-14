#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 30

typedef struct ListNode {
    int dest;       // Destination node
    int weight;     // Edge weight
    struct ListNode* next;  // Pointer to next node in the list
} ListNode;

typedef struct {
    ListNode* adjList[MAX_NODES];  // Array of adjacency lists for nodes
    int numNodes;                  // Number of nodes in the graph
} Graph;

ListNode* addEdge(ListNode* head, int dest, int weight) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = head;  // Insert at the beginning of the list
    head = newNode;
    return head;
}

void printGraph(ListNode* adjMat[]) {
    ListNode* current;
    for (int i = 0; i < MAX_NODES; i++) {
        printf("%d", i);
        if (adjMat[i] == NULL) {
            printf(" -> X");
        }
        else {
            current = adjMat[i];
            while (current != NULL) {
                printf(" -> ");
                printf("%d", current->dest);
                current = current->next;
            }
        }
        printf("\n");
    }
}

void dijkstra(ListNode* adjList[], int source, int dest) {
    int dist[MAX_NODES];
    int pred[MAX_NODES];
    int visited[MAX_NODES] = {0};

    // Initialize distances to infinity and predecessor to -1
    for (int i = 0; i < MAX_NODES; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[source] = 0;

    // Find shortest path using Dijkstra's algorithm
    for (int count = 0; count < MAX_NODES; count++) {
        // Find node with minimum distance (not yet visited)
        int minDist = INT_MAX;
        int u = -1;
        for (int i = 0; i < MAX_NODES; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) {
            break;  // No more reachable nodes
        }

        visited[u] = 1;

        // Update distances of adjacent nodes
        ListNode* current = adjList[u];
        while (current != NULL) {
            int v = current->dest;
            int weight = current->weight;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;
            }
            current = current->next;
        }
    }

    // Print shortest path from source to destination
    printf("Shortest path from %d to %d: ", source, dest);
    if (dist[dest] == INT_MAX) {
        printf("No path exists\n");
    } else {
        int node = dest;
        while (node != -1) {
            printf("%d", node);
            node = pred[node];
            if (node != -1) {
                printf(" <- ");
            }
        }
        printf("\n");
    }
}

int main() {

    ListNode* adjMat[MAX_NODES];
    for (int i = 0; i < MAX_NODES; i++) {
        adjMat[i] = NULL;
    };

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
            adjMat[start] = addEdge(adjMat[start], end, length); 
        } 
    }

    fclose(file);

    printGraph(adjMat);
    int source = 0;
    int dest = 0;
    printf("Enter source and destination: \n");
    scanf("%d %d", &source, &dest);
    dijkstra(adjMat, source,dest);

    return 0;
}