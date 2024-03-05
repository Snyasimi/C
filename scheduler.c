// TRYING TO REPLICATE PRIORITY QUEUES :)
//
#include<stdio.h>
#include<stdlib.h>


int numberOfJobs = 0;
int jobEnd =-1,jobFront = -1;
typedef struct {

	int priority;
	int data;
}job;

#define INVALIDJOB {-1,-1};
#define MAX_SIZE 20
job invalidJob = INVALIDJOB;


job Jobs[MAX_SIZE];


job createJob(int priority,int data){

	if(priority == 0 || data == 0){
	
		perror("Couldn't create job, too few arguments");
		return invalidJob;
	}

	job newJob;
	newJob.priority = priority;
	newJob.data = data;
	numberOfJobs++;
	return newJob;

}



int enqueueJob(job Job,job jobArray[]){

	if(jobEnd > MAX_SIZE - 1){

		perror("OVER FLOW JOB QUEUE FULL");
		return -1;//failure
	
	}

	else if(jobFront == -1 && jobEnd == -1){
	
		jobFront++;
		jobEnd++;
	}

	jobArray[jobEnd] = Job;
	jobEnd++;

	return 0;//success

}

job dequeueJob(job Jobs[]){

	if(jobEnd < 0){
	
		perror("UNDERFLOW,NO JOBS IN QUEUE");
		return invalidJob;
	}

	job temp = Jobs[jobFront];
	jobFront++;

	return temp;

}




int highestPriority(job Jobs[]){

	int highestPriorityJobIndx = 0;

	for(int i = 0 ; i < MAX_SIZE ; i++){
	
		if(Jobs[i].priority > Jobs[highestPriorityJobIndx].priority){

			highestPriorityJobIndx = i; 	

		}

	}

	return highestPriorityJobIndx;

}

void viewJobs(job Job[]){

	//looping through array INDEX STARTS FROM 1
	for(int i = 1 ; i <= numberOfJobs ; i++){
	
		printf("{Job number -> %d, Job priority->%d, Job data->%d},",i,Job[i].priority,Job[i].data);
	}
	return;
}



int main(){


	enqueueJob(createJob(2,5),Jobs);

	
enqueueJob(createJob(3,5),Jobs);

enqueueJob(createJob(4,5),Jobs);
enqueueJob(createJob(10,5),Jobs);
enqueueJob(createJob(4,5),Jobs);

printf("\n| highest priority job = %d |\n",highestPriority(Jobs));
viewJobs(Jobs);


	return 0;


}
