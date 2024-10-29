#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int i, j, size;
	int n;
	int *dizi;
	printf("Sayi giriniz: ");
	scanf("%d", &n);
	
	dizi = (int*) calloc(2,sizeof(int));
	i=0;
	size=2;
	dizi[i] = n;
	
	while(dizi[i]!=1){
			
		if(n % 2 == 1){
			n = (3*n)+1;
		}
		else{
			n = n/2;
		}
		
		i++;
		
		if(i>=size){
			size *= 2;
			dizi = (int*) realloc (dizi, size * sizeof(int));
		}
		
		dizi[i] = n;
	
	}
	
	printf("Dizinin elemanlari: ");
	for(j=0;j<=i;j++){
		printf("%d ", dizi[j]);
	}
	printf("\nDizinin eleman sayisi: %d\nDizinin hafizada kapladigi alan: %d", i+1, size);
	
	free(dizi);
	
	return 0;
}
