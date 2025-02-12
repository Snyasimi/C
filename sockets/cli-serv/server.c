#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
char username[]="foobaz";
char password[]="foobaz123";


int read_file( char *buffer){
	
	int file = open("./hello.txt",O_RDONLY,0777);
	
	if( file < 0 ){
		
		perror("Could not open file\n");
		return 1;

	}

	if(read(file,buffer,1024) < 0 ){

		perror("Could not read from file\n");
		return 1;
	}
//	printf("Buffer populated with\n %s\n and whr has: %s\n",buffer,whr);
	return 0;

}
			
int main(){

	
	char buf[1024] = {0};
	
	char *bufptr = buf;

	read_file(bufptr);

	//printf("\nBuffer has%p\n %s\n",bufptr,buf);
	

	struct sockaddr_in server_soc;

	server_soc.sin_family = AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&server_soc.sin_addr);
	server_soc.sin_port  = htons(6969);

	printf("Username is %s\nPassword is %s\n",username,password);

	int server_fd = socket(AF_INET,SOCK_STREAM,0);

	if(server_fd < 0){ perror("Error creating socket\n"); return 1;}

	if(bind(server_fd,(struct sockaddr *)&server_soc,sizeof(server_soc))<0){
		
		perror("Erro binding socket\n"); 
		return 1;
	}
	printf("Server Binded\n");

	if(listen(server_fd,5) < 0){

		perror("Error listening for connections\n");
	}

	printf("Server listeing on port 6969 on 127.0.0.1\n");

	int new_connection = accept(server_fd,NULL,NULL);

		
	if(new_connection < 0){

		printf("Error estalishing connection\n");
		
		return 1;	
	}

printf("A client Connected..\n");
sleep(2);
	
		

		char buffer[] = "\nEnter email and password\nEmail:\n";
		char email[50];
		char password[50] = "Enter Password";

		if(send(new_connection,(void *)&buffer,sizeof(buffer),0) < 0 ){

			perror("Error while sendling message\n");
			return 1;
		}

		memset(buffer,0,sizeof(buffer));
		printf("Waiting for response..\n");
		if(recv(new_connection,(void *)&email,sizeof(email),0) < 0){

			perror("Error recieving Email\n");
			return 1;
		}
		printf("Email: %s\n",email);
		
		send(new_connection,(void *)&password,sizeof(password),0);
		memset(password,0,sizeof(password));

		printf("Waiting for password..\n");
		if(recv(new_connection,(void *)&password,sizeof(password),0) < 0){

			perror("Error recieving message\n");
			return 1;
		}
		
		printf("Password: %s\n",password);
		
		printf("Password OK....\nSending file Hello.txt to client\n\n");
		sleep(2);

		size_t bytes_snt ={0};
		size_t bts ={0};

		while(bytes_snt != 1024){
		
			bts = send(new_connection,(void *)&buf,sizeof(buf),0);

			bytes_snt += bts;
		}
		sleep(2);
		printf("File sent\n");
		

		
		
		
	




	return 0;
	


}

