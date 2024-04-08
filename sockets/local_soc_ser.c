#include<stdio.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<string.h>


int main(){

    int sock_fd = socket(AF_LOCAL,SOCK_STREAM,0);
    //declaring addresses
    struct sockaddr_un server,client;

    server.sun_family = AF_LOCAL;
    char filename[] = "./comms";
    strncpy(server.sun_path,filename,sizeof(filename)-1);

    //binding socket to address
    if(bind(sock_fd,(struct sockaddr *)&server,SUN_LEN(&server)) < 0 ){
        perror("Err");
        printf("Error binding socket\n");
        return 1;

    }

    printf("Socket Binded\nWill listen for connections\n");

    if(listen(sock_fd,5) < 0 ){

        printf("Failed to listen for connections\n");
        return 1;
    }

    int size = sizeof(client);
    int new_connection = accept(sock_fd,(struct sockaddr *)&client,&size);
    
    if(new_connection < 0){
        printf("Could not establish connection\n");
        perror("ERR");
        return 1;
    }

    printf("Client Connected :) \n");

    //for(int i = 0 ; i < 5 ;i++){
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



close(sock_fd);

    return 0;
}