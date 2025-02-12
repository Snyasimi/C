#include<stdio.h>
#include<stdlib.h>


int main(){


int *myarray = (int *)malloc(5*sizeof(int));

for(int i = 0 ; i< (int)sizeof(myarray) ; i++){

	myarray[i] = i;
	printf("%d\n",*myarray);

}





return 0;

}
