#include "project3.h"

#define MAX 10000000

char buffer[MAX][20];

int count = 0;
int temp_buffer_location = 0;
int number_split = 0;




void reader(void)
{

}


void adder()
{

}

void reducer(void)
{

}

int main(int args, char* argv[])
{
	

	FILE *file = fopen("inputfile-100KB.txt", "r");
    
   	//int count =0;
   	int size =0,n,b;
   	int tempcount;

   	int memoryLocation[10];

   	char c;


   	printf("Enter value of n: ");
   	scanf("%d", &n);
   	printf("Enter value of b: ");
   	scanf("%d", &b);




   	//creating the pthreads
   
   	//pthread_t thread1, thread2;




   	//Finding the size of the file
   	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	printf("Size of the file is %d\n", size);

	/*
	char ch;
	int byteAmount = size/2;

    if(file == NULL)
    {
    	perror("File open error");
    	return -1;
    }

	
    while( ( ch = fgetc(file) ) != EOF || count < byteAmount)
	{
  		buffer[count++] = ch; // make Buffer global variable
  		printf("%c", ch);
	} 
	*/

/*
	//This reads all the words regardess of special characters
    do
    {
    	c = fscanf(file, "%s", buffer[i]);
    	//printf("%s\n", buffer[i]);
    	i++;

    }while(c != EOF);
*/ 
   // head = malloc(sizeof(wordBuffer));

/*
    do
    {
    	c = fscanf(file, "%s", head->string);
    	count++;
    	printf("%s\n", head->string);
    	head = head->next;
    	head = malloc(sizeof(wordBuffer));

    }while(c != EOF);

*/

 


    do
    {
    	c = fscanf(file, "%[A-Z|a-z]", buffer[count]);
    	
    	printf("%s\n", buffer[count]);
    	count++;
    	fscanf(file, "%*[^A-Za-z]");

    }while(c != EOF);


    number_split = count/n;
    memoryLocation[0] = 0;

    for (int i = 1; i < n; ++i)
    {
    	memoryLocation[i] = memoryLocation[i-1] + number_split;
    }

    for (int i = 0; i < n; ++i)
    {
    	printf("%d\n", memoryLocation[i]);
    }

     // FILE *tempfile[10];
    //FILE *file = open(...)
    /*
    for (int i = 0; i < n; ++i)
    {
    	char name[10] = "tempfile";
    	char ext[6] = ".txt";
    	char tempbuffer[10];
    	char temp_file_name[20];
    	sprintf(tempbuffer, "%d", i);

    	
    	name[10] = strcat(name, tempbuffer);
    	printf("%s\n", strcat(name, ext));
    	temp_file_name[20] = strcat(name, ext);
    	FILE *tempfile = fopen(temp_file_name, "rw");
    	if(tempfile == NULL)
    	{
    		perror("Failed");

    	}

    	do
    	{
    		printf("%s\n", buffer[temp_buffer_location]);
    		fprintf(tempfile, "%s\n", buffer[temp_buffer_location]);
    		tempcount++;
    		temp_buffer_location++;

    	}while((temp_buffer_location < count) && (tempcount < (count/n)));
    }
    */

    //Reading only alpha characters
    //Above implementations reads all
    /*
    while (fscanf(file, "%[A-Z|a-z]", head->string) == 1) 
    {   // read until find a non alpha character
    	printf("%s\n", head->string);
    	head->word_count = count;
    	count++;

    	head = head->next;
    	head = malloc(sizeof(wordBuffer));

   		fscanf(file, "%*[^A-Za-z]");  // discard non alpha character and continue
	}
	*/
	


	fclose(file);


    printf("The size is %d and number of words are %d\n", size, count);



    //pthread_create(&thread1, NULL, &mapper, NULL);
    //pthread_create(&thread2, NULL, &mapper, NULL);


	//pthread_join(thread1, NULL);
    //pthread_join(thread2, NULL);


    //free(head);

	return 0;
}