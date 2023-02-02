#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// the elements in the list
struct element {
    int data;
    struct element *next;
};

// a pointer to the head of the list
struct element *head;

// a temporary pointer used for freeing memory
struct element *temp;

int main(int argc, char *argv[])
{

int sum; /* this data is shared by the thread(s) */

void *runner(void *param); /* the thread */

pthread_t tid; /* the thread identifier */
pthread_attr_t attr; /* set of attributes for the thread */

if (argc != 2) {
	fprintf(stderr,"usage: a.out <integer value>\n");
	/*exit(1);*/
	return -1;
}

if (atoi(argv[1]) < 0) {
	fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
	/*exit(1);*/
	return -1;
}

/* get the default attributes */
pthread_attr_init(&attr);

/* create the thread */
pthread_create(&tid,&attr,runner,argv[1]);

/* now wait for the thread to exit */
pthread_join(tid,NULL);

while (head->next != NULL)
    {
        printf("%d\n",head->data);

        // free memory after visiting a node
        temp = head;
        head = head->next;
        free(temp);
    }

}


/**
 * The thread will begin control in this function
 */
void *runner(void *param)
{
    int collatz_num = atoi(param);
    struct element *node;

    // malloc allocates the memory to hold a struct element
    node = (struct element *) malloc(sizeof(struct element));
    head = node;

    while (1)
    {
        // populate the list
        node->data = collatz_num;
        node->next = (struct element *) malloc(sizeof(struct element));

        node = node->next;

	if (collatz_num == 1)
	{
		break;
	}

        if (collatz_num % 2 == 0)
	{
		collatz_num /= 2;
	}
	else
	{
		collatz_num = (collatz_num / 3) + 1;
	}

    }
    node->next = NULL;
    return 0;
}
