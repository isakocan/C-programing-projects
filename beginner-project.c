#include <stdio.h>
#include <math.h>

/*
  Made by https://github.com/DeXotaK
  Uploaded on 20.09.2023
*/

void primenf(){
	
	int number;
	printf("\n________________________________\n\nWelcome to the prime number finder!\nEnter the number here: ");
	scanf("%d", &number);
	printf("\nCalculating.\nCalculating..\nCalculating...\n\n");
	int x;
	int i;
	for(i=2;i<number;i++){
	
		if(number % i == 0){
			
		x = 0;
		break;
		}
		x = 1;	
	}
	
	if(x) {	
		printf("This number is prime.\n________________________________");
	}
	else{
		printf("This number is not prime.\n________________________________");
	}
	printf("\n\n\n\n\n\n\n\n\n\n"); 
}




int	prime(int number){
	
	int i;
	if(number == 1){
		return 0;
	}
	
	for(i = 2 ; i < number ; i++){
		
		if (number % i == 0){
			
			return 0;
		}
	}
	return 1;	
}



void divisor() {
	
	int number;
	printf("\n________________________________\n\nWelcome to the tool to find the divisors of a number!\nEnter the number here: ");
	scanf("%d", &number);
	printf("\nCalculating.\nCalculating..\nCalculating...\n\n");	
	int i,n;
	int exactdiv[number];
	
	printf("Integer divisors of the number\n-----------------------------\n");
	for(i=1,n=0; i<=number ; i++){	
		if (number % i == 0) {
			exactdiv[n] = i;
			n++;
			printf("%d -%d\n", i,i);
			
			}
		}
		
	printf("\nPrime divisors of the number\n-----------------------------\n");	
	
	int a = n;
	for (n=0; n < a; n++){
	
		if (prime(exactdiv[n])) {
		
			printf("%d\n", exactdiv[n]);
		}
	}
	if(number == 1) printf("This number has no prime divisor!\n\n");
	
	printf("\n\n\n\n\n\n\n\n\n\n"); 
}

void calculator() {
	
	int number, i; 
	int total = 0;
	float totald = 1.0;
	printf("\n-------------\nCalculator\n-------------\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n\n\n\n\n\n\n\nEnter here: ");
	scanf("%d", &i);
	float temp, divt = 1.0;
	
	switch(i){
		
	case 1:
	for (i=0 ; ; i++) {
		
		if (i==0) printf("\nEnter as many numbers as you want. Enter the number 0 to end.\n");
		printf("Enter a number: ");
		scanf("%d", &number);
	
		if(number == 0) {	
			break;
		}		
		total = total + number;	
	}
	printf("Total of Numbers: %d\n\n", total);
	break;
	
	case 2:
	printf("\nEnter as many numbers as you want. Enter the number 0 to end.\n");
	for (i=0 ; ; i++) {
	 
		printf("Enter a number: ");
		scanf("%d", &number);
	
		if(number == 0) {	
			break;
		}		
		total = total - number;	
		if (i==0) total = -total;
	}
	printf("Total of Numbers: %d\n\n", total);
	break;		
	
	case 3:
	total = 1;
	for (i=0 ; ; i++) {
		
		if (i==0) printf("\nEnter as many numbers as you want. Enter the number 1 to end.\n");
		printf("Enter a number: ");
		scanf("%d", &number);
	
		if(number == 1) {	
			break;
		}		
		total = total * number;	
	}
	printf("Total of Numbers: %d\n\n", total);
	break;	
	
	case 4:
	for (i=0 ; ; i++) {	
		if (i==0) printf("\nEnter as many numbers as you want. Enter the number 1 to end.\n");
		printf("Enter a number: ");
		scanf("%d", &number);
		if(i==0) {
			temp = number;
			continue;
		}
		if(number == 1) {	
			break;
		}
		else if(number == 0){
			printf("Indivisible to zero!");
			divt = 0;
			break;
		}		
		divt = temp / number;	
		temp = divt;
	}
	printf("Total of Numbers: %.2f\n\n", divt);
	break;	
		
	default:
	printf("\nYou entered a wrong number. Please try again.\n");
	break;
	}	
}

