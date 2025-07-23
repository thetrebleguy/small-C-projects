#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include <math.h>

int userMode(int* choice);
char userNameSelect(char* name1, char* name2, int* choice);
void printInstructions();
void printBoard(char* name1, char* name2, int* roll, int* choice);
int findBestMove(int* i, int* j);
bool isBoardFull();
int checkWinner();
int minimax(bool isMaximizing, int depth);
void findWinner();
bool winnerFound = 0;
int steps = 0;

int board[3][3] = {{0, 0, 0}, 
                   {0, 0, 0}, 
                   {0, 0, 0}};
                   
char actualBoard[3][3] = {{'_', '_', '_'}, 
                          {'_', '_', '_'},
                          {'_', '_', '_'}
};

int main(){
    printf("Welcome to Tic-Tac-Toe Game!\n");
    printf("by: thetrebleguy\n");
    printf("-----------------------------------------\n\n");

    int choice = 0;
    int *pChoice = &choice;
    userMode(pChoice);

    char name1[50] = "";
    char name2[50] = "";
    char *pName1 = name1;
    char *pName2 = name2;
    int roll = 1; // first player goes first
    int *pRoll = &roll;

    userNameSelect(name1, name2, pChoice);
    printf("\nPlayer 1 Name: %s\n", name1);
    printf("Player 2 Name: %s\n\n", name2);
    printInstructions();
    do{
        printBoard(name1, name2, pRoll, pChoice);
    } while (steps < 9 && winnerFound == false);

    if (steps == 9 && winnerFound == false){
        printf("\nIt's a tie!");
        return 0;
    } 

    if (choice == 1){
        if (winnerFound){
            printf("\nCongrats to %s! You won the game!", roll == 1 ? name1 : name2);
        }
    } else{
        if (winnerFound && roll == 1){
            printf("\nCongratulations! You won against the computer, %s!", name1);
        } else if (winnerFound && roll == 2){
            printf("\nYou lost to the computer, better luck next time, %s!", name1);
        }
    }

    return 0;
}

int userMode(int* choice){
    do{       
        printf("Please select a mode:\n");
        printf("1. 2 PLAYERS\n");
        printf("2. COMPUTER\n");
        scanf("%d", &(*choice));

        switch (*choice){
            case 1:
                printf("\nYou selected 2 PLAYERS mode!\n\n");
                break;
            case 2:
                printf("\nYou selected COMPUTER mode!\n\n");
                break;
            default:
                printf("\nPlease select 1 or 2.\n\n");
                break;
        }
    } while (*choice != 1 && *choice != 2);
    return (*choice);
};

// let user selects the names
char userNameSelect(char* name1, char* name2, int* choice){
    if ((*choice) == 1){
        printf("What is your name going to be player 1? ");
        scanf("%s", &(*name1));
        printf("What is your name going to be player 2? ");
        scanf("%s", &(*name2));
    } else{
        printf("What is your name going to be? ");
        scanf("%s", &(*name1));
        strcpy(name2, "Computer");
    };
}

// prints the instructions
void printInstructions(){
    printf("To select a square, please select a number labelled\n");
    printf("from 1 - 9 as below\n\n");

    printf("  1  |  2  |  3  \n");
    printf("------------------\n");
    printf("  4  |  5  |  6  \n");
    printf("------------------\n");
    printf("  7  |  8  |  9  \n");
    Sleep(5000);
};

