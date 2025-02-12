//TRYING TO MAKE A SHELL
/*
 * We should exec commands in path
 * While our process is replaced we could recover so as to continue execing our shell
 * read args and pass to programs 
 *
 *
 * 
 * */


#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>



#define MAX_ARGS 2048


int main(){

	char buffer[MAX_ARGS];

	printf("enter text\n");

	if(read(0,buffer,MAX_ARGS) < 0){

		printf("Failed to read input\n");
		perror("Error");

	}

	printf("Done reading");


	//clean input 




return 0;
}

