#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>


int main(){

	struct addrinfo *res,*info;
	struct addrinfo hint;
	struct sockaddr_in server_sock;
	int sock_fd;

	struct sockaddr client;

	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_flags = AI_ADDRCONFIG;
	printf("hi\n");
	if(getaddrinfo("wild-wolf",NULL,&hint,&res) < 0 )
	{
		printf("error getting host");
		return 0 ;
		}
	
	char ADDR[INET_ADDRSTRLEN];
	for(struct addrinfo *node = res; node != NULL; node = node->ai_next){

		struct sockaddr_in *sock_addr = (struct sockaddr_in *)node->ai_addr;
		inet_ntop(node->ai_family,&(sock_addr->sin_addr),ADDR,INET_ADDRSTRLEN);
		printf("%s\n",ADDR);

		//create socket and exit loop
		
		sock_fd  = socket(AF_INET,SOCK_STREAM,0);
		if (sock_fd <0){
				
				perror("Error creating socket\n");
			}
		printf("%d\n",sock_fd);	
		server_sock.sin_family = node->ai_family;
		
		//inet_ntop(res->ai_family,&(sock_addr->sin_addr),server_sock.sin_addr, INET_ADDRSTRLEN);

		server_sock.sin_addr = sock_addr->sin_addr;
		server_sock.sin_port = htons(8000);

		printf("Socket created\n");
		break;


		}
		
		if(bind(sock_fd,(struct sockaddr *)&server_sock,res->ai_addrlen) < 0 ){

				printf("Error binding socket %d",sock_fd);
				perror("Error");
				return 1;
		}

		printf("SOket binded %d",sock_fd);

		if(listen(sock_fd,5) < 0 ){

				perror("Failed to listen for connections\n");
			}

		printf("\nWaiting connections...\n");
	
		int new_connection = accept(sock_fd,NULL,NULL);

		if(new_connection < 0 ){
				perror("Error");
				printf("Error establishing\n");
			}
		printf("Client connected ");
		while(1){

			char msg_buffer[10];
			recv(new_connection,(void *)msg_buffer,sizeof(msg_buffer),0);
			printf("%s",msg_buffer);
			
		}

		printf("done");

	close(sock_fd);
	close(new_connection);
	return 0;
	}
