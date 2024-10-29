#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<conio.h>
#include <time.h>


typedef struct player{
	char name[20];
	int score;
	int colors_count[5];
}PLAYER;



typedef struct move_data{
	int selected_stone_x;
	int selected_stone_y;
	int move_coord_x;
	int move_coord_y;
	int isFirstMove; 
}MOVE_DATA;


typedef struct game_data{
	PLAYER player;
	MOVE_DATA move_data;
	char** prev_game_board;
}GAME_DATA;



char** createMatrix(int size){
	char** matrix;
	int i,j;
	matrix = (char**)malloc(size*sizeof(char*));
	for(i=0;i<size;i++){
		matrix[i] = (char*)malloc(size*sizeof(char));
	}
	return matrix;
}


char** createGameBoard(int size){
	char** matrix = createMatrix(size);
	int i,j;
	srand(time(NULL));
	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			matrix[i][j] = 'A' + (rand() % 5);
		}
	}
	
	matrix[(size/2)-1][(size/2)-1] = '_';
	matrix[(size/2)-1][(size/2)] = '_';
	matrix[(size/2)][(size/2)-1] = '_';
	matrix[(size/2)][(size/2)] = '_';
	
	return matrix;
}



PLAYER* createPlayer(int which_player){
	PLAYER* player = (PLAYER*)malloc(sizeof(PLAYER));
	int i;
	printf("\nEnter the Player %d's Name: ", which_player);
	scanf("%s", player->name);
	player->score = 0;
	for(i=0;i<5;i++){
		player->colors_count[i] = 0;
	}
	return player;
}



void freeMatrix(char** matrix, int size){
	if(matrix != NULL){
		int i;
		for(i=0;i<size;i++){
			free(matrix[i]);
		}
		free(matrix);
	}
}


void printGame(char** matrix, int size, PLAYER* player1, PLAYER* player2, MOVE_DATA* move_data){
    
	int i,j;
	int player1_name_len = strlen(player1->name);
	if(player1_name_len < 8) printf("%s\t\t\t%s\n----------\t\t----------\nScore: %d\t\tScore: %d\n\n|", player1->name, player2->name, player1->score, player2->score);
	else printf("%s\t\t%s\n----------\t\t----------\nScore: %d\t\tScore: %d\n\n|", player1->name, player2->name, player1->score, player2->score);
	
	for(i=0;i<5;i++){
		printf("%2d ", player1->colors_count[i]);
	}
	printf("|\t|");
	for(i=0;i<5;i++){
		printf("%2d ", player2->colors_count[i]);
	}
	printf("|\n| A  B  C  D  E |\t| A  B  C  D  E |");
	printf("\n\n\n      ");
	
	for(i=0;i<size;i++){
		if(i+1 > 9) printf(" %d", i+1);
		else printf(" %d ", i+1);
	}
	printf("\n     ");
	for(i=0;i<size;i++){
		printf("---");
	}
	printf("-\n");
	
	for(i=0;i<size;i++){
		printf("%2d -> ", i+1);
		for(j=0;j<size;j++){
			if(i==move_data->selected_stone_x && j==move_data->selected_stone_y) printf("[%c]", matrix[i][j]);
			else printf(" %c ", matrix[i][j]);
		}
		printf("\n\n");
	}
}



int isGameOver(char** game_board, int size){
	
	int i=0,j=0,flag=0;	
	while(i<size && flag!=1){
		while(j<size && flag!=1){			
			if(game_board[i][j] == '_') j++;
			else{
				if(j+2 < size && game_board[i][j+2] == '_' && game_board[i][j+1] != '_') flag=1;
				else if(j-2 >= 0 && game_board[i][j-2] == '_' && game_board[i][j-1] != '_') flag=1;
				else if(i-2 >= 0 && game_board[i-2][j] == '_' && game_board[i-1][j] != '_') flag=1;
				else if(i+2 < size && game_board[i+2][j] == '_' && game_board[i+1][j] != '_') flag=1;
				else j++;
			}
		}
		i++;
		j=0;
	}
	
	return flag;
}



