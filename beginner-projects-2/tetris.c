#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void showPlayground(int column, int upField[][column], int size, int playground[][column], int row, int mid, int bestScore, int score){
	//print upfield
	int i, j;
	printf("Best Score: %d\nScore: %d\n\n", bestScore, score);	
	for(i=0;i<7;i++){
		if(i<3){
			for(j=0;j<column;j++){
				if(upField[i][j]==0) printf("  ");
				else printf(" *");
			}
		}
		else if(i==3){
			for(j=0;j<column;j++){
				if(j==mid) printf(" ^");
				else printf("  ");	
			}
		}
		else if(i==4){
			for(j=0;j<column;j++){
				if(j==mid) printf("-|");
				else printf("--");
			}
		}
		else{
			for(j=0;j<column;j++){
				printf(" %d", upField[i-2][j]);
			}	
		}
		printf("\n");
	}
	//print playground
	for(i=0;i<row;i++){
		printf("|");
		for(j=0;j<column;j++){
			if(j==0){
				if(playground[i][j]==0) printf(" ");
				else printf("*");
			}
			else{
				if(playground[i][j]==0) printf("  ");
				else printf(" *");
			}
		}
		printf("|\n");
	}
	for(j=0;j<column;j++){
		printf("--");
	}
	printf("-");
}


