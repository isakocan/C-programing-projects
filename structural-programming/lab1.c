#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int i,j,k;
	int n,m;
	int **pol1, **pol2, *sonuc;
	
	//1. polinom
	printf("1. polinomun terim sayisini giriniz: ");
	scanf("%d", &n);
	pol1 = (int**) malloc(2*sizeof(int*));
	for(i=0;i<2;i++){
		*(pol1+i) = (int*) malloc(n*sizeof(int));
	}
	for(i=0;i<n;i++){
		printf("%d. terimin ust ve katsayisini giriniz: \n", i+1);
		scanf("%d %d", &pol1[0][i], &pol1[1][i]);
	}
	
	//2. polinom
	printf("2. polinomun terim sayisini giriniz: ");
	scanf("%d", &m);
	pol2 = (int**) malloc(2*sizeof(int*));
	for(i=0;i<2;i++){
		*(pol2+i) = (int*) malloc(m*sizeof(int));
	}
	for(i=0;i<m;i++){
		printf("%d. terimin ust ve katsayisini giriniz: \n", i+1);
		scanf("%d %d", &pol2[0][i], &pol2[1][i]);
	}
	
	
	//carpým sonucu
	sonuc = (int*) calloc(20,sizeof(int));
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			k = pol1[0][i] + pol2[0][j];
			*(sonuc + k) += pol1[1][i] * pol2[1][j];
		}
	}
	
	//ekrana yazdýrma
	printf("Carpim polinomu: ");
    for (i = 19; i >= 0; i--) {
        if (*(sonuc + i) != 0) {
            printf("(%d)x^(%d) + ", *(sonuc + i), i);
        }
    }
		
	return 0;
}
