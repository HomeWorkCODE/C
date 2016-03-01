#include "Queue.h"

int main(int argc, char const *argv[])
{
	int i;
	initQueue(0);

	for (i = 1; i < 5; ++i)
	{
		addElement((float)i);
	}
	// print(front);
	// terminate(front);
	// print(front);
	// not = addNode(front,1515151);
	// deleteNode(front,getLast(front));
	// printf("%0.1f\n\n",getValue(getLast(front)));
	// print(front);
	// terminate(&front);
	// front = deleteNode(front,&front);
	// front = deleteNode(front,&front);
	print(getFront());
	printf("%0.1f\n",getValue();
	return 0;
}

/*// Two glboal variables to store address of front and rear nodes. 
struct Node* front = NULL;
struct Node* rear = NULL;*/