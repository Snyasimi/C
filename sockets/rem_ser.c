#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>

int main(){

    struct sockaddr_in server,client;

        server.sin_family = AF_INET;
        //server.sin_addr = INADDR_LOOPBACK;
        inet_pton(AF_INET,"127.0.0.1",&server.sin_addr);
        server.sin_port = htons(6000);
        
        //make socket

        int sock_fd = socket(AF_INET,SOCK_STREAM,0);

        if(sock_fd < 0 ){

            perror("Could not make a socket");
            return 1;
        }

        //bind 
	size_t size = sizeof(server);
        if(bind(sock_fd,(struct sockaddr *)&server,size/*SUN_LEN(&server)*/ ) < 0 ){

            perror("Could not bind socket");
            return 1;

        }
	printf("Socket binded..\n");
        //connect
        if( listen(sock_fd,5)<0){

            perror("Failed to listen for connections");
            return 1;
        }

	printf("Listening for connections..\n");
	socklen_t cli_len = sizeof(client);
        int new_connection = accept(sock_fd,(struct sockaddr *)&client,&cli_len);

        if(new_connection < 0 ){
            perror("Could not establish connection");
            return 1;
        }

        printf("Client Connected :) \n");

    while(1){

        char buffer[20];
        //recieve from cli
        if(recv(new_connection,(void*)&buffer,sizeof(buffer),0) < 0 ){
            
            printf("Couldnt recieve data\n");
            perror("ERR\n");
            return 1;
        }

        //check if bye was sent
        if(strncmp(buffer,"bye",(size_t)strnlen(buffer,sizeof(buffer))) == 0 ){

            printf("Client disconnected...\n");
            
            close(new_connection);
            sleep(2);
            printf("Connection closed");
            return 0;
        }

        printf("Message recieved...\n %s\n",buffer);
        memset(buffer,0,sizeof(buffer));

    }
    
    

    sleep(1);
    printf("done");



return 0;
}
