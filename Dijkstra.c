// Dijkstra ADT interface for Ass2 (COMP2521)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "Dijkstra.h"
#include "PQ.h"
#include "Graph.h"

#define INFINITY 100000

typedef PredNode* PredList;
typedef ItemPQ* ITEMPQ;
ITEMPQ newItemPQ(int edgeweight, int distance, int Vertex);
static bool requires_attention(ShortestPaths *new, ItemPQ u, int w);
static void relax_edge(ShortestPaths *new, ItemPQ u, Vertex w, Vertex v);
PredList newPred(ItemPQ u);
PQ DiPQ(int vertices, ShortestPaths new, Graph g, Vertex v);
static int findedge(Graph g, Vertex i, Vertex j);
static void NewPath(ShortestPaths *new, ItemPQ u, Vertex t, Vertex v);


ShortestPaths dijkstra(Graph g, Vertex v) {

    printf("vertex %d\n", v);
    assert(g != NULL);

    int numV = numVerticies(g);
    printf("numV %d\n", numV);

    struct ShortestPaths* new = malloc(sizeof(ShortestPaths));
    assert(new != NULL);

    new->noNodes = numV;
    new->src = v;
    new->dist = malloc(sizeof(int)*numV);
    assert(new->dist != NULL);
    new->pred = malloc(numV*sizeof(struct PredNode));
    assert(new->pred != NULL);

    for (int i=0; i < numV; i++) {
  	  new->dist[i] = -1;
      //printf("hi\n");
  	}

    for (int i=0; i < numV; i++) {
      new->pred[i] = NULL;
  	}

    new->dist[v] = 0;
    //printf("%d\n", new->dist[v]);
    ItemPQ u;

    PQ Q = DiPQ(numV, *new, g, v);

    while (!PQEmpty(Q)) {

      u = dequeuePQ(Q);
      Vertex t;

      for (t = 0; t < new->noNodes; t++) {

        if (adjacent(g,t, u.key)) {

          if (requires_attention(new, u, t) == 1) {
            relax_edge(new, u, t, v);
            int k = findedge(g, t, u.key);
            ITEMPQ element = newItemPQ(k, new->dist[t], t);
            addPQ(Q, *element);
          }
          else if (requires_attention(new, u, t) == 0) {
            NewPath(new, u, t, v);
            int k = findedge(g, t, u.key);
            ITEMPQ element = newItemPQ(k, new->dist[t], t);
            addPQ(Q, *element);
          }

          /*int k = findedge(g, t, u.key);
          ITEMPQ element = newItemPQ(k, new->dist[t], t);
          addPQ(Q, *element);*/
        }
      }
    }

  return *new;
}

void showShortestPaths(ShortestPaths paths) {
  printf("\n");

  printf("Number of vertices: %d\n", paths.noNodes);
  printf("Number of edges: %d\n", paths.src);

  for (int i = 0; i < paths.noNodes; i++) {
    struct PredNode* curr = paths.pred[i];
    printf("%d : ", i);
    while (curr) {
      printf("%d -> ", curr->v);
      curr = curr->next;
    }
    printf("\n");
  }
  printf("\n");
}


void  freeShortestPaths(ShortestPaths paths) {

}


static bool requires_attention(ShortestPaths *new, ItemPQ u, Vertex t) {
  if (new->dist[t] >  u.key) {
    return 1;
  }
	else {
    return 0;
  }
 }

static void NewPath(ShortestPaths *new, ItemPQ u, Vertex t, Vertex v) {
	struct PredNode* newNode = newPred(u);
  new->pred[t] = newNode;
  new->dist[t] = u.value;
}

static void relax_edge(ShortestPaths *new, ItemPQ u, Vertex t, Vertex v) {
    struct PredNode* newNode = newPred(u);
    newNode->next = new->pred[v];
    new->pred[v] = newNode;
    new->dist[t] = u.value;
 }

PredList newPred(ItemPQ u) {

    struct PredNode *newNode = malloc(sizeof(struct PredNode));
    assert(newNode != NULL);
    newNode->v = u.key;
    newNode->next = NULL;

    return newNode;
}
ITEMPQ newItemPQ(int edgeweight, int distance, Vertex t) {

    ITEMPQ newItem = malloc(sizeof(ItemPQ));
    assert(newItem != NULL);
    newItem->key = t;
    newItem->value = distance + edgeweight;

    return newItem;

}

PQ DiPQ(int vertices, ShortestPaths new, Graph g, Vertex v) {

  PQ Q = newPQ();
  for (int i = 0; i <= vertices; i++) {
    if (v!=i) {
      Vertex k = findedge(g, v, i);
      struct ItemPQ* element = newItemPQ(k, 0, i);
      addPQ(Q, *element);
    }
  }
  return Q;
}

static int findedge(Graph g, Vertex i, Vertex j) {
  if (adjacent(g, i, j)) {
    struct _adjListNode* curr = outIncident(g, i);

    while (curr->w != j) {
      curr = curr->next;
    }
    return curr->weight;
  }
  return 0;
}
