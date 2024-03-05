#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include <pthread.h>


pthread_mutex_t lock;

int sum ;

char buffer[20];
int fd1;


void *read_data();
void *write_data();

int main(){

    fd1 = open("write.txt",O_CREAT | O_RDWR,0777);
    pthread_t thread1,thread2;
    pthread_mutex_init(&lock,NULL);

    printf("..");
    pthread_create(&thread1,NULL,read_data,NULL);
    pthread_create(&thread2,NULL,write_data,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);



    pthread_mutex_destroy(&lock);

    return 0 ;
}


void *read_data(){

    pthread_mutex_lock(&lock);
    //char *data[20];
    printf("Enter data to read\n:");
    scanf("%s",buffer);
    if(write(fd1,buffer,20) < 0 ){

        printf("data not written");
        pthread_exit(NULL);

    }

    printf("Data written\n");

    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);

    
    



}

void *write_data(){

    sleep(10);
   /* if(read(fd1,buffer,20) < 0 ){

        printf("failed to read data\n");
        pthread_exit(NULL);

    }
    
    */
    printf("data written = %s\n",buffer);
    pthread_exit(NULL);
}