void odd_even() {
	
	int number, i, n, total = 0;
	printf("\n________________________________\n\nWelcome to the odd-even number addition tool!\nEnter the number here: ");
	scanf("%d", &number);
	printf("\nCalculating.\nCalculating..\nCalculating...\n\n");	
	if (number % 2 == 1) printf("\nYour number is odd.\n");
	else if (number % 2 == 0) printf("\nYour number is even.\n");
	else printf("\nYour number is even.\n");	
	printf("\nEven numbers up to your number\n---------------------------------\n\n");
	for(i=0; i<=number; i++) {
		
		if (i % 2 == 1) {
			
			continue ;
		}
		
		total = total + i;
		printf("%d ", i);
		if (i == 0) continue;
		else if (i % 10 == 0) printf("\n");	
	}
	printf("\nTotal ---> %d", total);
	total = 0;
	printf("\n\nOdd numbers up to your number\n---------------------------------\n\n");
	for(i=0, n=1; i<=number; i++, n++) {
		
		if (i % 2 == 0) {
			
			continue ;
		}
		
		total = total + i;
		printf("%d ", i);	
		if (n % 5 == 0 || i == number) printf("\n");
	}
	printf("\nTotal ---> %d\n", total);
}


int fact() {
	
	int i=1, number, a=1;
	
	printf("\nEnter a number: ");
	scanf("%d",&number);
	
	while (i <= number) {
		
		a = a * i;
		i++;
	}
	if (a <= 0) {
		printf("\nThe maximum number limit has been exceeded! Please enter a smaller number.\n");
		return 0;
	}
	printf("\nFactorial of the number you enter\n---------------------------------\n---> %d! = %d\n", number, a);
}


int fibonacci() {
	int first, second, number, i, temp, n;
	first = 1;
	second = 1;
	printf("\n<- Fibonacci number generator ->\n\nEnter a number: ");
	scanf("%d", &number);
	if (number == 1 ){
	printf("\n1");
	return 0;	
	} 
	else if (number == 0) {
		return 0;
	}
	printf("\n%d %d ", first, second);
	
	for(i=0, n=1 ; i < number-2 ; i++, n++) {
	
		temp = second;
		second += first;
		first = temp;
		if (second <= 0) {
			printf("\n\nThe maximum number limit has been exceeded! Please enter a smaller number.\n");
			break;
		}
		printf("%d ", second);
		if (n % 10 == 0) printf("\n");		
	}
	printf("\n");
}


void digit(){
	
	int n;
	int digit = 0;
	int total = 0;
	
	printf("\nWizard to find digits and calculate the sum of digits\n-----------------------------------------------------\n\nEnter a number: ");
	scanf("%d",&n);
	
	do {
	total = total + (n % 10);
	digit ++;
	n = n / 10;
	}
	while (n > 0);

	printf("\nThe number is a %d-digit number.\nThe sum of the digits of the number is %d.\n\n", digit, total);	
}



void sort() {
	
	int size, i, j, temp;
	printf("\n\nHow many numbers will you enter?\nEnter a number: ");
	scanf("%d", &size);
	int numbers[size];
	printf("Now enter your numbers one by one\n\n");
	for (i=0; i < size ; i++){
		printf("Enter a number: ");
		scanf("%d", &numbers[i]);
	}
	
	for (j=1; j < size ; j++){
		
		for(i=0; i < size-j ; i++){
	
			if (numbers[i] > numbers[i+1]){
		
				temp = numbers[i];
				numbers[i] = numbers[i+1];
				numbers[i+1] = temp;
			}	
		}
	}
	printf("\nYour numbers are sorted!\n-------------------------\n{ ");
	for (i = 0, j = 1 ; i < size; i++, j++){	
		if (i == size-1) {
			printf("%d ", numbers[i]);
			break;
		}
		printf("%d, ", numbers[i]);
		if (j % 10 == 0) printf("\n");
   	}
	printf("}\n\n");	
}


