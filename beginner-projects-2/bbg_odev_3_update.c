#include <stdio.h>

/*
The sun was shining brightly in the sky. It was a beautiful   day for a picnic. Lisa and  Tom packed their      basket with sandwiches, fruits, and  drinks. They were ready to have some    fun.
142 harf
34 kelime
4 cumle
===================================================================================
Once when I was six years   old I saw a magnificent picture in a book  , called True Stories from Nature , about the primeval forest   .     It was a picture of a boa constrictor in the act of swallowing an animal. Here is a copy of the drawing .     
Cumle sayisi: 3
Kelime sayisi: 46
Harf sayýsý: 183
*/


int main() {
	
	printf("Enter here your paragraph: \n--------------------------------\n");
	
	char paragraph[1000];
	
	gets(paragraph);
	
	int sentence = 0;
	int letter = 0;
	int word = 0;
	int i = 0;
	
	
	while (paragraph[i] != '\0') {
		//cumle sayisi
		if (paragraph[i] == '.' || paragraph[i] == '?' || paragraph[i] == '!') {
			sentence = sentence + 1;
		}
		//kelime sayisi
		if (paragraph[i+1] != ' ' && paragraph[i+1] != '.' && paragraph[i+1] != ',' && paragraph[i+1] != '\0' && paragraph[i] == ' ') {
			word = word + 1;
		}
		//harf sayisi
		if (paragraph[i] >= 'A' && paragraph[i] <= 'Z' || paragraph[i] >= 'a' && paragraph[i] <= 'z') {
			letter = letter + 1;
		}
		i = i + 1;
	}	
	
	printf("\n================================\nsentence count: %d\nword count: %d\nletter count: %d\n\n", sentence, word+1, letter);
	
	
	int lettertype = 0;
	int j;
	char table[31][26];
	int x, y;
	
	for(x=0;x<31;x++){
		for(y=0;y<26;y++){
			table[x][y] = ' ';	
		}
	}
	


	//harf cesitleri
	for (j=0 ; j<=25 ; j++){
		lettertype = 0;
		i = 0;
		while (paragraph[i] != '\0') {
		if (paragraph[i] == 'A'+j || paragraph[i] == 'a'+j ) {
			lettertype = lettertype + 1;
			}
		i = i + 1;
		}
		
		
		x = 30;
		table[x][j] = 'A'+j ;
		x = 29;
		while (x >= 30-lettertype){
			table[x][j] = 'X';
			x--;
		}		
		
	}
	
	for(x=4;x<31;x++){
			for(y=0;y<25 ;y++){
				if(y==0 && x<30) {
					if(30-x < 10) printf("%d ->|", 30-x);
					else printf("%d->|", 30-x);
				}
				if(y==0 && x==30) printf("    |");
				printf("%c|", table[x][y]);	
			}
			printf("\n");
		}	
		
			
	return 0;
}
