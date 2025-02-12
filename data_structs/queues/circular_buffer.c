#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define SIZE 5

		
int read_indx = -1;
int write_indx= -1; 

int enqueue(int data);
int dequeue();

	int buffer[SIZE] = {0};


int main(){

	//printf("Write indexis %d\n",write_indx);


	//printf("Data at position 0 is %d\n",read_indx);




	//enqueue(22);
	//dequeue();
	//enqueue(45);
	//dequeue();
	//enqueue(99);
	//dequeue();
	//enqueue(77);
	//dequeue();
	//enqueue(99);
	//dequeue();
	//enqueue(67);
	//dequeue();
	//enqueue(69);
	//enqueue(96);
	//dequeue();
	//dequeue();
	//dequeue();
	//dequeue();
	//enqueue(55);
	//dequeue();
	//dequeue();
	//dequeue();
	//dequeue();
	//
	int count = 0;
	while(count < 20){

		enqueue(count);
		dequeue(count);
		count++;
		sleep(2);

	}


	//printf("Data at 0 is %d\nwtite index at:%d\nRead index at:%d\n\n", buffer[4],write_indx,read_indx);




	return 0;
}


int enqueue(int data){

	if(write_indx == -1 && read_indx == -1){

		write_indx++;
		read_indx++;

		buffer[write_indx] = data;
		printf("Data: %d written at position: %d\n",data,write_indx);

		
		return 0;
	}
	else if( (write_indx + 1) % SIZE == read_indx ){
		
		write_indx = (write_indx + 1) % SIZE;

		buffer[write_indx] = data;
		read_indx++;
		printf("Data: %d written at position: %d\n",data,write_indx);
		return 0;
	}
	else{

		write_indx = (write_indx + 1) % SIZE;
		buffer[write_indx] = data;
		printf("Data: %d written at position: %d\n",data,write_indx);
		return 0;
	}

}

int dequeue(){

	if(write_indx == -1 && read_indx == -1){

		printf("Cannot read empty queue");
		return 1;

	}
	else if( (read_indx +1 ) % SIZE > write_indx){

		printf("Cannot read old data\n");
		return 1;
	} 

	read_indx = (read_indx ) % SIZE;

	printf("Data at %d is: %d\n",read_indx, buffer[read_indx]);
	read_indx++;

	return 0;

}

