#include "cmpsc473mr.h"


int count = 0;
int temp_buffer_location = 0;
int number_split = 0;
int memoryLocation[10];
int N=0, B=0;


word_list *head = NULL;


//just a basic function to return the minimum of two numbers

/*
int min(int x, int y)
{
	if(x > y)
	{
		return y;
	}

	return x;
}
*/

void close_file(FILE* file)
{
	fclose(file);
}


void *map_reader_i(void *ptr)
{	

	
}


void *map_adder_i(void *ptr)
{	
	

}

void reducer()
{

}

int main(int args, char* argv[])
{
	int c, i;
	extern char *optarg;
	extern int optind, optopt;

	int file_;
	double size;

	word_list word;

	N=0; B=0;

	while ((c = getopt(args, argv, "n:b:")) != -1) 
	{
		switch(c)
		{
			case 'n': 
					N = atoi(optarg); 
					break;
			case 'b': 
					B = atoi(optarg); 
					break;
		}
	}

	//char filename[50];

	//strcpy(filename, argv[optind]);

	FILE *file = fopen(argv[optind], "r");

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

	char *buffer = mmap( 0, (size + 10), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, file_, 0 );

	printf("%s\n", buffer);


	return 0;
}