#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){


	printf("I am the parent process\n");

	pid_t pid = fork();

	if((int)pid == 0){
	
		printf("I am the child,\n sleeping for 5 secs\n...");
		sleep(5);
		printf("Executing now...\n");
		execl("/bin/ls","../ls",NULL);
		exit(0);
	} 

	else if((int)pid < 0 ){
	
		printf("error");
	} 
	printf("Waiting for child..\nsleeping for 2..\n");
	sleep(2);
	printf("waiting after sleep..\n");
	wait(NULL);
	printf("Done waiting for child,sleeping now...\n");
	sleep(5);
	printf("Parent done sleeping..\n");

	printf("child done..\n waiting for 3 secs\n...");
	sleep(3);
	printf("parent done\n");

	return 0;
}

