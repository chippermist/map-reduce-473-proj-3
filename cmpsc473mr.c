#include "cmpsc473mr.h"


int count = 0;
int temp_buffer_location = 0;
int number_split = 0;
int memoryLocation[10];	//no longer used
int N=0, B=0;
double timer_start =0;
double timer_end = 0;	

pthread_t *threads;
queue** sharedBuffer;
int* sharedBufferStatusForAdder;


word_list *head = NULL;


void close_file(FILE* file)
{
	fclose(file);
}


void init()
{
	int k = 0;
	while(k < N)
	{
		sharedBuffer[k] = create_list();
		sharedBufferStatusForAdder[k] = 0;
		k++;
	}

}

void *map_reader_i(void *ptr)
{	
	/*wordBuffer *word;
	word = (wordBuffer*)ptr;
	word_list *sharedMapBuffer = NULL;
	sharedMapBuffer = malloc(sizeof(word_list));
	
	pthread_mutex_t lock;
	pthread_t adder_i;
	pthread_mutex_init(&lock, NULL);
	char *c;
	//printf("1\n");
	//printf("%s\n", word->string);
	//printf("2\n");
	do
    {
    	c = sscanf(word->string, "%[A-Z|a-z]", sharedMapBuffer->word);
    	
    	printf("%s is a word\n", sharedMapBuffer->word);
    	sscanf(word->string, "%*[^A-Za-z]");
    	sharedMapBuffer= sharedMapBuffer->next;

    	sharedMapBuffer = malloc(sizeof(word_list));
    }while(c != EOF);

    sharedMapBuffer = malloc(sizeof(word_list));
	head = sharedMapBuffer;

	adderBuffer *node = -malloc(sizeof(adderBuffer));
	node->lock = lock;
	node->list = sharedMapBuffer;
	node->index = index;

	node->count = 0;


	pthread_create(&adder_i, NULL, map_adder_i, (void*)ptr);

    c = strtok(word->string, " ,.*^!@~'");
    while(c != NULL)
    {
    	//printf("%s\n", c);
    	while(sharedMapBuffer->size == B);

    	pthread_mutex_lock(&lock);
    	sharedMapBuffer->word = malloc(sizeof(char*)*strlen(c)+1);
    	sharedMapBuffer->word = c;
    	c = strtok(NULL, " ");
    	sharedMapBuffer = sharedMapBuffer->next;
    	sharedMapBuffer = malloc(sizeof(word_list));
    	pthread_mutex_unlock(&lock);
    }


    printf("Printing from the head\n");
    while(head != NULL)
    {
    	printf("%s\n", head->word);
    	head = head->next;
    }
    node->read_before = 1;

    pthread_exit(NULL);*/
    pthread_t adderthread;

	readerBuffer *rdata = (readerBuffer *)ptr; // rdata 
	int index = rdata->index;
	char *chunk = rdata->chunk;
	queue *wordlist = create_list();


	pthread_mutex_t lock;

	pthread_mutex_init(&lock, NULL);


	adderBuffer *word_data = malloc(sizeof(adderBuffer));
	word_data->adderlist = wordlist;
	word_data->index = index;
	word_data->read_before = 0;
	word_data->lock = lock;

	pthread_create(&adderthread, NULL, map_adder_i, (void*)word_data);
	char *ptrs = strtok(chunk, " \n\r\t;:.!?',\"-\0");
	
	
	while (ptrs != NULL){
		while(wordlist->size == B);
		pthread_mutex_lock(&lock);
		enqueue (wordlist, 1, ptrs);
		//printf("Enqueuing\n");
		pthread_mutex_unlock(&lock);
		ptrs = strtok(NULL,  " \n\r\t;:.!?',\"-\0");
	}

	word_data->read_before = 1;


	pthread_exit(NULL);

	
}


void *map_adder_i(void *ptr)
{	

	adderBuffer *word_data = (adderBuffer*)ptr;

	int index = word_data->index;
	queue* wordlist = word_data->adderlist;
	pthread_mutex_t lock = word_data->lock;

	while(!word_data->read_before || wordlist->size > 0)
	{ 
		//printf("1\n");
		while ( wordlist->size == 0 ); 
		//printf("2\n");

		pthread_mutex_lock(&lock);	
		node* wordsList = dequeue(wordlist);
	 	pthread_mutex_unlock(&lock);
	 	
	 	//sharedBuffer = malloc(sizeof(queue**)*10);
		//sharedBuffer[index] = create_list();
		node* word_find = look(sharedBuffer[index], wordsList->word);

	 	if (word_find == NULL) 
	 	{
	 		enqueue(sharedBuffer[index], wordsList->count, wordsList->word);
	 		//printf("Enqueuing now....lets see if this works..\n");
	 	}
	 	else 
	 	{
	 		word_find->count = word_find->count + wordsList->count;
	 	}
	 	free(wordsList);
	 	//printf("I am here\n");
	}

	sharedBufferStatusForAdder[index] = 1;


	pthread_exit(NULL);
}



