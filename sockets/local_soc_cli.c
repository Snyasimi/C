#include<stdio.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<string.h>

int main(){

    struct sockaddr_un client,server;

    client.sun_family = AF_LOCAL;
    //client.sun_path = './comms';

    char filename[] = "./comms";
    strncpy(client.sun_path,filename,sizeof(filename));


    server.sun_family = AF_LOCAL;
    char Filename[] = "./comms";
    strncpy(server.sun_path,Filename,sizeof(filename)-1);

    int sock_fd = socket(AF_LOCAL,SOCK_STREAM,0);

    
    if(connect(sock_fd,(struct sockaddr *)&server,sizeof(server)) < 0 ){
        printf("Error connecting\n");
        perror("ERR");
        return 1;
    }

    printf("Connected to server..\n");

   //="Hello server..";
    sleep(1);

    

    //for(int i = 0 ; i < 5 ;i++){
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
    //sleep(10);





close(sock_fd);

return 0;

}