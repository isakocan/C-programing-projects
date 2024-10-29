#include <stdio.h>
 

int main() {
	
	int gunsayisi;
	printf("Gun sayisi gir: ");
	scanf("%d", &gunsayisi);
	
	int hisse[gunsayisi];
	int i;
	for(i=0;i<gunsayisi;i++){
		printf("%d. gunun hisse fiyatini gir: ",i+1);
		scanf("%d", &hisse[i]);	
	}
	
	
	int alinangun, satilangun;
	int kar, maxkar=0;
	int t = gunsayisi-2 , j, k;
	
	for(j = gunsayisi-1 ; j>=1 ; j = j-1){
		
		for(k = t ; k >= 0 ; k = k-1){
			
			kar = hisse[j] - hisse[k];
			
			if (maxkar <= kar) {
				maxkar = kar;
				alinangun = k;
				satilangun = j;
			}
		}
		
		t = t-1;
		
	}
	
	
	if (maxkar == 0) printf("\n===========================\nHicbir gun karli olmuyor. \nKar: 0");
	else printf("\n==============================================\n%d. gun hisseyi aliriz.\n%d. gun hisseyi satariz.\nKar: %d", alinangun+1, satilangun+1, maxkar);

	
	return 0;
}
