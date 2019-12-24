// Niriksha Mutharia
// lecture notes used as a guide to implement the functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "Graph.h"

typedef struct GraphRep {
	int nV; // number of vertices
	int nE;	// number of edges
	adjListNode **array; // stores the outgoing vertices
	adjListNode **in_array; // stores the incoming vertices
} GraphRep;

// validate that the graph isn't NULL
// and the vertex is in the range of the graph
bool validV(Graph g, Vertex ver) {
	return (g != NULL && ver >= 0 && ver < g->nV);
}

// create a vertex
AdjList createNode(int ver, int weight){
	// intialise a new node
  struct _adjListNode* newNode = malloc(sizeof(struct _adjListNode));
  newNode->w = ver;
	newNode->weight = weight;
  newNode->next = NULL;

	// return new node
  return newNode;
}

// create an empty graph
Graph newGraph(int noNodes) {

	// ensure there is going to be at least one node in the graph
	assert(noNodes > 0);

	// create an empty graph
	Graph g = malloc(sizeof(GraphRep));
	assert(g != NULL);
	g->nV = noNodes;
	g->nE = 0;
	g->array = malloc(noNodes * sizeof(struct _adjListNode));
	g->in_array = malloc(noNodes * sizeof(struct _adjListNode));
	assert(g->array != NULL);
	assert(g->in_array != NULL);

	// create an empty array of lists
	for (int i=0; i < noNodes; i++) {
	  g->array[i] = NULL;
	}

	for (int i=0; i < noNodes; i++) {
	  g->in_array[i] = NULL;
	}

	// return graph
	return g;
}

void insertEdge(Graph g, Vertex src, Vertex dest, int weight) {

	assert(g != NULL && validV(g, src) && validV(g, dest) && weight > 0);

	// create a dest vertex and add it to the appropriate list
	struct _adjListNode* newNode = createNode(dest, weight);
	newNode->next = g->array[src];
  g->array[src] = newNode;
	g->nE++;

	// create a src vertex and add it to the appropriate list
	struct _adjListNode* in_Node = createNode(src, weight);
	in_Node->next = g->in_array[dest];
  g->in_array[dest] = in_Node;

}

void removeEdge(Graph g, Vertex src, Vertex dest) {

	assert(g != NULL && validV(g, src) && validV(g, dest));

	// initialise a pointer that iterates through the list
	struct _adjListNode* curr = g->array[src];

	while (curr != NULL) {

		// used when the first vertex is the dest vertex
		// free the edge and decrement #edges
		if (curr->w == dest) {
			g->array[src] = curr->next;
			g->nE--;
			free(curr);
			break;
		}

		// used for every other vertices except first
		// free the edge and decrement #edges
		else if (curr->next->w == dest) {
			curr->next = curr->next->next;
			g->nE--;
			break;
		}

		curr = curr->next;
	}

	// edge is also deleted from dest to src in the incoming array
	// initialise a pointer that iterates through the list
	struct _adjListNode* in_curr = g->in_array[dest];

	while (in_curr != NULL) {
		// used when the first vertex is the src vertex
		// free the edge
		if (in_curr->w == src) {
			g->in_array[dest] = in_curr->next;
			free(in_curr);
			break;
		}
		// used for every other vertices except first
		// free the edge
		else if (in_curr->next->w == src) {
			in_curr->next = in_curr->next->next;
			break;
		}
		in_curr = in_curr->next;
	}

}

// check if two vertices are adjacent
bool adjacent(Graph g, Vertex src, Vertex dest) {

	assert(g!=NULL && validV(g, src) && validV(g, dest));

	// initialise a pointer that iterates through the list
	struct _adjListNode* curr = g->array[src];

	// return true if vertices are adjacent
	// else return false
	while (curr != NULL) {
		if (curr->w == dest) {
			return true;
		}
		curr = curr->next;
	}

	return false;
}

// return #vertices in a graph
int numVerticies(Graph g) {
	assert(g != NULL);
	return g->nV;
}

// return a pointer to the list of adjacent vertices
// on outgoing edges from a given vertex.
AdjList outIncident(Graph g, Vertex v) {
	struct _adjListNode* curr = g->array[v];
	return curr;
}

// return a pointer to the list of adjacent vertices
// on incoming edges to a given vertex.
AdjList inIncident(Graph g, Vertex v) {
	struct _adjListNode* curr = g->in_array[v];
	return curr;
}

// show the graph
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

// free the graph
void freeGraph(Graph g) {
	assert(g != NULL);

	for (int i = 0; i < g->nV; i++) {
		free(g->array[i]);
		free(g->in_array[i]);
	}

	free(g->array);
	free(g->in_array);

	g->nV = 0;
	g->nE = 0;

	free(g);
}
