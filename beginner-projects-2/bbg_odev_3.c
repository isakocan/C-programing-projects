#include <stdio.h>

int main() {
	
	char paragraph[1000];
	int sentence = 0;
	int letter = 0;
	int word = 1;
	int i = 0;
	int letter_type;
	int j;
	
	printf("Enter a paragraph here: \n--------------------------------\n");
	gets(paragraph);
	
	while (paragraph[i] != '\0') {
		//cumle sayisi
		if (paragraph[i] == '.' ) {
			sentence = sentence + 1;
		}
		//kelime sayisi
		if (paragraph[i] == ' ' && paragraph[i+1] != ' ' ) {
			word = word + 1;
		}
		//harf sayisi
		if (paragraph[i] >= 'A' && paragraph[i] <= 'Z' || paragraph[i] >= 'a' && paragraph[i] <= 'z') {
			letter = letter + 1;
		}
		i = i + 1;
	}
	
	printf("\n================================\nSentence count: %d\nWord count: %d\nLetter count: %d\n", sentence, word, letter);
	
	//harf cesitleri
	for (j=0 ; j<=25 ; j++){
		
		letter_type = 0;
		i = 0;
		
		//harf cesidinin miktari
		while (paragraph[i] != '\0') {
			if (paragraph[i] == 'A'+j || paragraph[i] == 'a'+j ) {
				letter_type = letter_type + 1;
			}
			i = i + 1;
		}
		
		//yazdýrma
		if (letter_type >= 10){
			printf("\n%c: %d -> ", 'A'+j, letter_type);
		}
		else{
			printf("\n%c: %d  -> ", 'A'+j, letter_type);
		}
		
		for (i = 0 ; i < letter_type ; i++ ){
			printf("%c", '*');
		} 
	}
	
	
	return 0;
}
