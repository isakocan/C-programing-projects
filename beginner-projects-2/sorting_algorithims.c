#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubblesort(int array[], int size){
	int i=0, j, flag=1,tmp;
	while(i<10){
		flag=0;
		for(j=0;j<10-i;j++){
			if(array[j+1] < array[i]){
				tmp=array[j];
				array[j]=array[j+1];
				array[j+1]=tmp;
				flag=1;
			}
		}
		i=i+1;
	}
	printf("\n\n\nNew list with bubble sorted!\n{ ");
	for(i=0;i<9;i++){
		printf("%d, ", array[i]);
	}
	printf("%d }", array[9]);
}

void selectionsort(int array[], int size){
	int i, j, min,tmp;
	for(i=0;i<9;i++){
		min=i;
		for(j=i+1;j<10;j++){
			if(array[j] < array[min]){
				min = j;
			}
		}
		tmp=array[i];
		array[i]=array[min];
		array[min]=tmp;
	}
	printf("\n\n\nNew list with selection sorted!\n{ ");
	for(i=0;i<9;i++){
		printf("%d, ", array[i]);
	}
	printf("%d }", array[9]);
}

void insertionsort(int array[], int size){
	int i, j, tmp;
	for(i=1;i<10;i++){
		j=i;
		tmp=array[i];
		while(j>0 && tmp<array[j-1]){
			array[j]=array[j-1];
			j=j-1;
		}
		array[j]=tmp;
	}
	printf("\n\n\nNew list with insertion sorted!\n{ ");
	for(i=0;i<9;i++){
		printf("%d, ", array[i]);
	}
	printf("%d }", array[9]);
}


int main(){
	
	//create a random array
	int i, array[10];
	srand(time(NULL));
	
	for(i=0;i<10;i++){
		array[i] = (rand()%9)+1;
	}
	
	//show array
	printf("Random list\n{ ");
	for(i=0;i<9;i++){
		printf("%d, ", array[i]);
	}
	printf("%d }", array[9]);
	
	bubblesort(array, 10);
	selectionsort(array, 10);
	insertionsort(array, 10);
	
	return 0;
}