int root() {
	int a,b,c, degree;
	float delta;
	float x1, x2, x;
	
	printf("\n<- Mathematics equation root finder ->\n\nWizard to find the root of 1st order and 2nd order equations.\nHow many degrees is your equation?\n\nEnter 1 or 2 : ");
	scanf("%d", &degree);
	
	if (degree == 1) {
		
		printf("\nYour equation will be in the format ax+b.\nEnter the value of equation a = ");
		scanf("%d", &a);
		printf("Enter the value of equation b = ");
		scanf("%d",&b);
		
		if (a == 0) {
			printf("\nYou entered a wrong number! Please try again.\n(The number a cannot take the value 0 !)\n\n");
			return 0;
		}
		else if (b < 0) {
			printf("\nYour equation: %dx%d\n", a, b);
			x = (-b) / (1.0*a) ;
			printf("\nThe root of the equation is x = %.2f\n\n", x);
		}
		else if (b == 0) {
			printf("\nYour equation: %dx\n", a);
			x = 0;
			printf("\nThe root of the equation is x = %.2f\n\n", x);
		}
		else {
		printf("\nYour equation: %dx+%d\n", a, b);	
		x = (-b) / (1.0*a);
		printf("\nThe root of the equation is x = %.2f\n\n", x);		
		}
		
		
	}
	
	else if (degree == 2) {
		
		printf("\nYour equation will be in the format ax^2 +bx +c.\nEnter the value of equation a = ");
		scanf("%d", &a);
		printf("Enter the value of equation b = ");
		scanf("%d",&b);
		printf("Enter the value of equation c = ");
		scanf("%d",&c);
	
		if (a == 0) {
			printf("\nYou entered a wrong number! Please try again.\n(The number a cannot take the value 0 !)\n\n");
			return 0;
		}
		else if (b < 0 && c < 0) {
			printf("\nYour equation: %dx^2 %dx %d\n", a, b, c);
		}
		else if (b < 0 && c == 0) {
			printf("\nYour equation: %dx^2 %dx\n", a, b);	
		}
		else if (b < 0) {
			printf("\nYour equation: %dx^2 %dx +%d\n", a, b, c);	
		}
		else if (b == 0 && c < 0) {
			printf("\nYour equation: %dx^2 %d\n", a, c);
		}
		else if (b == 0 && c == 0) {
			printf("\nYour equation: %dx^2\n", a);
		}
		else if (c < 0) {
			printf("\nYour equation: %dx^2 +%dx %d\n", a, b, c);	
		}
		else if (c == 0) {
			printf("\nYour equation: %dx^2 +%dx\n", a, b);	
		}
		else {
		printf("\nYour equation: %dx^2 +%dx +%d\n", a, b, c);			
		}
			
		delta = (b*b)- ((4.0*a)*c) ;
		
		if(delta<0){
		printf("\nThe equation has no rational number root!\n\n");	
		}
		
		else if(delta==0){	
			x = (-b + sqrt(delta)) / 2.0*a;
			printf("\nThe root of the equation is x = %.2f\n\n", x);
		}
		
		else {
		x1 = (-b + sqrt(delta)) / (2.0*a);
		x2 = (-b - sqrt(delta)) / (2.0*a);
		printf("\nThe roots of your equation\nx1: %.2f \t x2: %.2f\n\n",x1,x2);
		}	
	}
	
	else {
		printf("\nYou entered a wrong number! Please try again.\n\n");
	}	
}

int mystrlen(char array[]) {
	
	int i, length = 0;
	for(i=0; array[i] != '\0'; i++){
		length++;
	}
	return length;
}


void reverse(){
	
	char name[200];
	printf("\nWizard to reverse what you type\n\nEnter a word: ");
	scanf("%s", name);
	printf("\nThe writing is reversed!\n---> ");
	int length = mystrlen(name);
	int i;
	for (i = length ; i >= 0 ; i--){
		printf("%c", name[i]);
	}
	printf("\n\n");	
}







