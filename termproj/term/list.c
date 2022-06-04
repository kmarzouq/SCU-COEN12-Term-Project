/* Khondakar Mujtaba
 *
 *Creates a dynamic array for data to be stored in
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<assert.h>
#include "list.h"

//defines list data type big O(1)
struct list{
	int count;
	int arrn;
	struct node *head;
	};
//defines node data type Big O(1)
struct node{
	void **data;
	struct node *next;
	struct node *prev;
	int size, full, first;
	};
//creates the list with an empty head. Big O(1) 
LIST *createList(void){
	struct list *lp;
	lp=malloc(sizeof(struct list));
	assert(lp!=NULL);
	lp->count = 0;
	lp->head=NULL;
	lp->arrn=0;
	return lp;
	}
// makes a new node big O (1)
static void NewNode(LIST *lp, int x){ 
	struct node *pn;
	struct node *nn;
	void **narr;
	nn = malloc(sizeof(struct node));
	assert(nn!=NULL);
	narr=malloc(sizeof(void*)*x);
	assert(narr!=NULL);
	nn->data = narr;
	nn->prev=NULL;
	nn->next = NULL;
	pn=lp->head->prev;
	pn->next=nn;
	nn->next=lp->head;
	nn->prev=pn;
	lp->head->prev=nn;
	nn->size=x;
	nn->full=0;
	nn->first=0;
	lp->arrn++;
	}
// frees a node Big O(1)
static void freeNode(LIST *lp, struct node *n){ //issue with freeing
	assert(lp!=NULL && n!=NULL);
	free(n->data);
	free(n);
	lp->arrn--;
	}
//destroys a list Big O(n)
void destroyList(LIST *lp){
	assert(lp!=NULL);
	int i;
	struct node *x;
	struct node *temp;
	int z = lp->arrn;
	x=lp->head;
	for(i=0; i<z; i++){
		temp=x;
		x=x->next;
		freeNode(lp, temp);
		}
	free(lp);
	}
//return number of items in list Big O(1)
int numItems(LIST *lp){
	assert(lp!=NULL);
	return lp->count;
	}
//adds to the bottom of the first node's array and then proceeds to move up. Makes a new node when head is full and makes that its new head. Big O(1) 
void addFirst(LIST *lp, void *item){ 
	assert(lp!=NULL && item!=NULL);
	if(lp->arrn==0){
		lp->head=malloc(sizeof(struct node));
		void **narr;
		narr=malloc(sizeof(void*)*4);
		lp->head->data=narr;
		lp->head->next=lp->head;
		lp->head->prev=lp->head;
		lp->head->size=4;
		lp->head->full=0;
		lp->arrn=1;
		lp->head->first=0;
		}
	struct node *x;
	x=lp->head;
	int length;
	if(lp->head->full==lp->head->size){
		length = lp->count/2 < x->size ? x->size : lp->count/2;
		NewNode(lp,length);
		x=lp->head->prev;
		lp->head=x;
		}
	x->first=(x->first+x->size-1)%x->size;
	x->data[(x->first+x->size)%x->size]=item;
	lp->count++;
	x->full++;
	}

//removes the top element of the head of a list and returns it. Frees node if head is full. Big O(1)
void *removeFirst(LIST *lp){ 
	assert(lp!=NULL);
	void *ret;
	ret = lp->head->data[lp->head->first%lp->head->size];
	lp->head->full--;
	lp->head->first=(lp->head->first+1)%lp->head->size;
	lp->count--;
	if (lp->head->full==0){
		struct node *z;
		struct node *y;
		struct node *temp;
		z=lp->head->next;
		y=lp->head->prev;
		temp = lp->head;
		z->prev=y;
		y->next=z;
		freeNode(lp,temp);
		if(lp->arrn==0){
			lp->head=NULL;
			}
		else{
			lp->head=z;
			}
		}
	return ret;
	}
//adds to top of last node and then adds below it. adds a new node if head is full Big O(1)
void addLast (LIST *lp, void *item){ 
	assert(lp!=NULL && item!=NULL);
	if(lp->arrn==0){
		lp->head=malloc(sizeof(struct node));
		void **narr;
		narr=malloc(sizeof(void*)*4);
		lp->head->data=narr;
		lp->head->prev=lp->head;
		lp->head->next=lp->head;
		lp->head->size=4;
		lp->head->full=0;
		lp->head->first=0;
		lp->arrn=1;
		}
	int length;
	struct node *x;
	x=lp->head->prev;
	if(x->full==x->size){
		length = lp->count/2 < x->size ? x->size : lp->count/2;
		NewNode(lp,length);
		x=lp->head->prev;
		}
	x->data[(x->first+x->full)%x->size]=item;
	lp->count++;
	x->full++;
	}
//removes the bottom element of the last node and returns it. Frees the node if it is empty. Big O(1)
void *removeLast(LIST *lp){
	assert(lp!=NULL);
	void *ret;
	struct node *x=lp->head->prev;
	ret=x->data[(x->first+x->full+x->size)%x->size];
	lp->count--;
	x->full--;
	if(x->full==0){
		struct node *g;
		struct node *h;
		struct node *temp;
		g=x->next;
		h=x->prev;
		temp=x;
		g->prev=h;
		h->next=g;
		freeNode(lp,temp);
		if(lp->arrn==0){
			lp->head=NULL;
			}
		else{
			lp->head=g;
			}
		}
	return ret;
	}
// gets an item from a specific index Big O(n)
void *getItem(LIST *lp, int index){
	assert(lp!=NULL);
	int i;
	struct node *x;
	x=lp->head;
	for(i=0; i<lp->arrn; i++){
		if(index>=x->size){
			index=index - x->size;
			x=x->next;
			}
		else{
			return x->data[index];
			}
		}
	return NULL;
	}
//gets the first Item in a list. Big O(1)
void *getFirst(LIST *lp){
	assert(lp!=NULL);
	struct node *x;
	x=lp->head;
	return x->data[x->first];
	}
//gets the last item in a list. Big O(1)
void *getLast(LIST *lp){
	assert(lp!=NULL);
	struct node *x;
	x=lp->head->prev;
	return x->data[(x->first+x->size-1)%x->size];
	}
//sets the item at a specific index as a specific item. Big O(1)
void setItem(LIST *lp, int index, void *item){ 
	assert(lp!=NULL && index<lp->count && item !=NULL);
	struct node *f;
	f=lp->head;
	int x = index;
	while(x>=f->size){
		x-=f->size;
		f=f->next;
		}
	f->data[x]=item;
	}
