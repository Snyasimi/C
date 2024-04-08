#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){

    struct sockaddr_in server;

        server.sin_family = AF_INET;
        inet_pton(AF_INET,"127.0.0.1",&server.sin_addr);
        server.sin_port = htons(6000);



	//create socket
	
	int sock_fd = socket(AF_INET,SOCK_STREAM,0);

	if(sock_fd < 0 ){
	
		perror("Could not create socket");
	}

	//conect
	
	if(connect(sock_fd,(struct sockaddr *)&server,sizeof(server)) < 0 ){
		perror("could not connect to socket");
	
	}

	printf("Connected to server");



	while(1){
         char buffer[30];
        sleep(1);
        printf("Enter message to send\n:");
        scanf("%s",buffer);

        if(strncmp(buffer,"bye",(size_t)strnlen(buffer,sizeof(buffer))) == 0 ){

            printf("Disconnecting...\n");

            if(send(sock_fd,(void *)&buffer,strnlen(buffer,sizeof(buffer)),0) < 0){

        
                printf("Couldnt send data\n");
        
                perror("ERR\n");
                return 1;
            }

            close(sock_fd);
            return 0;
        }

        if(send(sock_fd,(void *)&buffer,strnlen(buffer,sizeof(buffer)),0) < 0){

        printf("Couldnt send data\n");
        perror("ERR\n");
        return 1;
    }

    printf("Data sent\n");

    }





	// char buffer[] = "hello server.";

	// if(send(sock_fd,buffer,sizeof(buffer),0) < 0 ){
	
	// 	perror("Could not send message");
	// }
	// sleep(1);

	// printf("Message sent..\n");


	
    //     return 0;

	return 0;


}