int isSelectValid(char** game_board, int size, MOVE_DATA* move_data){
	int i,j;
	i= move_data->selected_stone_x;
	j= move_data->selected_stone_y;
	
	if(game_board[i][j] == '_') return 0;
	else if(j+2 < size && game_board[i][j+2] == '_' && game_board[i][j+1] != '_') return 1;
	else if(j-2 >= 0 && game_board[i][j-2] == '_' && game_board[i][j-1] != '_') return 1;
	else if(i-2 >= 0 && game_board[i-2][j] == '_' && game_board[i-1][j] != '_') return 1;
	else if(i+2 < size && game_board[i+2][j] == '_' && game_board[i+1][j] != '_') return 1;
	else return 0;
}



int isMoveValid(char** game_board, int size, MOVE_DATA* move_data){
	
	int i,j,k,l;
	i= move_data->selected_stone_x;
	j= move_data->selected_stone_y;
	k= move_data->move_coord_x;
	l= move_data->move_coord_y;
	
	if(game_board[k][l] == '_' && k<size && k>=0 && l<size && l>=0){
		if(i+2==k && j==l && game_board[i+1][j]!='_') return 1;
		else if(i-2==k && j==l && game_board[i-1][j]!='_') return 1;
		else if(i==k && j+2==l && game_board[i][j+1]!='_') return 1;
		else if(i==k && j-2==l && game_board[i][j-1]!='_') return 1;
		else return 0;
	}
	else return 0;
}



void saveGame(char** game_board, int size, PLAYER* player1, PLAYER* player2, char* filename) {
    FILE* file = fopen(filename, "w");
	int i,j;
    
	fprintf(file, "%d\n", size);
    for(i=0;i<size;i++){
        for (j=0;j<size;j++) {
            fprintf(file, "%c", game_board[i][j]);
        }
        fprintf(file, "\n");
    }
    
    fprintf(file, "%s %d\n", player1->name, player1->score);
    for (i = 0; i < 5; i++) {
        fprintf(file, "%d ", player1->colors_count[i]);
    }
    fprintf(file, "\n");
    
    fprintf(file, "%s %d\n", player2->name, player2->score);
    for ( i = 0; i < 5; i++) {
        fprintf(file, "%d ", player2->colors_count[i]);
    }
    
    fclose(file);
    printf("\n\n[i]-> That game saved successfully!\n");
}


void loadGame(char*** game_board, int* size, PLAYER* player1, PLAYER* player2) {
    
	int i,j;
    char* buffer;
    char game_name[20];
    FILE* file;
    do{
		printf("Write the name of the game that you want to play: ");
		scanf("%s", &game_name);
		file = fopen(game_name, "r");
		if(file==NULL)printf("[i]-> Wrong file name!\n");	
	}while(file==NULL);
    
    
    fscanf(file, "%d", size);
    *game_board = createMatrix(*size);
    buffer = (char*)malloc((*size)*sizeof(char));
    for(i=0;i<*size;i++) {
        fscanf(file, "%s", buffer);
        for (j=0;j<*size;j++){
            (*game_board)[i][j] = buffer[j];
		}
	}

    free(buffer);
    
    fscanf(file, "%s %d", player1->name, &player1->score);
    for(i=0;i<5;i++){
        fscanf(file, "%d", &player1->colors_count[i]);
    }
    
	fscanf(file, "%s %d", player2->name, &player2->score);
    for(i=0;i<5;i++) {
        fscanf(file, "%d", &player2->colors_count[i]);
    }
    
    fclose(file);
}



