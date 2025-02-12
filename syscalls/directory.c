#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>


int main(){

	//Create a directory
	//create a file
	
	if(mkdir("Homework",0777) < 0){

		printf("Error occured\n");
		return 1;
	}


	if( open("Homework/class.txt",O_CREAT | O_RDWR,0777) < 0 ){

		printf("There was an error creating the file");
		return 1;
	}

	printf("File has been created\n");





	return 0;
}
