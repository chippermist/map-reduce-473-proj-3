#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>


#define MAX_LENGTH 20
#define MAX_THREADS 10
#define BUFFER_SIZE 1024


typedef struct __word_list{
	char *word;
	int count;
	struct __word_list *next;
	struct __word_list *tail;
	struct __word_list *head;
	int size;
}word_list;

typedef struct __list{
	char *string;
	int index;
}wordBuffer;

typedef struct __this_is_same_as_word_list
{
	char* word;
	int count;
	struct __this_is_same_as_word_list *next;
}node;

typedef struct queue
{
    node *head;
    node *tail;
    int size;
}queue;

typedef struct __adderStruct{
	pthread_mutex_t lock;
	int count;
	word_list *list;
	queue *adderlist;
	int read_before;
	int index;
}adderBuffer;



typedef struct rdata_t {
	char* chunk;
	int index;
} readerBuffer; 


static double timer() {    
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return ((double) (tp.tv_sec) + 1e-9 * tp.tv_nsec);
}

void *map_reader_i(void*);

void *map_adder_i(void*);

void *reducer(void*);

void init();

queue *create_list ( )
{
	queue *list = malloc( sizeof( queue ) );
	list->size = 0;
	list->head = list->tail = NULL;
	return list;
}


void enqueue( queue *list, int count, char *word )
{
	node *current = (node*)malloc(sizeof(node));
	current->word = malloc( sizeof( char* ) *(strlen( word ) + 1 ) ); // strlen does not include null terminator
	current->count = count;

	strcpy( current->word , word );
	current->next = NULL;

	if (list->tail == NULL )
	{ //empty
		list->head = current;
		list->tail = current;
	} 
	else {
		list->tail->next = current; //point tail to new node
		list->tail = current;
	}
	list->size++;
}

node *dequeue (  queue *list )
{
	 node *current = list->head;
	 node *prev = NULL;
	if (current == NULL ){ // empty
		return NULL;
	}
	while( current->next != NULL ) 
	{ // iterate to end
		prev = current;
		current = current->next;
	}
	if (current != list->head ) {
		prev->next = NULL;	
		list->tail = prev;
	}
	else {
		list->head = list->tail = NULL; // one element
	}
	list->size--;
	return current;
}


node *look (queue *list, char *word)
{
	node *current = list->head;
	if (current == NULL )
		return NULL;
	while (current->next )
	{
		if (strcmp(word, current->word) == 0) 
			return current;
		current = current->next;
	}
	return NULL;
}