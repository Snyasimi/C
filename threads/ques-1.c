#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

struct rectangle{

	int length;
	int width;
};

struct cuboid{

	int height;
	int length;
	int width;
};

void *calculate_area(void *rec);
void *calculate_volume(void *cub);

int area,volume;

int main(){


	struct rectangle rect;
	struct cuboid cube;

	pthread_t thread1,thread2;

	printf("AREA\nEnter the length\n:");
	scanf("%d",&rect.length);
	printf("Enter width\n:");
	scanf("%d",&rect.width);

	
	printf("\nVolume\nEnter lenght\n:");
	scanf("%d",&cube.length);
	printf("Enter height\n:");
	scanf("%d",&cube.height);
	printf("Enter width\n:");
	scanf("%d",&cube.width);

	pthread_create(&thread1,NULL,calculate_area,(void *)&rect);
	pthread_create(&thread2,NULL,calculate_volume,(void *)&cube);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	printf("Threads Dnoe");


	return 0;
}


void *calculate_area(void *rec){

	struct rectangle *re = (struct rectangle *)rec;
	area = re->length * re->width;
	printf("The area is: %d\n",area);
	pthread_exit(0);


}
void *calculate_volume(void *cub){


	struct cuboid *cu = (struct cuboid *)cub;
	volume = cu->height * cu->length * cu->width;
	printf("The volume is: %d\n",volume);
	pthread_exit(0);
}


