int main() {
	
	

	printf("Hello There!\n\n==============================================================================\n->This program is a program that includes C programming language starter projects.\n->You can select the desired operation from the menu.\n->You can type the numbers written at the beginning of the operations and press *enter*.\n->You can press *0* to end the program.\n==============================================================================\n");
	
	while(1){
	printf("\nMenu\n--------------------------------\n1. Prime number finder\n2. Finding divisors of a number\n3. Calculator\n4. Odd-Even number finder\n5. Factorial calculator\n6. Fibonacci number generator\n7. Number of digits and digit sum calculation\n8. Number sort\n9. Math equation root finder\n10. Reverser\n\nPress *0* to end the program.");
	printf("\n\n\n\n\n\n\nEnter the number here: ");
	int a, yesno;
	scanf("%d",&a);
	
	
	if(a == 0){
		printf("\n\n========================\n\nThe program shuts down.\nThe program shuts down..\nThe program shuts down...\n\n========================\n\n\n");
		break;
	}

	switch(a){
		
		case 0:
		break;
		
		case 1:
		while(1){
		primenf();
			while(1){
			printf("\nDo you want to continue?\nYes(1) or No(0)?\n\n\n\n\n\nEnter here: ");
			scanf("%d", &yesno);
			if(yesno == 0 || yesno == 1) break;
			else printf("You entered a wrong number. Please try again.\n");
			}
			if (yesno == 0) break;

		}
		break;
		
		case 2:
		while(1){
		divisor();
			while(1){
			printf("\nDo you want to continue?\nYes(1) or No(0)?\n\n\n\n\n\nEnter here: ");
			scanf("%d", &yesno);
			if(yesno == 0 || yesno == 1) break;
			else printf("You entered a wrong number. Please try again.\n");
			}
			if (yesno == 0) break; 
		}
		break;
		
		case 3:
		while(1){
		calculator();
			while(1){
			printf("\nDo you want to continue?\nYes(1) or No(0)?\n\n\n\n\n\nEnter here: ");
			scanf("%d", &yesno);
			if(yesno == 0 || yesno == 1) break;
			else printf("You entered a wrong number. Please try again.\n");
			}
			if (yesno == 0) break;
		}	
		break;
		
		case 4:
		while(1){
		odd_even();
			while(1){
			printf("\nDo you want to continue?\nYes(1) or No(0)?\n\n\n\n\n\nEnter here: ");
			scanf("%d", &yesno);
			if(yesno == 0 || yesno == 1) break;
			else printf("You entered a wrong number. Please try again.\n");
			}
			if (yesno == 0) break;
		}	
		break;
		
		case 5:
		while(1){
		fact();
			while(1){
			printf("\nDo you want to continue?\nYes(1) or No(0)?\n\n\n\n\n\nEnter here: ");
			scanf("%d", &yesno);
			if(yesno == 0 || yesno == 1) break;
			else printf("You entered a wrong number. Please try again.\n");
			}
			if (yesno == 0) break;
		}	
		break;
		
		case 6:
		while(1){
		fibonacci();
			while(1){
			printf("\nDo you want to continue?\nYes(1) or No(0)?\n\n\n\n\n\nEnter here: ");
			scanf("%d", &yesno);
			if(yesno == 0 || yesno == 1) break;
			else printf("You entered a wrong number. Please try again.\n");
			}
			if (yesno == 0) break;
		}	
		break;
		
		case 7:
		while(1){
		digit();
			while(1){
			printf("\nDo you want to continue?\nYes(1) or No(0)?\n\n\n\n\n\nEnter here: ");
			scanf("%d", &yesno);
			if(yesno == 0 || yesno == 1) break;
			else printf("You entered a wrong number. Please try again.\n");
			}
			if (yesno == 0) break;
		}	
		break;
		
		case 8:
		while(1){
		sort();
			while(1){
			printf("\nDo you want to continue?\nYes(1) or No(0)?\n\n\n\n\n\nEnter here: ");
			scanf("%d", &yesno);
			if(yesno == 0 || yesno == 1) break;
			else printf("You entered a wrong number. Please try again.\n");
			}
			if (yesno == 0) break;
		}	
		break;
		
		case 9:
		while(1){
		root();
			while(1){
			printf("\nDo you want to continue?\nYes(1) or No(0)?\n\n\n\n\n\nEnter here: ");
			scanf("%d", &yesno);
			if(yesno == 0 || yesno == 1) break;
			else printf("You entered a wrong number. Please try again.\n");
			}
			if (yesno == 0) break;
		}	
		break;
		
		case 10:
		while(1){
		reverse();
			while(1){
			printf("\nDo you want to continue?\nYes(1) or No(0)?\n\n\n\n\n\nEnter here: ");
			scanf("%d", &yesno);
			if(yesno == 0 || yesno == 1) break;
			else printf("You entered a wrong number. Please try again.\n");
			}
			if (yesno == 0) break;
		}	
		break;

		default:
		printf("\n\n===================================================================================\n\nOperation failed. You entered a number that is not in the menu. Please try again!\n\n===================================================================================\n\n");
		break;
  	}
	}
	return 0;	
}
