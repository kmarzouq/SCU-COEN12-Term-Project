/*
 * File:	list.h
 *
 * Copyright:	2020, Darren C. Atkinson
 *
 * Description:	This file contains the public function and type
 *		declarations for a list abstract data type for generic
 *		pointer types.  The list supports deque operations, in
 *		which items can be easily added to or removed from the
 *		front or rear of the list, as well as indexing.
 */

# ifndef LIST_H
# define LIST_H
//creates list data type
typedef struct list LIST;
//creates list
extern LIST *createList(void);
//destorys a list
extern void destroyList(LIST *lp);
//returns number of items in a list
extern int numItems(LIST *lp);
//adds an element to the first node
extern void addFirst(LIST *lp, void *item);
//adds an element to the last node
extern void addLast(LIST *lp, void *item);
//removes the first element
extern void *removeFirst(LIST *lp);
//removes the last element
extern void *removeLast(LIST *lp);
//gets the first first element
extern void *getFirst(LIST *lp);
//gets the last element
extern void *getLast(LIST *lp);
//gets an item given an index
extern void *getItem(LIST *lp, int index);
//adds an item to a certain index
extern void setItem(LIST *lp, int index, void *item);

# endif /* LIST_H */
