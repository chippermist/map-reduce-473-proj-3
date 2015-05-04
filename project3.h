#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>


typedef struct __word_list{
	char word[50];
	int count;
	struct word_list *next;
}word_list;

typedef struct __list{ //global
	char string[30];

}wordBuffer;




void reader(void);

void adder();

void reducer(void);