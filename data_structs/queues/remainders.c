//Concepts of modular arithmentic
//
//find modular congluents

#include<stdio.h>

typedef struct{

	int first_number;
	int second_number;
}pair;

int main(){


	int mod_number = 20;
	int total_numbers;

	printf("Enter the number to mod by:\n");
	scanf("%d",&mod_number);
	printf("How many numbers do you want to test?\n");
	scanf("%d",&total_numbers);

	for(int i = 1 ; i < total_numbers ; i++){
	
		int first_number = i;
		printf("%d iter\n", i);
		for(int j = 1; j < total_numbers ; j++){
			printf("Testing %d and %d\n",i,j);

			if( (i % mod_number) == (j % mod_number) ){

				printf("These two yield the same reminder {%d, %d} when modded by %d\n",i,j,mod_number);
			}
		}

	}

}
