/*
 * Trying to implement roundrobin algo using a 
 * circular queue, this data structre will store 
 * data, priority
 * 
 * 
 */


#include<stdlib.h>
#include<stdio.h>


int FRONTINDX =-1;
int REARINDX = -1;
#define MAX_LENGTH  20

typedef struct{
	int priority;
	int data;
}Job;

Job JOB_QUEUE[MAX_LENGTH];

Job INVALID_JOB = {-1,-1};

Job createNode(int data,int priority){
	//Creates a node,does not insert, to insert
	//use the enqueue function
	Job newJob;
	newJob.data = data;
	newJob.priority = priority;
	printf("Data created");
	return newJob;

}

int Enqueue(Job job){

	if((REARINDX > MAX_LENGTH || REARINDX == MAX_LENGTH) && FRONTINDX > 0 ){

		REARINDX = 0;
		JOB_QUEUE[REARINDX] = job;
		REARINDX++;
		return 0;

	}
	else if((REARINDX > FRONTINDX) && FRONTINDX > 0){

		fprintf(stderr,"Overflow error,cannot add to queue as it is at full capacity\n");
		return 1;
	}

 		printf("FRONT INDX = %d\nREARINDX = %d",FRONTINDX,REARINDX);
	 if(FRONTINDX == -1 && REARINDX == -1 ){

 		printf("IM TRUE");
		FRONTINDX++;
		REARINDX++;
 		printf("FRONT INDX = %d\nREARINDX = %d",FRONTINDX,REARINDX);
		JOB_QUEUE[FRONTINDX] = job;
		return 0;
	} 

 		printf("FRONT INDX = %d\nREARINDX = %d",FRONTINDX,REARINDX);
	JOB_QUEUE[REARINDX] = job;
	REARINDX++;
	return 0;


}

Job Dequeue(){

	/*we return invalid job if theres an underlow,
	 * invalid job has a priority of -1
	 *
	 */

	if(FRONTINDX < 0){

		printf("\nUnderflow error, Cannot dequeue empty queue\n");
		return INVALID_JOB;
	}

	Job job;
	job = JOB_QUEUE[FRONTINDX];
	FRONTINDX++;

	return job;

}

int SortJobs(){

	//merge sort 
	
}


int main(int argc, char *argv[]){

	Enqueue(createNode(1,12));
	
	Job dequeued = Dequeue();

	printf("DAta is %d",dequeued.priority);
	return 0;

}