void selectStone(char** game_board, int size, MOVE_DATA* move_data){
	int flag=1;
	do{
		if(flag!=1) printf("\n\n[i]-> There is no valid move for the stone that you selected!\n Select a different stone.\n");
		printf("\n\nEnter the coordinates which stone you want to move!\nX Coordinate: ");
		scanf("%d", &move_data->selected_stone_x);
		printf("Y Coordinate: ");
		scanf("%d", &move_data->selected_stone_y);
		move_data->selected_stone_x--;
		move_data->selected_stone_y--;
		if(move_data->selected_stone_x < 0 || move_data->selected_stone_x >= size) flag=0;
		else if(move_data->selected_stone_y < 0 || move_data->selected_stone_y >= size) flag=0;
		else flag = isSelectValid(game_board, size, move_data);
	}
	while(flag!=1);
}



int findScore(PLAYER* player){
	int i;
	int min = player->colors_count[0];
	for(i=1;i<5;i++){
		if(player->colors_count[i] < min){
			min = player->colors_count[i];
		}
	}
	return min;
}




void savePrevGame(GAME_DATA* prev_game, PLAYER* player, MOVE_DATA* move_data, char** game_board, int size){
	int i,j;
	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			prev_game->prev_game_board[i][j] = game_board[i][j];
		}
	}
	
	for(i=0;i<5;i++){
		prev_game->player.colors_count[i] = player->colors_count[i];		
	}
	prev_game->player.score = player->score;
	prev_game->move_data.selected_stone_x = move_data->selected_stone_x;
	prev_game->move_data.selected_stone_y = move_data->selected_stone_y;
}


void makeUndo(GAME_DATA* prev_game, PLAYER* player, MOVE_DATA* move_data, char** game_board, int size){
	
	int i,j;
	GAME_DATA tmp;
	tmp.prev_game_board = createMatrix(size);
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			tmp.prev_game_board[i][j] = prev_game->prev_game_board[i][j];
		}
	}
	tmp.move_data.selected_stone_x = prev_game->move_data.selected_stone_x;
	tmp.move_data.selected_stone_y = prev_game->move_data.selected_stone_y;
	tmp.player.score = prev_game->player.score;
	for(i=0;i<5;i++){
		tmp.player.colors_count[i] = prev_game->player.colors_count[i];
	}
	
	savePrevGame(prev_game, player, move_data, game_board, size);
	
	player->score = tmp.player.score;
	for(i=0;i<5;i++){
		player->colors_count[i] = tmp.player.colors_count[i];
	}
	move_data->selected_stone_x = tmp.move_data.selected_stone_x;
	move_data->selected_stone_y = tmp.move_data.selected_stone_y;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			game_board[i][j] = tmp.prev_game_board[i][j];
		}
	}
}


void askUndo(int* undo, GAME_DATA* prev_game, PLAYER* cur_player, PLAYER* player1, PLAYER*  player2, MOVE_DATA* move_data, char** game_board, int size, int* flag){
	int tmp = *flag;
	printf("\n\n[?]-> Would you like to undo your move?\nYes: 0 | No: 1\nYour choice: ");
	scanf("%d", undo);
	if(*undo == 0){
		*flag=1;
		makeUndo(prev_game, cur_player, move_data, game_board, size);
		system("CLS");
		printf("Player %s's turn\n----------------------\n\n\n", cur_player->name);
		printGame(game_board, size, player1, player2, move_data);
		printf("\n\n[?]-> Would you like to redo your move?\nYes: 0 | No: 1\nYour choice: ");
		scanf("%d", undo);
		if(*undo == 0) {
			*flag = tmp;
			makeUndo(prev_game, cur_player, move_data, game_board, size);
			system("CLS");
			printf("Player %s's turn\n----------------------\n\n\n", cur_player->name);
			printGame(game_board, size, player1, player2, move_data);
		}
		*undo=0;
	}
}

