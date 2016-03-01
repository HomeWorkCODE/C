#include <stdio.h>
#include <stdlib.h>
#include "List.h"

void initQueue(float x); /*set the front the the top of queue */
node * addElement(float x); /*add new node to the end returns pointer to it*/ 
/* terminate function from list.h */
float deleteFirst(); /*delete the first node and returns its data*/
/* listLen from list.h */
float getFrontValue(); /* returns the data of the first element */
node * getFront(); /* returns front */
node * getRear(); /* returns rear */