// prints the board, changes the order of play
void printBoard(char* name1, char* name2, int* roll, int* choice){
    int input = 0;
    int i, j = 0;
    int *pI = &i;
    int *pJ = &j;
    
    if ((*choice) == 1 || ((*choice) == 2 && (*roll) == 1)) {
        do{
            printf("\nWhich square do you want to pick, %s? ", ((*roll) == 1 ? (&(*name1)) : (&(*name2))));
            scanf("%d", &input);
            i = (input - 1) / 3; // row
            j = (input - 1) % 3; // column

            // checks if the input is between 1 - 9
            if (input < 1 || input > 9){
                printf("%s, please pick an integer between 1 - 9\n", ((*roll) == 1 ? (&(*name1)) : (&(*name2))));
                continue;
            };

            // checks if square is still available
            if (board[i][j] == 0){
                printf("%s picked square %d!\n\n", ((*roll) == 1 ? (&(*name1)) : (&(*name2))), input);
            } else{
                printf("Square %d is occupied! Please pick another square\n", input);
            }
        } while(board[i][j] != 0 || input < 1 || input > 9);
    } else{
        findBestMove(pI, pJ);
        printf("\nComputer picked square %d!\n\n", ((i*3) + (j+1)));
    };

    board[i][j] = (*roll);
    actualBoard[i][j] = (*roll) == 1 ? 'X' : 'O';
    steps++;

    for (int i = 0; i<=2; i++){
        for (int j = 0; j <= 2; j++){
            if (j < 2){printf("  %c  |", actualBoard[i][j]);} else{
                printf("  %c", actualBoard[i][j]);
            }
        };
        if (i < 2){printf("\n------------------\n");};
        if (i == 2){printf("\n");};
    };
    
    // check if winner is found
    findWinner();
    if (!winnerFound){
        (*roll) = (*roll) == 1 ? 2 : 1; 
    };
};

// checks for the best move by computer
int findBestMove(int* bestI, int* bestJ){
    int bestScore = -1000;
    for (int i = 0; i <= 2; i++){
        for (int j = 0; j <= 2; j++){
            if (board[i][j] == 0){
                board[i][j] = 2; // change the square into computer's move
                int score = minimax(false, 0);
                board[i][j] = 0;
                if (score > bestScore){
                    bestScore = score;
                    *bestI = i;
                    *bestJ = j; 
                }
            }
        }
    }
};

bool isBoardFull(){
    for (int i = 0; i <= 2; i++){
        for (int j = 0; j <= 2; j++){
            if(board[i][j] == 0){ // that means the board is still not full
                return false;
            }
        }
    }
    return true;
}

// check who wins
int checkWinner(){
    for (int i = 0; i <= 2; i++){
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]){
            if(board[i][0] == 1 || board [i][0] == 2){
                return board[i][0];
            };
        }
    }

    // checks for vertical straights,
    for (int j = 0; j <= 2; j++){
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]){
            if(board[0][j] == 1 || board [0][j] == 2){
                return board[0][j];
            };
        }
    }

    // checks for diagonal straights,
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[2][0] == board[1][1] && board[1][1] == board[0][2])){
        if(board[1][1] == 1 || board [1][1] == 2){
            return board[1][1];
        };
    }

    return 0;
}

int minimax(bool isMaximizing, int depth){
    // checks if the board is full
    if (isBoardFull()) return 0;
    int winner = checkWinner();
    if (winner == 2) return 10 - depth; // maximize because computer wins
    if (winner == 1) return -10 + depth; // minimize because player wins

    if (isMaximizing){
        int bestScore = -1000;
        for (int i = 0; i <= 2; i++){
            for (int j = 0; j <= 2; j++){
                if (board[i][j] == 0){
                    board[i][j] = 2;
                    int score = minimax(false, depth + 1);
                    board[i][j] = 0;
                    bestScore = fmax(score, bestScore);
                }
            }
        };
        return bestScore;
    } else{
        int bestScore = 1000;
        for (int i = 0; i <= 2; i++){
            for (int j = 0; j <= 2; j++){
                if (board[i][j] == 0){
                    board[i][j] = 1;
                    int score = minimax(true, depth + 1);
                    board[i][j] = 0;
                    bestScore = fmin(score, bestScore);
                }
            }
        };
        return bestScore;
    }
};

// checks if there is a winner
void findWinner(){
    // checks for horizontal straights,
    for (int i = 0; i <= 2; i++){
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]){
            if(board[i][0] == 1 || board [i][0] == 2){
                winnerFound = true;
                return;
            };
        }
    }

    // checks for vertical straights,
    for (int j = 0; j <= 2; j++){
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]){
            if(board[0][j] == 1 || board [0][j] == 2){
                winnerFound = true;
                return;
            };
        }
    }

    // checks for diagonal straights,
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[2][0] == board[1][1] && board[1][1] == board[0][2])){
        if(board[1][1] == 1 || board [1][1] == 2){
            winnerFound = true;
            return;
        };
    }
}