void makeMove(char** game_board, int size, PLAYER* player, MOVE_DATA* move_data){
	
	int flag=1;
	int sx, sy, mx, my;
	char tmp;
	
	do{
		if(flag!=1) printf("\n\n[i]-> The stone is not avaible to go coordinates that you entered!\n Enter coordinates again.\n");
		printf("\n\nEnter the coordinates that you want to move!\nX Coordinate: ");
		scanf("%d", &move_data->move_coord_x);
		printf("Y Coordinate: ");
		scanf("%d", &move_data->move_coord_y);
		move_data->move_coord_x--;
		move_data->move_coord_y--;
		if(move_data->move_coord_x < 0 || move_data->move_coord_x >= size) flag=0;
		else if(move_data->move_coord_y < 0 || move_data->move_coord_y >= size) flag=0;
		else flag = isMoveValid(game_board, size, move_data);
	}
	while(flag!=1);
	
	sx = move_data->selected_stone_x;
	sy = move_data->selected_stone_y;
	mx = move_data->move_coord_x;
	my = move_data->move_coord_y;
	
	tmp = game_board[sx][sy];
	game_board[sx][sy] = '_';
	player->colors_count[(game_board[(sx+mx)/2][(sy+my)/2] - 'A')]++;
	player->score = findScore(player);
	game_board[(sx+mx)/2][(sy+my)/2] = '_';
	game_board[mx][my] = tmp;
	
	move_data->isFirstMove = 0;
	
	move_data->selected_stone_x = mx;
	move_data->selected_stone_y = my;
}



void printWinner(PLAYER* player1, PLAYER* player2){
	
	if(player1->score < player2->score) printf("|_-_> Player %s won the game! <_-_|\n\n", player2->name);
	else if(player1->score > player2->score) printf("|_-_> Player %s won the game! <_-_|\n\n", player1->name);
	else{
		int player1_stone_count=0; 
		int player2_stone_count=0;
		int i;
		for(i=0;i<5;i++){
			player1_stone_count += player1->colors_count[i];
			player2_stone_count += player2->colors_count[i];
		}
		if(player1_stone_count < player2_stone_count) printf("|_-_> Player %s won the game! <_-_|\n\n", player2->name);
		else if(player1_stone_count > player2_stone_count) printf("|_-_> Player %s won the game! <_-_|\n\n", player1->name);
		else printf("===== DRAW =====\n\n");
	}
		
}



int computerSelectValid(char** game_board, int size, MOVE_DATA* move_data, char wanted1, char wanted2){
	int i,j;
	i= move_data->selected_stone_x;
	j= move_data->selected_stone_y;
	
	if(game_board[i][j] == '_') return 0;
	else if(j+2 < size && game_board[i][j+2] == '_' && game_board[i][j+1] != '_'){
		move_data->move_coord_x = i;
		move_data->move_coord_y = j+2;
		if(game_board[i][j+1] == wanted1 || game_board[i][j+1] == wanted2) return 1;
		else return -1;
	}
	else if(j-2 >= 0 && game_board[i][j-2] == '_' && game_board[i][j-1] != '_'){
		move_data->move_coord_x = i;
		move_data->move_coord_y = j-2;
		if(game_board[i][j-1] == wanted1 || game_board[i][j-1] == wanted2) return 1;
		else return -1;
	}
	else if(i+2 < size && game_board[i+2][j] == '_' && game_board[i+1][j] != '_'){
		move_data->move_coord_x = i+2;
		move_data->move_coord_y = j;
		if(game_board[i+1][j] == wanted1 || game_board[i+1][j] == wanted2) return 1;
		else return -1;
	}
	else if(i-2 >= 0 && game_board[i-2][j] == '_' && game_board[i-1][j] != '_'){
		move_data->move_coord_x = i-2;
		move_data->move_coord_y = j;
		if(game_board[i-1][j] == wanted1 || game_board[i-1][j] == wanted2) return 1;
		else return -1;
	}
	else return 0;
}


