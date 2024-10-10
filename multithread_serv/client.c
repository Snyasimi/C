#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
int main(){


	struct sockaddr_in CLIENT_SOCK;

	memset(&CLIENT_SOCK,0,sizeof(CLIENT_SOCK));
	CLIENT_SOCK.sin_family = AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&CLIENT_SOCK.sin_addr);
	CLIENT_SOCK.sin_port = htons(6969);

	int CLIENT_FD = socket(AF_INET,SOCK_STREAM,0);

	if(CLIENT_FD < 0){

		perror("FAiled to create socket\n");
		return 1;
	}
	printf("FD = %d\n",CLIENT_FD);
	if(connect(CLIENT_FD,(struct sockaddr *)&CLIENT_SOCK,sizeof(CLIENT_SOCK)) < 0 ){

		perror("Failed to connect to server");
		return 1;
	}

	printf("Connected to server\n");
	
	sleep(100);


	return 0;

}
