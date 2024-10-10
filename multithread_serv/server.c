#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<errno.h>

#include<pthread.h>

char SERVER_IP[INET_ADDRSTRLEN] ={0};

int get_ip(char hostname[]){

	struct addrinfo *results;
	//get adress info of server
	int ret = getaddrinfo(hostname,NULL,NULL,&results);
	
	if(ret != 0 ){

		printf("Error getting machine information\n%s",gai_strerror(ret));
		return 1;
	}

	for(struct addrinfo *start = results; start != NULL; start = start->ai_next){

		struct sockaddr_in *addr = (struct sockaddr_in *)start->ai_addr;

		if(addr != NULL){

			inet_ntop(AF_INET,&(addr->sin_addr),SERVER_IP,INET_ADDRSTRLEN);	
			//printf("%s\n",SERVER_IP);
			//freeaddrinfo(ret);
			freeaddrinfo(start);
			break;
		}

		if(addr == NULL){

			return 1;
		}
		
	}

	return 0;

}


void *handle_client(void *sock){

	int *fd = (int *)sock;
	printf("THis is a thread,Im assigned the FD %d\nMy Thread ID is:%lu",*fd,pthread_self());
	sleep(200);
	


}



int main(){

	//get servers info
	//
	
	struct addrinfo server_addr_info;
	struct sockaddr_in SERVER_SOCKET;
	struct sockaddr_in CLNT_SOCK;


	if(get_ip("wild-wolf") != 0){

		printf("\nERROR EXITING\n");
		return 1;
	}
	
	//create a socket
	//
	int SERVER_FD = socket(AF_INET,SOCK_STREAM,0);
	
	//client sock

	//initialize addr
	SERVER_SOCKET.sin_family = AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&SERVER_SOCKET.sin_addr);
	SERVER_SOCKET.sin_port = htons(6969);
	
	if(SERVER_FD < 0 ){

		printf("Failed to create socket\n");
		return 1;
	}
	printf("SERVER FD = %d",SERVER_FD);

	//bind socket
	if(bind(SERVER_FD,(struct sockaddr *)&SERVER_SOCKET,sizeof(SERVER_SOCKET)) < 0){

		perror("Could not bind socket to address\n");
		return 1;
			
	}

	//listen for connections
	
	if(listen(SERVER_FD,5) < 0){

		perror("Failed to listen for connections\n");
		return 1;
	}
	printf("Server Listening for connections...\nPORT: 6969\nIP:%s\n",SERVER_IP);
	while(1){
	sleep(2);	
	printf("SERVER FD = %d\n",SERVER_FD);
		int new_sock = accept(SERVER_FD,NULL,NULL);

		if(new_sock < 0){

			printf("Connection refused, dropped\n");
		}

		printf("Connected\n");
		pthread_t thread_id;
		
		pthread_create(&thread_id,NULL,handle_client,(void *)&new_sock);
		printf("Connection assigned a thread\n THREAD_ID:%lu___________",thread_id);
	}



return 0;	
}
