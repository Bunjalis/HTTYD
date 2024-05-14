#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_EDGES 100
#define MAX_NODES 30

typedef struct {
    int source;
    int destination;
    int weight;
} Edge;

int graph[MAX_NODES][MAX_NODES];
bool visited[MAX_NODES];
int path[MAX_NODES];
int num_nodes = 0;
int num_edges = 0;
int max_path_length = 0;

void initializeGraph(Edge edges[], int num_edges) {
    for (int i = 0; i < num_edges; i++) {
        int u = edges[i].source;
        int v = edges[i].destination;
        graph[u][v] = 1;  // Mark edge from u to v (assuming nodes are 0-indexed)
    }
}

bool dfsFindPath(int u, int path_length) {
    visited[u] = true;
    path[path_length++] = u;

    if (path_length == num_nodes) {
        max_path_length = path_length;
        return true;
    }

    for (int v = 0; v < num_nodes; v++) {
        if (graph[u][v] == 1 && !visited[v]) {
            if (dfsFindPath(v, path_length)) {
                return true;
            }
        }
    }

    visited[u] = false;  // Backtrack
    return false;
}

void printPath() {
    if (max_path_length == 0) {
        printf("No path covering all nodes exists.\n");
    } else {
        printf("Path Covering All Nodes: ");
        for (int i = 0; i < max_path_length; i++) {
            printf("%d", path[i]);
            if (i != max_path_length - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    }
}

int main(void) {
    Edge edges[MAX_EDGES];
    int start, end, length;
    int s = 0;

    FILE *file = fopen("input", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (s == 0) {
        if (fscanf(file, "%d %d %d", &start, &end, &length) == 3) {
            if (start == -1) {
                s = 1;
            } else {
                edges[num_edges++] = (Edge){start, end, length};
                num_nodes = (start > num_nodes) ? start + 1 : num_nodes;
                num_nodes = (end > num_nodes) ? end + 1 : num_nodes;
            }
        }
    }

    fclose(file);

    initializeGraph(edges, num_edges);

    bool pathFound = false;
    for (int i = 0; i < num_nodes; i++) {
        // Reset visited array for each starting node
        for (int j = 0; j < num_nodes; j++) {
            visited[j] = false;
        }

        if (dfsFindPath(i, 0)) {
            pathFound = true;
            break;
        }
    }

    printPath();

    return 0;
}