void computerMove(char** game_board, int size, PLAYER* computer, MOVE_DATA* move_data){
	
	int flag=1;
	int sx, sy, mx, my;
	char tmp;
	
	sx = move_data->selected_stone_x;
	sy = move_data->selected_stone_y;
	mx = move_data->move_coord_x;
	my = move_data->move_coord_y;
	
	tmp = game_board[sx][sy];
	game_board[sx][sy] = '_';
	computer->colors_count[(game_board[(sx+mx)/2][(sy+my)/2] - 'A')]++;
	computer->score = findScore(computer);
	game_board[(sx+mx)/2][(sy+my)/2] = '_';
	game_board[mx][my] = tmp;
		
	move_data->selected_stone_x = mx;
	move_data->selected_stone_y = my;
}





void computerMakeMove(char** game_board, int size, PLAYER* player1, PLAYER* computer, MOVE_DATA* movedata){
	
	int i, j, k, l;
	char wantedColor1 = 'A';
	int min = player1->colors_count[0];
	for(i=1;i<5;i++){
		if(player1->colors_count[i] < min){
			wantedColor1 = 'A'+ i;
			min = player1->colors_count[i];	
		}
	}
	char wantedColor2 = 'A';
	min = computer->colors_count[0];
	for(i=1;i<5;i++){
		if(computer->colors_count[i] < min){
			wantedColor2 = 'A'+ i;
			min = computer->colors_count[i];	
		}
	}
	
	int flag=1;
	i=0;
	while(i<size && flag!=0){
		j=0;
		while(j<size && flag!=0){
			movedata->selected_stone_x = i;
			movedata->selected_stone_y = j;
			if(computerSelectValid(game_board, size, movedata, wantedColor1, wantedColor2) == 1){
				while(computerSelectValid(game_board, size, movedata, wantedColor1, wantedColor2) != 0){
					if(computerSelectValid(game_board, size, movedata, wantedColor1, wantedColor2) == 1){
						computerMove(game_board, size, computer, movedata);
						flag=0;
					}
					else if(computerSelectValid(game_board, size, movedata, wantedColor1, wantedColor2) == -1){
						computerMove(game_board, size, computer, movedata);
						flag=0;
					}
				}
			}
			else if(computerSelectValid(game_board, size, movedata, wantedColor1, wantedColor2) == -1){
				k = i;
				l = j;
			}
			j++;
		}
		i++;
	}
	if(flag!=0){
		movedata->selected_stone_x = k;
		movedata->selected_stone_y = l;
		while(computerSelectValid(game_board, size, movedata, wantedColor1, wantedColor2) != 0){
			if(computerSelectValid(game_board, size, movedata, wantedColor1, wantedColor2) == 1) computerMove(game_board, size, computer, movedata);		
			else if(computerSelectValid(game_board, size, movedata, wantedColor1, wantedColor2) == -1) computerMove(game_board, size, computer, movedata);		
		}
	}
	
}



