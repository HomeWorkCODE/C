#include "List.h"

node * initList(float value) /*returns pointer to head*/
{
	node * head;
	head = (node *)malloc(1 * sizeof(node));
	head->next = NULL;
	head->data = value;
	return head;
}

void terminate(node ** head) /*terminate the list*/
{
    node* temp;
	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}

	*head = NULL;
}

node * addNode(node * head,float value) /*add new node to the end*/ 
{
	if(head == NULL)
		return NULL;
	else
	{
		if (getNext(head) == NULL)
		{
			node * Node;
			Node = (node *)malloc(1 * sizeof(node));
			Node->next = NULL;
			Node->data = value;
			head->next = Node;
			return Node;
		}
		else
		{
			return addNode(getNext(head),value);
		}
	}
	
}

node * deleteNode(node * head,node ** Node) /* delete node and return pointer to the next node */
{
	if(head == NULL)
		return NULL;

	if (head == *Node)
	{
		/*we need ot delete the head*/
		node * newHead = getNext(*Node);
		node * temp = *Node;
		free(temp);
		*Node=NULL;
		return newHead;
	}

	else
	{
		if(getNext(head) == *Node)
		{
			head->next = getNext(getNext(head));
			free(*Node);
		}
		else
			deleteNode(getNext(head),Node);
	}
	return head;
}

int listLen(node * head) /* will return the lenth of list with givin pointer to lists head*/
{
	if(head == NULL)
		return 0;

	return listLen(getNext(head)) + 1;
}

node * getHead(node * head) /* will return pointer to the head */
{
	return head;
}

node * getLast(node * head) /* will return pointer to end of the list */
{
	if(head == NULL)
		return NULL;

	if (getNext(head) == NULL)
	{
		return head;
	}
	getLast(getNext(head));
}

node * getNext(node * Node) /* return the next node */
{
	return Node->next;
}

node * getPrevious(node * head,node * Node) /* return the previous node */
{
	if(head == NULL)
		return NULL;

	if(getNext(head) == NULL)
		return NULL;

	else
	{
		if(getNext(head) == Node)
		{
			return head;
		}
		else
			getPrevious(getNext(head),Node);
	}
}

float getValue(node * Node) /* return the data */
{
	return Node->data;
}

float getAvarage(node * head,int length) /* return avarage of list values with given head */
{
	if(head == NULL)
		return 0;

	return (getAvarage(getNext(head),length) + (getValue(head)/length));
}

void print(node * head) /* for testing */
{
	while(head != NULL) 
	{
		printf("%0.1f -> ",getValue(head));
		head = getNext(head);
	}
	printf("\n");
}