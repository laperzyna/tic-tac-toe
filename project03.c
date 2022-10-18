#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

char board[3][3];
const char *x = "X";
const char *o = "O";

struct Play {
	int row;
	int col;
};
/*
 * takes in argument char winner
 * and prints whether game is X, O, or draw
*/
void printW(char winner) {
	if (winner == 'X' || winner == 'O') {
		printf("%c wins\n", winner);
	} else {
		printf("draw\n");
	}
}
/*
 * resets board in order to continue game
*/
void resetBoard() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = '?';
		}
	}
}
/*
 *prints board using 2D array
*/
void printBoard() {
	printf("%c | %c | %c", board[0][0], board[0][1], board[0][2]);
	printf("\n--+---+--\n");
	printf("%c | %c | %c", board[1][0], board[1][1], board[1][2]);
	printf("\n--+---+--\n");
	printf("%c | %c | %c", board[2][0], board[2][1], board[2][2]);
	printf("\n");
}
/*
 * prints board for part1 of project
 * takes in every argument(1-9) and calls printBoard function
 * to print
*/
void printBoard2(char one, char two, char three, char four, char five, char six, char seven, char eight, char nine) {
	board[0][0] = one;
	board[0][1] = two;
	board[0][2] = three;
	board[1][0] = four;
	board[1][1] = five;
	board[1][2] = six;
	board[2][0] = seven;
	board[2][1] = eight;
	board[2][2] = nine;
	printBoard();
}
/*
 * check for free spaces left in game and decrements open variable
 * as game loops
*/
int checkFreeSpace() {
	int open = 9;
	for (int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(board[i][j] != '?') {
				open--;
			}
		}
	}
	return open;
}
/*
 * checks current game for wins
 * checks rows, columns, and diagonals
 * returns ? if there is no win
*/
char check() {
	//check rows
	for(int i = 0; i <3; i++ ){
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
			return board[i][0];
		}
	}
	//check cols
	for(int i = 0; i <3; i++ ){
		if(board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
			return board[0][i];
		}
	}
	//check diagonals
	if(board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
		return board[0][0];
	}
	if(board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
		return board[0][2];
	}
	return '?';
}
/*
 * checks if the board is emtpy in order to use minimax
*/
int isBoardEmpty() {
	int isEmpty = 1;
	for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
			if(board[row][col] == *x || board[row][col] == *o){
				isEmpty = 0;
			}
		}
	}
	if (isEmpty){
		return -10;
	}
}
/*
 * initates the players turn 
 * defensive coding by adding whether the place
 * in the board is already filled
*/
void playerMove() {
	int i;
	int j;
	do {
		printf("X: ");
		scanf("%d %d", &i, &j);
		if(board[i][j] != '?') {
		printf("Invalid move\n");
		} else {
			board[i][j] = *x;
			break;
		}
	} while (board[i][j] != '?');
}
/*
 * evaluates score for X and O by initating 10 or -10
 * initiated variable are switched in order to have O
 * play defensively and offensively
 * also checks for current win in rows, columns, and diagonals
 * in order to use minimax correctly to find next best move
 * as well as if the board is empty
*/
int eval(int winForX) {
	int pointsForO = 10;
	int pointsForX = -10;
	if (winForX) {
		pointsForO = -10;
		pointsForX = 10;
	}
	//check rows
	for (int row = 0; row < 3; row++) {
		if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
			if (board[row][0] == *o) {
				return pointsForO;
			} else if (board[row][0] == *x) {
				return pointsForX;
			}
		}
	}
	//check colums
	for (int col = 0; col < 3; col++) {
		if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
			if (board[0][col] == *o){
				return pointsForO;
			} else if (board[0][col] == *x) { 
				return pointsForX;
			}
		}
	}
	//check diagonals
	if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
		if (board[0][0] == *o) {
			return pointsForO;
		} else if (board[0][0] == *x) {
			return pointsForX;
		}
	}
	if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
		if (board[0][2] == *o) {
			return pointsForO;
		} else if (board[0][2] == *x) {
			return pointsForX;
		}
	}
	//check for empty board
	if (isBoardEmpty()){
		return -10;
	}
	return 0;
}
/*
 * manual function to find max value
*/
int max(int num1, int num2) {
	if (num1 > num2) {
		return num1;
	} else {
		return num2;
	}
}
/*
 * manual function to find min value
*/
int min(int num1, int num2) {
	if (num1 < num2) {
		return num1;
	} else {
		return num2;
	}
}
/*
 * takes in arguments of depth, and isMax
 * calls eval function in order to get score
 * goes through each possible score and returns
 * the best value for both the maximizer and minimizer
*/
int minimax(int depth, bool isMax) {
	int score = eval(isMax);
	if (score == 10) {
		return score;
	}
	if (score == -10) {
		return score;
	}
	if (checkFreeSpace() == 0) {
		return 0;
	}
	//maximizers move
	if (isMax) {
		int best = 1000;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == '?') {
					board[i][j] = *x;
					best = max(best, minimax(depth+1, !isMax));
					board[i][j] = '?';
				}
			}
		}
		return best;		
	//minizers move
	} else {
		int best = -1000;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == '?') {
					board[i][j] = *o;
					best = min(best, minimax(depth+1, !isMax));
					board[i][j] = '?';
				}
			}
		}
		return best;
	}
}
/*
 * goes through and returns the best next move for O
*/
struct Play bestMove(char in) {
	int bestVal = -1000;
	struct Play move;
	move.row = -1;
	move.col = -1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '?') {
				board[i][j] = in;
				int winForX;
				if (in == 'O') {
					winForX = 0;
				} else {
					winForX = 1;
				}
				int moveVal = minimax(0, winForX);
				board[i][j] = '?';
				if (moveVal > bestVal) {
					move.row = i;
					move.col = j;
					bestVal = moveVal;
				}
			}
		}
	}
	if (bestVal == -10 && in != *x) {
		move = bestMove(*x);
	}
	return move;
}
/*
 * initiates computer's move using minimax to play defensively
 * and offensively against player
*/
void computerMove() {
	if (checkFreeSpace() > 0) {
		struct Play move = bestMove(*o);
		board[move.row][move.col] = *o;
	} else {
		printW('?');
	}
}
/*
 * uses defensive coding in case segment core dump
 * uses if statments to know when to just return minimax 
 * value and when to loop through a game of tic-tac-toe
 * game board starts with a '?' filled in every space
 * acting as an empty space
*/
int main(int argc, char *argv[]) {
	if (argc > 10) {
		printf("invalid number of agruments");
	}
	if (argc > 2) {
		char *one = argv[1];
		char *two = argv[2];
		char *three = argv[3];
		char *four = argv[4];
		char *five = argv[5];
		char *six = argv[6];
		char *seven = argv[7];
		char *eight = argv[8];
		char *nine = argv[9];
		printBoard2(*one, *two, *three, *four, *five, *six, *seven, *eight, *nine);
		struct Play move = bestMove(*o);
 		printf("O: %d %d\n", move.row, move.col);		
	}
	if (argc == 1) {
		char winner = '?';
		resetBoard();
		while((winner = '?') && checkFreeSpace() != 0) {
			printBoard();
			playerMove();
			winner = check();
			if (winner != '?' || checkFreeSpace() == 0) {
				break;
			}
			computerMove();
			winner = check();
			if (winner != '?' || checkFreeSpace() == 0) {
				break;
			}
		}
		printBoard();
		printW(winner);
	}
	return 0;
}
