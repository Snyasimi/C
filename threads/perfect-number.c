#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>
#include<pthread.h>


 struct range {

	int start;
	int end;
	int number;
};


void find_perfect(int max);


int perfect_number(int number);

pthread_mutex_t lock;

long SUM,NUMBER = 50;

int main(){
	pthread_mutex_init(&lock,NULL);



	//pthiread_create(thread1,NULL,add_divisors
	//find perfect number

	//perfect_numbier(100);
	//
	find_perfect(500);

	pthread_mutex_destroy(&lock);
	return 0;	




}

void find_perfect(int max){

	//printf number if its a perfect number
	for(int i = 1 ; i <= max  ; i++){
	
		if(perfect_number(i)){
		
			printf("[%d] is Perfect\n",i);
		}

		continue;
	} 
	
	printf("\nDone\n");

	return;

}


void add_divisors(void *range){

	// if start >= half, dont execute
	//loop from start index to end while adding sum
	long Sum  = 0;
	
	struct range *Range = (struct range *)range;

	int start = Range->start;
	int end = Range->end;
	int number = Range->number;

	if( start >= end){
	
		pthread_exit(NULL);
	}

	for(int i = start; start<=end ; start++){
	
		if( number % i == 0 ){
		
			Sum += i;
		}
		continue;
	}

	pthread_mutex_lock(&lock);
	sum += Sum;
	pthread_mutex_unlock(&lock);
	pthread_exit(0);
}


int perfect_number(int Num){

	// loop from start to 0-n
	// check if n is a divisor of number
	// if is divisor sum += n
	// if sum == number,is perfect
	long  sum = 0;
	long i =1;

	//divide number by 2 
	//then divide 2 again 
	//one half one thread other half other thread
	
	struct range first_half,second_half;

	first_half.start = 1;
	first_half.end = (int)(Num / 2) / 2;
	first_half.number = Num;

	second_half.start = (int)(Num /2) / 2;
	second_half.end = (int)Num / 2;
	second_half.number = Num;

	pthread_t thread1,thread2;

	pthread_create(thread1,NULL,add_divisors,(void *)&first_half);
	pthread_create(thread1,NULL,add_divisors,(void *)&second_half);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	/*

	for(i; i <= number /2 ;i++ ){
	
		if (number  % i == 0){
		//lock mutex
			sum += i;
			//printf("[%d]->divisible\n",i);
		//unlock	//
		}
		//i++;
		continue;
	}
	*/


	if(sum == number){
	
		//printf("[%d] Its Perfect\n",number);
		return true;
	}

	//printf("[%d] Not perfect\n",number);

	return false;

}