void twoPlayerGame(int neworcont){
	
	int size, flag, control, undo, i, j, savenquit;
	char** game_board;
	PLAYER* player1 = (PLAYER*)malloc(sizeof(PLAYER));
	PLAYER* player2 = (PLAYER*)malloc(sizeof(PLAYER));
	MOVE_DATA* move_data = (MOVE_DATA*)malloc(sizeof(MOVE_DATA));
	GAME_DATA* prev_game = (GAME_DATA*)malloc(sizeof(GAME_DATA));
	char game_name[20];
	
	
	
	if(neworcont == 0){
		system("CLS");
		printf("Enter the size of game board: ");
		scanf("%d", &size);
		while(size%2 != 0){
			system("CLS");
			printf("[i]-> The size must be a even number!\n");
			printf("Enter the size of game board: ");
			scanf("%d", &size);
		}
		game_board = createGameBoard(size);
		player1 = createPlayer(1);
		player2 = createPlayer(2);
	}
	else{
		loadGame(&game_board, &size, player1, player2);
	}
	
	prev_game->prev_game_board = createMatrix(size);
	
	do{
		control = isGameOver(game_board, size);
		flag = 1;
		undo = 1;
		move_data->selected_stone_x = -1;
		move_data->selected_stone_y = -1;
		move_data->isFirstMove = 1;
					
		while(flag != 0 && control != 0){
			system("CLS");
			printf("Player %s's turn\n----------------------\n\n\n", player1->name);
			printGame(game_board, size, player1, player2, move_data);
			if(move_data->isFirstMove == 1){
				selectStone(game_board, size, move_data);
				system("CLS");
				printf("Player %s's turn\n----------------------\n\n\n", player1->name);
				printGame(game_board, size, player1, player2, move_data);
			}
			savePrevGame(prev_game, player1, move_data, game_board, size);
			makeMove(game_board, size, player1, move_data);
			flag = isSelectValid(game_board, size, move_data);
			if(undo!=0){
				system("CLS");
				printf("Player %s's turn\n----------------------\n\n\n", player1->name);
				printGame(game_board, size, player1, player2, move_data);
				askUndo(&undo, prev_game, player1, player1, player2, move_data, game_board, size, &flag);
			}
		}
					
		
		control = isGameOver(game_board, size);
		if(control!=0){
			computerMakeMove(game_board, size, player1, player2, move_data);
		}
		
		
		if(control!=0){
			system("CLS");
			printf("Player %s's turn\n----------------------\n\n\n", player2->name);
			printGame(game_board, size, player1, player2, move_data);
			printf("\n[?]-> Would you like to quit that game?\nYes: 0 | No: 1\nYour choice: ");
			scanf("%d", &savenquit);
			if(savenquit == 0){
				printf("\n[i]-> Save the game and quit: 1 | Save the game without quitting: 2\nYour choice: ");
				scanf("%d", &savenquit);
				printf("Give a name that game to save: ");
				scanf("%s", game_name);
				saveGame(game_board, size, player1, player2, game_name);
				if(savenquit == 1) control = -1;	
			}
		}	
		
		
				
	}while(control > 0);
	
	if(control == 0){
		system("CLS");
		printf("  ________   __  _______  ____ _   _________  __\n");
    	printf(" / ___/ _ | /  |/  / __/ / __ \\ | / / __/ _ \\/ /\n");
	    printf("/ (_ / __ |/ /|_/ / _/  / /_/ / |/ / _// , _/_/ \n");
    	printf("\\___/_/ |_/_/  /_/___/  \\____/|___/___/_/|_(_)\n");
	    printf("                                               \n");
		printWinner(player1, player2);
		printGame(game_board, size, player1, player2, move_data);
	}
	
	
	freeMatrix(game_board, size);
	freeMatrix(prev_game->prev_game_board, size);
	free(player1);
	free(player2);
	free(move_data);
	free(prev_game);
}


