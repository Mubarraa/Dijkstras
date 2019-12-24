// PQ ADT interface for Ass2 (COMP2521)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "PQ.h"


typedef struct PQRep {
	ItemPQ  *items;            
	int     nitems;
    //int     nslots;
} PQRep;

static void arrangeUp (ItemPQ a[], int i);
static void swap (ItemPQ a[], int i, int j);
static void arrangeDown (ItemPQ a[], int i, int N);
static int less (ItemPQ i, ItemPQ j);

/* Creates new priority pq, that can store items of type ItemPQ.
*/
PQ newPQ(){

    PQ new = malloc(sizeof(PQRep));
    //ItemPQ *a = malloc(sizeof(items));
	assert(new != NULL /*&& a != NULL*/);
	new->items = NULL;
	new->nitems = 0;
	return new;    
}


/* Adds item (ItemPQ) to the priority pq.
   If an item with 'key' exists, it's 'value' is updated.
*/
void  addPQ(PQ pq, ItemPQ element){

    int i = 0;
    int found = 0;
    while (i < pq->nitems) {        
        if (pq->items[i].key == element.key) {
            found = 1;
            break;
        }
        i++;
    }

    if (found == 1) {
        pq->items[i].value = element.value;   
    }else {
        pq->nitems++;
        pq->items[pq->nitems] = element;
        arrangeUp(pq->items,pq->nitems);
    }

}

/* Removes and returns the item (ItemPQ) with smallest 'value'.
   For items with equal 'value', observes FIFO.
   Returns null if this pq is empty.
*/
ItemPQ  dequeuePQ(PQ pq) {

    ItemPQ top = pq->items[1]; // ItemPQ[0] ?
    pq->items[1] = pq->items[pq->nitems];
    pq->nitems--;

    arrangeDown(pq->items, 1, pq->nitems);
    return top;

}

/* Updates item with a given 'key' value, by updating that item's value to the given 'value'.
   If item with 'key' does not exist in the pq, no action is taken
*/
void  updatePQ(PQ pq, ItemPQ element) {

    int i = 0;
    int found = 0;
    while (i < pq->nitems) {        
        if (pq->items[i].key == element.key) {
            found = 1;
            break;
        }
        i++;
    }

    if (found == 1) {
        pq->items[i].value = element.value;   
    }
}

int PQEmpty(PQ pq) {

    if (pq->nitems > 0) return 1;
    return 0;

}

void  showPQ(PQ pq) {

    if (pq->nitems == 0) {

        printf("Priority pq Empty");
    }else {

        int i = 0;
        while (i < pq->nitems) {
            printf("%d ", pq->items[i].key);
            i++;
        }

    }
}
void  freePQ(PQ pq) {

    free(pq);
    
}

static void arrangeUp (ItemPQ *a, int i) {

    while (i > 1 && less(a[i/2], a[i])) {
        swap (a, i, i/2);
        i = i/2;
    }
}

static void swap (ItemPQ *a, int i, int j) {

    ItemPQ temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

static int less (ItemPQ i, ItemPQ j) {
    
    if (i.key < j.key) return 1;
    if (i.key > j.key) return 0;

    return -1;
}

static void arrangeDown (ItemPQ a[], int i, int N) {

    while (2*i <= N) {

        int j = 2*i;
        if ( j < N && less(a[j], a[j+1])) j++;
        if (!less(a[j], a[j])) break;
        swap(a,i,j);

        i = j;

    }

}
