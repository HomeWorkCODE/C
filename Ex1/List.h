#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	float data;
	struct _node * next;
}node;

node * initList(float value); /*return pointer to head*/
void terminate(node ** head); /*terminate the list*/
node * addNode(node * head,float value); /*add new node to the end returns pointer to it*/ 
node * deleteNode(node * head,node ** Node); /* delete node and return pointer to the head */
int listLen(node * head); /* will return the lenth of list with givin pointer to lists head*/
node * getHead(node * head); /* will return pointer to the head */
node * getLast(node * head); /* will return pointer to end of the list */
node * getNext(node * Node); /* return the next node */
node * getPrevious(node * head,node * Node); /* return the previous node */
float getValue(node * Node); /* return the value */
float getAvarage(node * head,int length); /* return avarage of list values with given head and length */
void print(node * head); /*prints the linked list*/