int main(){
	
	int start, menu;
	int row, column;
	int left, right, up, down, mid;
	int flag, control;
	int i, j, k, l, n;
	int tetriminoes [9][3][3] = 
	{{{0,0,0},{1,1,1},{0,0,0}},
	 {{1,1,0},{1,1,0},{0,0,0}},
	 {{0,1,0},{0,1,0},{0,0,0}},
	 {{0,0,0},{0,1,0},{0,0,0}},
	 {{0,1,0},{0,1,0},{0,1,1}},
	 {{0,1,1},{1,1,0},{0,0,0}},
	 {{0,1,1},{0,1,0},{0,1,0}},
	 {{1,1,0},{0,1,1},{0,0,0}},
	 {{1,1,1},{0,1,0},{0,0,0}}};
	int randomTetrimino, randomRotate, doRotate, doMove;
	int tetrimino[3][3], temp[3][3];
	int bestScore = 0;
	int score;
	srand(time(NULL));
	
	do{
	
	//menu-----------------------------------------------------------------------------------------------------------------
		do{
			printf("  _______ ______ _______ _____  _____  _____ \n");
		    printf(" |__   __|  ____|__   __|  __ \\|_   _|/ ____|\n");
		    printf("    | |  | |__     | |  | |__) | | | | (___  \n");
		    printf("    | |  |  __|    | |  |  _  /  | |  \\___ \\ \n");
		    printf("    | |  | |____   | |  | | \\ \\ _| |_ ____) |\n");
		    printf("    |_|  |______|  |_|  |_|  \\_\\_____|_____/ \n\n\n\n");
			printf("-*- Press '0' to start a new game! -*-\n\n");
			printf("MENU\n--------\n1.What is Tetris?\n2.How to Play?\n3.Game Rules\n4.Quit\n\n([?]INFO: Press 1, 2, 3 or 4 to use the menu.)\n\n\n\nYour choice: ");
	
			scanf("%d", &start);
	
			if(start == 0){
				menu = 0;
				system("CLS");
				printf("Enter the size of the game board!\n\n\n");				
			}
	
			else if(start == 1){
				system("CLS");
				printf("\n\n\n====================\n\nTetris is an addictive puzzle game that appeals to our desire to create order out of chaos.\n");
				printf("Tetris was created by Alexey Pajitnov in 1984 as a product of Pajitnov's computer programming experience and interest in puzzles.\n");	
				printf("Tetris became one of the most successful and recognizable video games in the decades that followed and almost all gaming platforms.\n\n");
				printf("====================\n\n");
				printf("-Press '1' to go back to the menu-\n\n\n\n\n\n");
				scanf("%d", &menu);
				menu = 1;
				system("CLS");
			}
	
			else if(start == 2){
				system("CLS");
				printf("\n\n\n============================================\nHow to play Tetris!\n\n\n");
				printf("The aim of Tetris is to score as many points as possible by creating and clearing uninterrupted horizontal lines on the playing field with falling blocks.\n");
				printf("The player rotates, moves and drops the falling Tetriminoes around the playing field.\n");
				printf("Lines are cleared when they are filled with blocks with no empty space left.\n");
				printf("If blocks fall on the top line of the playing field, the game is over.\n\n");
				printf("============================================\n\n");
				printf("-Press '1' to go back to the menu-\n\n\n\n\n\n");
				scanf("%d", &menu);
				menu = 1;
				system("CLS");
			}
	
			else if(start == 3){
				system("CLS");
				printf("\nGame Rules\n==============================\n\n");
				printf("1) If you press '0' at any moment of the game, you can return to the menu.\nExample:\n('0' to menu)\nRotate? 1. Left / 2.Right / 3.Upside down / 4.Don't : \n\n");
				printf("2) When selecting the coordinate where you want to move the tetrimino, take it according to the '^' arrow.\n");
				printf("Example:\n\n        * *        \n        *           \n        *           \n        ^          \n        |          \n                  1\n1 2 3 4 5 6 7 8 9 0\n");
				printf("\n[?] If you enter a value of 8 in the movement coordinate, the '^' will go above the number 8.\n\n");
				printf("              * *   \n              *     \n              *      \n              ^    \n              |    \n                  1\n1 2 3 4 5 6 7 8 9 0\n\n\n");
				printf("3) If you want to change the movement, you can answer 'No' to the question 'Do you confirm the movement?' to return to the rotation and movement.\n\n");
				printf("4) Each time you place a block you get 1 point. If you can complete a line, you get points equal to the length of the line.\n\n");
				printf("5) If the tetriminos rise above the playground, the game is over.\n\n");
				printf("Press '1' to go back to the menu: ");
				scanf("%d", &menu);
				menu = 1;
				system("CLS");
			}

			else if(start == 4){
				printf("\n\n\nAre you sure?\n1.Yes / 2.No: ");
				scanf("%d", &menu);
				
				if(menu == 1) return 0;
				else {
					system("CLS");
					menu = 1;
				}
			}
			
			else{
				printf("\nInvalid input. Please try again!\n");
				printf("Press '1' to go back to the menu: ");
				scanf("%d", &menu);
				menu = 1;
				system("CLS");	
			}
		}
		while(menu == 1);
	//menu-----------------------------------------------------------------------------------------------------------------
	
	
	//get rows and columns
		do{
			printf("\nNumber of rows: ");
			scanf("%d", &row);
			printf("Number of columns: ");
			scanf("%d", &column);
			if(row<3 || column<3) printf("It's too small! Try again.\n");
			else if(row>50 || column>50) printf("It's too big! Try again.\n");
		}
		while(row<3 || row>50 || column<3 || column>50);
	
	//create score	
		score = 0;
	//create the playground
		int playground[row][column];
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				playground[i][j] = 0;
			}
		}
	
	//create the upfield
		int upField[5][column];
		for(i=0;i<5;i++){
			for(j=0;j<column;j++){
				upField[i][j] = 0;
			}
		}
	//put numbers to the upfield
		for(i=column-1; i>=0; i--){
			if (i+1 >= 10){
				upField[3][i] = (i+1) / 10;
				upField[4][i] = (i+1) % 10;
			}
			else{
				upField[4][i] = i+1;
			}
		}
	
	
		do{	
	//create random tetrimino
			randomTetrimino = (rand()%9) ;
			randomRotate = (rand()%4)+1;
			
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					temp[i][j] = tetriminoes[randomTetrimino][i][j];
				}
			}
			
	
	//random rotate
			if(randomRotate == 1){
				for(i=0;i<3;i++){
					k=2-i;
					for(j=0;j<3;j++){
						tetrimino[i][j] = temp[j][k];
					}
				}
			}
			else if(randomRotate == 2){
				for(i=0;i<3;i++){
					k=2-i;
					for(j=0;j<3;j++){
						l=2-j;
						tetrimino[i][j] = temp[k][l];
					}
				}
			}
			else if(randomRotate == 3){
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						l=2-j;
						tetrimino[i][j] = temp[l][i];
					}
				}
			}
			else{
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						tetrimino[i][j] = temp[i][j];
					}
				}
			}
	
	//find mid
			if(column % 2 == 1) mid = (column/2);
			else mid = (column/2)-1;
			
	//put tetrimino to upfield
			for(i=0; i<3; i++){
				n = mid-1;
				for(j=0; j<3; j++){
					upField[i][n] = tetrimino[i][j];
					n = n+1;
				}
			}
	
	
			do{
	//rotate--------------------------------------------------------------------------------
				do{
					system("CLS");
					showPlayground(column, upField, 5, playground, row, mid, bestScore, score);
	
					printf("\n[+]-> Press '0' to finish this game and go back to the menu\n\nRotate?\n-----------\n1. Left / 2. Right / 3. Upside down / 4. Don't : ");
					scanf("%d", &doRotate);
					control = doRotate;
					if(control == 0){
						printf("\n\nAre you sure you want to go back to the menu?  1. Yes / 2. No : ");
						scanf("%d", &control);
						if(control == 1) control = 0;
						else {
							control = 1;
							doRotate = 0;
						}
					}
					if(doRotate <= 3 && control != 0){
						if(doRotate == 1){
							for(i=0;i<3;i++){
								k = 2-i;
								n = mid-1;
								for(j=0;j<3;j++){
									temp[i][j] = tetrimino[j][k];
									upField[i][n] = temp[i][j];
									n=n+1;
								}
							}
						}
						else if(doRotate == 2){
							for(i=0;i<3;i++){
								n = mid-1;
								for(j=0;j<3;j++){
									l = 2-j;
									temp[i][j] = tetrimino[l][i];
									upField[i][n] = temp[i][j];
									n=n+1;
								}
							}
						}
						else if(doRotate == 3){
							for(i=0;i<3;i++){
								k=2-i;
								n = mid-1;
								for(j=0;j<3;j++){
									l = 2-j;
									temp[i][j] = tetrimino[k][l];
									upField[i][n] = temp[i][j];
									n=n+1;
								}
							}
						}
						for(i=0;i<3;i++){
							for(j=0;j<3;j++){
								tetrimino[i][j] = temp[i][j];
							}
						}		
					}
				}
				while(doRotate <= 3 && control != 0);
	//rotate------------------------------------------------------------------------------


	//find right, left, up and down-----------------------------
		//find right
			if(upField[0][mid+1] == 1 || upField[1][mid+1] == 1 || upField[2][mid+1] == 1) right = 1;
			else right = 0;
		//find left
			if(upField[0][mid-1] == 1 || upField[1][mid-1] == 1 || upField[2][mid-1] == 1) left = 1;
			else left = 0;
		//find down
			if(upField[2][mid-1] == 1 || upField[2][mid] == 1 || upField[2][mid+1] == 1) down = 1;
			else down = 0;
		//find up
			if(upField[0][mid-1] == 1 || upField[0][mid] == 1 || upField[0][mid+1] == 1) up = 1;
			else up = 0;
	//find right, left, up and down-----------------------------
	

	//moving--------------------------------------------------------------------------------
				if(control != 0){
					system("CLS");
					showPlayground(column, upField, 5, playground, row, mid, bestScore, score);
					do{
						printf("\n[+] Press '0' to not move the tetrimino\nEnter the movement coordinate: ");
						scanf("%d", &doMove);
						system("CLS");
						if(doMove != 0){
							doMove = doMove-1;
							if(doMove-left >= 0 && doMove+right < column && doMove != mid){
								for(i=0;i<3;i++){
									for(n=mid-left;n<=mid+right;n++){
										upField[i][n] = 0;
									}
									l=1-left;
									for(j=doMove-left;j<=doMove+right;j++){
										upField[i][j] = tetrimino[i][l];
										l=l+1;                                                                         
									}
								}
								mid = doMove;
							}
							else{
								if(doMove != mid) printf("[!]-> Tetriminos cannot leave the playground!\n");
							}
							showPlayground(column, upField, 5, playground, row, mid, bestScore, score);
							doMove = 1;
						}
					}
					while(doMove > 0);
				}		
	//moving------------------------------------------------
	
	//confirm
				if(control != 0){
					do{
						showPlayground(column, upField, 5, playground, row, mid, bestScore, score);
						printf("\n\n[+]-> Press '0' to finish this game and go back to the menu\n\nDo you confirm the movement?\n1. Yes / 2. No : ");
						scanf("%d", &flag);
						if(flag == 0) {
							printf("\n\nAre you sure you want to go back to the menu?  1. Yes / 2. No : ");
							scanf("%d", &control);	
							if(control == 1) control = 0;						
							system("CLS");
						}
						else system("CLS");			
					}
					while(control != 0 && flag == 0);
				}
				else system("CLS");
				
			}
			while(flag != 1 && control != 0);
	
	
	//controlling the fall of tetrimino
			if(control != 0){
				k=down+1;
				j=mid-left;
				i=0;
				while(j<=mid+right && flag != 0){
					if(upField[k][j] == 1 && playground[i][j] == 1){
						flag = 0;
						i = i-1;
					}
					else j = j+1;
				}
				i=i+1;
				if(flag != 0){
					j=mid-left;
					while(j<=mid+right && flag != 0){
						if(upField[k][j] == 1 && playground[i][j] == 1 || upField[k-down][j] == 1 && playground[i-down][j] == 1){
							flag = 0;
							i = i-1;
						}
						else j = j+1;
					}
					i = i+1;
					if(flag != 0){
						while(i<row && flag!=0){
							j=mid-left;
							while(j<=mid+right && flag!=0){
								if(upField[k][j] == 1 && playground[i][j] == 1 || upField[k-down][j] == 1 && playground[i-down][j] == 1 || upField[k-down-up][j] == 1 && playground[i-down-up][j] == 1){
								flag = 0;
								i = i-1;
								}
								else j = j+1;		
							}
							i = i+1;
			 			}
					}
				}
				i = i-1;
			 				 	
				
				if(i-up-down<0){
					system("CLS");
					printf("   _____          __  __ ______    ______      ________ _____  _ \n");
    				printf("  / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\| |\n");
    				printf(" | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) | |\n");
    				printf(" | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  /| |\n");
    				printf(" | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\|_|\n");
			    	printf("  \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_(_)\n");
			    	printf("\nPress '0' to go back to the menu: ");
			    	scanf("%d", &control);
			    	control = 0;
			    	system("CLS");
				}
			}
	
	//put tetrimino to playground 
			if(control != 0){
				for(k=1+down;k>=1-up;k--){
					for(j=mid-left;j<=mid+right;j++){
						if(upField[k][j] == 1){
							playground[i][j] = 1;
							upField[k][j] = 0;
						}	
					}
					i=i-1;
				}
				
				score = score+1;
				
	//remove full lines and fall down
				l=0;
				for(i=row-1;i>=l;i--){
					j=0;
					flag = 1;
					while(j<column && flag!=0){
						if(playground[i][j] == 0) flag=0;			
						else j=j+1;
					}
					if(flag!=0){
						score = score+column;
						for(k=i;k>l;k--){
							for(j=0;j<column;j++){
								playground[k][j] = playground[k-1][j];
							}
						}
						for(j=0;j<column;j++){
							playground[0][j] = 0;
						}	
						l = l+1;
						i = i+1;	
					}
				}	
					
				if(bestScore < score){
					bestScore = score;
				}	
			}
		}
		while(control!=0);
	}
	while(1);
}
