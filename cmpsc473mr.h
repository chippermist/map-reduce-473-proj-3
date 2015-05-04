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
	char word[50];
	int count;
}word_list;

typedef struct __list{
	char string[30];
}wordBuffer;


void *map_reader_i(void*);

void *map_adder_i(void*);

void reducer();