void computerGame(int neworcont){
	int size, flag, control, undo, i, j, savenquit;
	char** game_board;
	PLAYER* player1 = (PLAYER*)malloc(sizeof(PLAYER));
	PLAYER* player2 = (PLAYER*)malloc(sizeof(PLAYER));
	MOVE_DATA* move_data = (MOVE_DATA*)malloc(sizeof(MOVE_DATA));
	GAME_DATA* prev_game = (GAME_DATA*)malloc(sizeof(GAME_DATA));
	char game_name[20];
	
	
	
	if(neworcont == 0){
		system("CLS");
		printf("Enter the size of game board: ");
		scanf("%d", &size);
		while(size%2 != 0){
			system("CLS");
			printf("[i]-> The size must be a even number!\n");
			printf("Enter the size of game board: ");
			scanf("%d", &size);
		}
		game_board = createGameBoard(size);
		player1 = createPlayer(1);	
		player2 = createPlayer(2);	
	}
	else{
		loadGame(&game_board, &size, player1, player2);
	}
	
	prev_game->prev_game_board = createMatrix(size);
	
	do{
		control = isGameOver(game_board, size);			
		
		if(control!=0){
			computerMakeMove(game_board, size, player1, player2, move_data);
			system("CLS");
			printf("Player %s's turn\n----------------------\n\n\n", player1->name);
			printGame(game_board, size, player1, player2, move_data);
		}		
					
		control = isGameOver(game_board, size);
			
		if(control!=0){
			computerMakeMove(game_board, size, player2, player1, move_data);
			system("CLS");
			printf("Player %s's turn\n----------------------\n\n\n", player2->name);
			printGame(game_board, size, player1, player2, move_data);
		}	
		
	}while(control > 0);
	
	if(control == 0){
		system("CLS");
		printf("  ________   __  _______  ____ _   _________  __\n");
    	printf(" / ___/ _ | /  |/  / __/ / __ \\ | / / __/ _ \\/ /\n");
	    printf("/ (_ / __ |/ /|_/ / _/  / /_/ / |/ / _// , _/_/ \n");
    	printf("\\___/_/ |_/_/  /_/___/  \\____/|___/___/_/|_(_)\n");
	    printf("                                               \n");
		printWinner(player1, player2);
		printGame(game_board, size, player1, player2, move_data);
	}
	
	
	freeMatrix(game_board, size);
	freeMatrix(prev_game->prev_game_board, size);
	free(player1);
	free(player2);
	free(move_data);
	free(prev_game);
}



int main(){
	
	
	
	int menu, gametype;
	
	do{
		
		printf(" ________  ___  __    ___  ________  ________  ___  _________    ___    ___ \n");
    	printf("|\\   ____\\|\\  \\|\\  \\ |\\  \\|\\   __  \\|\\   __  \\|\\  \\|\\___   ___\\ |\\  \\  /  /|\n");
	    printf("\\ \\  \\___|\\ \\  \\/  /|\\ \\  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|___ \\  \\_| \\ \\  \\/  / /\n");
    	printf(" \\ \\_____  \\ \\   ___  \\ \\  \\ \\   ____\\ \\   ____\\ \\  \\   \\ \\  \\   \\ \\    / / \n");
	    printf("  \\|____|\\  \\ \\  \\\\ \\  \\ \\  \\ \\  \\___|\\ \\  \\___|\\ \\  \\   \\ \\  \\   \\/   / /  \n");
    	printf("    ____\\_\\  \\ \\__\\\\ \\__\\ \\__\\ \\__\\    \\ \\__\\    \\ \\__\\   \\ \\__\\__/   / /    \n");
	    printf("   |\\_________\\|__| \\|__|\\|__|\\|__|     \\|__|     \\|__|    \\|__|\\____/ /     \n");
    	printf("   \\|_________|                                                \\|____|/      \n\n\n\n\n");

		printf("-___Menu___-\n\nQuit: 0\nNew Game: 1\nContinue Game: 2\n\n\nYour Choice: ");
		scanf("%d", &menu);
		
		switch(menu){
			case 0:
				printf("\n\n\n\nQuitting...");
				return 0;
				break;
			case 1:
				printf("1 vs 1: 1 | 1 vs Computer: 2\nYour choice: ");
				scanf("%d", &gametype);
				if(gametype == 1) twoPlayerGame(0);
				else computerGame(0);
				printf("\n\n[i]-> Press any number to back to the menu: ");
				scanf("%d", &menu);
				system("CLS");
				break;
			case 2:
				printf("1 vs 1: 1 | 1 vs Computer: 2\nYour choice: ");
				scanf("%d", &gametype);
				if(gametype == 1) twoPlayerGame(1);
				else computerGame(1);
				printf("\n\n[i]-> Press any number to back to the menu: ");
				scanf("%d", &menu);
				system("CLS");
				break;
			default:
				system("CLS");
				printf("[i]-> Invalid choice!\nPlease try again.\n\n\n\n");
				break;
		}
	}
	while(1);
}
	
	
