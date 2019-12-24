#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "Graph.h"

int main (void) {

	    // create the graph given in above fugure
    int noNodes = 6;
    struct GraphRep* graph = newGraph(noNodes);
	insertEdge(graph, 0, 1, 4);
    insertEdge(graph, 0, 2, 2);
    insertEdge(graph, 1, 2, 2);
    insertEdge(graph, 1, 4, 4);
    insertEdge(graph, 1, 3, 9);
    insertEdge(graph, 2, 4, 8);
    insertEdge(graph, 3, 4, 1);
    insertEdge(graph, 4, 1, 1);
    insertEdge(graph, 5, 1, 5);
    insertEdge(graph, 5, 2, 2);
    insertEdge(graph, 3, 4, 3);
	removeEdge(graph, 0, 2);
	removeEdge(graph, 1, 2);
	removeEdge(graph, 1, 3);
	outIncident(graph, 3);

    // print the adjacency list representation of the above graph
    showGraph(graph);

	freeGraph(graph);

    return 0;

}

bool validV(Graph g, Vertex ver) {
   return (g != NULL && ver >= 0 && ver < g->nV);
}

AdjList createNode(int ver, int weight){
    struct _adjListNode* newNode = malloc(sizeof(struct _adjListNode));
    newNode->w = ver;
	newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// create an empty graph
Graph newGraph(int noNodes) {
	// ensure there is going to be at least on node in the graph
	assert(noNodes > 0);
	// ensure memory allocated successfully
	Graph g = malloc(sizeof(GraphRep));
	assert(g != NULL);
	// create an empty graph
	g->nV = noNodes;
	g->nE = 0;
	// ensure memory allocated successfully
	g->array = malloc(noNodes * sizeof(struct _adjListNode));
	assert(g->array != NULL);
	// create an empty list
	for (int i=0; i < noNodes; i++) {
		g->array[i] = NULL;
	}
	return g;
}

void insertEdge(Graph g, Vertex src, Vertex dest, int weight) {

	assert(g != NULL && validV(g, src) && validV(g, dest) && weight > 0);

	struct _adjListNode* curr = g->array[src];

	while (curr != NULL) {
		if (curr->w != dest) {
			curr = curr->next;
		}
		else {
			return;
		}

	}

	struct _adjListNode* newNode = createNode(dest, weight);
	newNode->next = g->array[src];
    g->array[src] = newNode;
	g->nE++;

}

void removeEdge(Graph g, Vertex src, Vertex dest) {

	assert(g != NULL && validV(g, src) && validV(g, dest));
	struct _adjListNode* curr = g->array[src];

	while (curr != NULL) {
		if (curr->w == dest) {
			g->array[src] = curr->next;
			g->nE--;
			free(curr);
			break;
		}
		else if (curr->next->w == dest) {
			curr->next = curr->next->next;
			g->nE--;
			break;
		}
		curr = curr->next;
	}

}

bool adjacent(Graph g, Vertex src, Vertex dest) {
	assert(g!=NULL && validV(g, src) && validV(g, dest));
	struct _adjListNode* curr = g->array[src];
	while (curr != NULL) {
		if (curr->w == dest) {
			return (curr != 0);
		}
		curr = curr->next;
	}
	return (curr==0);
}


int numVerticies(Graph g) {
	assert(g != NULL);
	return g->nV;
}

AdjList outIncident(Graph g, Vertex v) {
	struct _adjListNode* curr = g->array[v];
	return curr;
}
/*
AdjList inIncident(Graph g, Vertex v) {

} */

void showGraph(Graph g) {
	assert(g != NULL);

	printf("\n");

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);

	printf("\n");

    for (int i = 0; i < g->nV; i++) {
		struct _adjListNode* curr = g->array[i];
		printf("%d : ", i);
    	while (curr) {
    		printf("%d -> ", curr->w);
    		curr = curr->next;
    	}
		printf("\n");
    }

	printf("\n");

}

void freeGraph(Graph g) {
	assert(g != NULL);
	for (int i = 0; i < g->nV; i++) {
		free(g->array[i]);
	}
	free(g->array);
	g->nV = 0;
	g->nE = 0;
	free(g);
}
