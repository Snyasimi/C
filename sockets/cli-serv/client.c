#include<stdio.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>


int main(){

	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
	server_addr.sin_port = htons(6969);

	int client_fd = socket(AF_INET,SOCK_STREAM,0);

	if(client_fd < 0 ){

		perror("Failed to create socket\n");
	}

	if( connect(client_fd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0 ){

		perror("Could not connect to server\n");
		return 1;

	}
	printf("Connected to server\n");
	
	char data[50];
	char buffer[50];
	if( recv(client_fd,(void *)&buffer,sizeof(buffer),0) < 0){

		perror("Error reciving msg from server\n");
		return 1;
	}

	printf("%s",buffer);
	memset(buffer,0,sizeof(buffer));

	scanf("%s",&data);

	if( send(client_fd,(void *)data,sizeof(data),0) == 0 ){
	
		perror("Error sendinng\n");
		return 1;
	}

	memset(data,0,sizeof(data));
	if( recv(client_fd,(void *)data,sizeof(data),0) < 0){

		perror("Could not recieve message\n");
		return 1;
	}
	sleep(2);

	printf("%s\n",data);
		
	memset(data,0,sizeof(data));
	scanf("%s",&data);

	if( send(client_fd,(void *)data,sizeof(data),0) < 0 ){

		perror("Could not send data");
		return 1;
	}

	printf("Password sent\n");
	sleep(1);
	printf("Password OK......\nRecieveing file from server...\n");

	size_t bytes_recv;
	char txt_buf[1024];
	size_t bts ={0};
	//while(bytes_recv != 1024){

		bts = recv(client_fd,(void *)&txt_buf,sizeof(txt_buf),0);
		bytes_recv += bts;
		printf("\n\n\n\t--------FILE CONTENT-------\t\n %s\n",txt_buf);
	//}









	return 0;
}
