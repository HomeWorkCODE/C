/*Queue - Linked List implementation*/
#include "Queue.h"

node * front = NULL;

void initQueue(float x)/*return pointer to front*/
{
	front = initList(x);
}

node * addElement(float x) /*add new node to the end returns pointer to it*/ 
{
	node * Node;
	if(front == NULL)
	{
		return NULL;
	}

	else
	{
		Node = addNode(front,x);
		return Node;
	}
}

float deleteFirst() /*delete the first node and returns its data*/
{
	float tmp = getValue(front);
	front = deleteNode(front,&front);
	return tmp;
}

float getFrontValue() /* returns the data of the first element */
{
	if(front != NULL) 
	{
		return getValue(front);
	}
	return ;
}

node * getFront() /* returns front */
{
	return front;
}
node * getRear() /* returns rear */
{
	return getLast(front);
}