void *reducer(void* ptr)
{
	
	for (int i = 0; i < N; i++) 
	{
		//printf("hello\n");
		while(sharedBufferStatusForAdder[i] != 1);
		//printf("Finally...\n");

	}

	//printf("Hi\n");
	queue* sharedBufferFinal = create_list();

	for (int i = 0; i < N; i++) 
	{
		while(sharedBuffer[i]->size > 0) 
		{
			node* wordsList = dequeue(sharedBuffer[i]);

			node* ret = look(sharedBufferFinal, wordsList->word);

		 	if (ret == NULL) 
		 	{
		 		enqueue(sharedBufferFinal, wordsList->count, wordsList->word);
		 	}
		 	else 
		 	{
		 		ret->count += wordsList->count;
		 	}
		 	free(wordsList);
		}

	}
	FILE* file = fopen("output.txt", "rw+");

	//printf("1\n");
	node *current_node = sharedBufferFinal->head;

	while(current_node)
	{
		//printf("Hello \n");
		fprintf(file, "%s, %d\n", current_node->word, current_node->count);
		current_node = current_node->next;
	}


	close_file(file);


	pthread_exit(NULL);
}

int main(int args, char* argv[])
{
	//int c;
	extern char *optarg;
	extern int optind, optopt;

	int file_;
	int flag =0;
	double size;

	N=0, B=0;

	N = atoi(argv[2]);
	B = atoi(argv[3]);

	if(args < 3)
	{
		perror("Please enter the (filname) (threads) (buffer size)\n");
	}

	//char filename[50];

	//strcpy(filename, argv[optind]);


	//timer to test
	timer_start = timer();


	FILE *file = fopen(argv[1], "r");

	if(file == NULL)
	{
		perror("File cannot be opened.");
		return -1;
	}

	//Finding the size of the file
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	file_ = fileno(file);

	printf("Size of the file is: %f\n", size);

	char *buffer = mmap( 0, size+1 , PROT_READ | PROT_WRITE, MAP_PRIVATE , file_, 0 );

	sharedBuffer = malloc(sizeof(queue *) * N);
	sharedBufferStatusForAdder = malloc(sizeof(int*)*N);


	init();
	/*	i=0;
	char *chunk;

	int min_chunk_size = size / N;
	int where_we_are = 0;
	int 

	for (int i = 0; i < N && where_we_are < size; i++)
	{

		int chunkSize = min_chunk_size;
		where_we_are = min_chunk_size;
		
		printf( "min chunk size: %d\n", min_chunk_size);

		while (chunkSize < size && buffer[chunkSize] != ' ' && buffer[chunkSize] != '\n' && buffer[chunkSize] != '\r')
		{
			//printf("%c\n", buffer[where_we_are]);
			chunkSize++;
		}

		if(chunkSize <= size)
		{
			where_we_are = chunkSize;
		}

		

		printf( "where_we_are: %d, chunkSize: %d\n", where_we_are, chunkSize);
				
	}
*/

	//printf("%s\n", buffer);

	int where_it_went = 0;
	int chunkSize = size / N;
	int where_we_are = 0; 

	threads = malloc(sizeof(pthread_t)* N);

	for(int z = 0; z < N && where_we_are < size; z++)	//working until the number of N
	{
		char *chunk;
		int curChunkSize = chunkSize;
		int start = where_it_went;
		int current = 0;

		if( (start + chunkSize) > size)
		{
			current = size;			
		}
		else
		{
			current = start + chunkSize;
		}

		while (current != size && buffer[current] != ' ' && buffer[current] != '\0' && buffer[current] != '\n') 
		{
			current++;
			curChunkSize++;
		}
		where_it_went = current;


		printf("%d current : %d where it went: %d\n",curChunkSize, current, where_it_went );


		chunk = malloc(sizeof(char)*curChunkSize + 10);

		int end_point = start + curChunkSize;
		for (int i = start; i < end_point; i++)
		{
			chunk[i-start] = buffer[i];
			if(i == curChunkSize-1)
			{
				chunk[curChunkSize] = '\0';
			}
		}

		//printf("%s\n", chunk);
		wordBuffer wordReader;
		wordReader.string = malloc(sizeof(char)*curChunkSize);
		wordReader.string = chunk;
		wordReader.index = z;

		//threads[z] = malloc(sizeof(pthread_t));

		pthread_create(&threads[z], NULL, map_reader_i, &wordReader);
		//pthread_create(&threads[z+1], NULL, map_adder_i, &wordReader);

	for (int i = 0; i < N; ++i)
	{
		pthread_join(threads[i], NULL);
	}
		flag++;
	}


	free(threads);

	close_file(file);

	while(flag < N)
	{
		sharedBufferStatusForAdder[flag] = 1;
		flag++;
	}

	printf("Threads have done processing\n");

	
	pthread_t reducer_thread;
	pthread_create(&reducer_thread, NULL, reducer, NULL);

	timer_end = timer();


	
	printf("Time taken : %f\n", timer_end - timer_start);
	
	pthread_exit(NULL);


	
	return 0;
}

