#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

int player1Position = 0;
int player2Position = 0;
int currentPlayer = 1; 
int startUpMode(int* choice);
int rollDie();
void movePlayer(int roll, char* name1, char* name2);
void createBoard();
int checkLaddersAndSnakes(int position);

int main(){
    printf("Welcome to Snake and Ladders!\n");
    printf("Created by: thetrebleguy\n");
    printf("------------------------------------------------------\n\n");

    int choice = 0;
    int *pChoice = &choice;
    startUpMode(pChoice); // let user selects 

    char name1[50] = "";
    char name2[50] = ""; 

    // player selecting names
    if (choice == 1){
        printf("Player 1, what is your name going to be? ");
        scanf("%s", &name1);
        printf("Player 2, what is your name going to be? ");
        scanf("%s", &name2);
    } else{
        printf("What is your name going to be? ");
        scanf("%s", &name1);
        strcpy(name2, "Computer");
    }

    printf("\n#P1 is %s\n", name1);
    printf("#P2 is %s\n\n", name2);
    createBoard(); // creates the board

    do{
        int roll = rollDie();
        currentPlayer == 1 ? printf("%s rolls a...\n", name1) : printf("%s rolls a...\n", name2);
        Sleep(2000);

        printf("%d\n", roll);
        Sleep(2000);
        
        movePlayer(roll, name1, name2);
        createBoard();
        Sleep(5000);
    } while (player1Position != 100 && player2Position != 100);

    if (player1Position == 100){
        printf("\nCongratulations %s!\nYou won the snake and ladders game!", name1);
    } else{
        printf("\nCongratulations %s!\nYou won the snake and ladders game!", name2);
    }
    return 0; 
};

int startUpMode(int* choice){
    do{
        printf("Select a mode:\n");
        printf("1: 2 PLAYERS\n");
        printf("2: COMPUTER\n");
        printf("1 or 2: ");
        scanf("%d", &(*choice));

        switch (*choice){
        case 1:
            printf("\nYou picked 2 PLAYERS mode!\n\n");
            break;
        case 2:
            printf("\nYou picked COMPUTER mode!\n\n");
            break;
        default:
            printf("\nPlease select 1 or 2\n\n");
            break;
        }
    } while (*choice != 1 && *choice != 2);
    return (*choice);
}

int rollDie(){
    srand(time(NULL));
    return (rand() % 6) + 1;
}

void movePlayer(int roll, char* name1, char* name2){
    // moves the player and checks if it will be over 100,
    if (currentPlayer == 1){
        if (player1Position + roll <= 100){
            player1Position += roll; 

            int player1PositionNew = checkLaddersAndSnakes(player1Position);
            if (player1PositionNew != player1Position && player1PositionNew > player1Position){
                printf("%s takes the ladder and moves up to %d!\n", name1, player1PositionNew);

            } else if(player1PositionNew != player1Position && player1PositionNew < player1Position){
                printf("%s slide down the snake and moves down to %d!\n", name1, player1PositionNew);
            }
            player1Position = player1PositionNew;
        } else{
            printf("%s cannot move!\n", name1);
        }
    } else{
        if (player2Position + roll <= 100){
            player2Position += roll;

            int player2PositionNew = checkLaddersAndSnakes(player2Position);
            if (player2PositionNew != player2Position && player2PositionNew > player2Position){
                printf("%s takes the ladder and moves up to %d!\n", name2, player2PositionNew);
            } else if(player2PositionNew != player2Position && player2PositionNew < player2Position){
                printf("%s slide down the snake and moves down to %d!\n", name2, player2PositionNew);
            }
            player2Position = player2PositionNew;
        } else{
            printf("%s cannot move!\n", name2);
        }
    }

    // collision
    if (player1Position == player2Position){
        if (currentPlayer == 1){
            printf("%s landed on %s! Sending %s back to 0.\n", name1, name2, name2);
            player2Position = 0;
        } else {
            printf("%s landed on %s! Sending %s back to 0.\n", name2, name1, name1);
            player1Position = 0;
        }
    }

    // final announcement
    currentPlayer == 1 ? printf("%s is at square %d!\n\n", name1, player1Position) : printf("%s is at square %d!\n\n", name2, player2Position);
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
};

// creating the board
void createBoard(){
    int currentNum = 0;
    const int ladderStarts[] = {1, 4, 9, 21, 28, 49, 73, 80};
    const int ladderCount = sizeof(ladderStarts) / sizeof(ladderStarts[0]); 
    const int snakeStarts[] = {24, 33, 37, 62, 78, 88, 92, 97};
    const int snakeCount = sizeof(snakeStarts) / sizeof(snakeStarts[0]);
    
    int isLadderStart(int position) {
        for (int i = 0; i < ladderCount; i++) {
            if (ladderStarts[i] == position) {
                return 1;
            }
        }
        return 0;
    };

    int isSnakeStart(int position) {
        for (int i = 0; i < snakeCount; i++) {
            if (snakeStarts[i] == position) {
                return 1;
            }
        }
        return 0;
    }  

    for(int row = 9; row >= 0; row--){
        if (row % 2 == 0){ // left to right
            for (int col = 1; col <= 10; col++){
                currentNum = row * 10 + col;
                if (currentNum == player1Position){
                    printf("#P1   ");
                } else if (currentNum == player2Position){
                    printf("#P2   ");
                } else if (isLadderStart(currentNum)){
                    printf("%-2d^   ", currentNum);
                } else if (isSnakeStart(currentNum)){
                    printf("%-2dv   ", currentNum);
                } else{
                    printf("%-3d   ", currentNum);
                }
            }
        } else{
            for (int col = 10; col >= 1; col--){
                currentNum = row * 10 + col;
                if (currentNum == player1Position){
                    printf("#P1   ");
                } else if (currentNum == player2Position){
                    printf("#P2   ");
                } else if (isLadderStart(currentNum)){
                    printf("%-2d^   ", currentNum);
                } else if (isSnakeStart(currentNum)){
                    printf("%-2dv   ", currentNum);
                } else {
                    printf("%-3d   ", currentNum);
                }
            }
        }
        printf("\n\n");
    }
};

// snakes and the ladders
int checkLaddersAndSnakes(int position) {
    switch (position) {
        case 1:  return 23; // ladder
        case 4:  return 15; // ladder
        case 9:  return 30; // ladder
        case 21: return 43; // ladder
        case 24: return 7;  // snake 
        case 28: return 75; // ladder
        case 33: return 10; // snake
        case 37: return 3;  // snake
        case 49: return 70; // ladder 
        case 62: return 18; // snake
        case 73: return 96; // ladder
        case 78: return 57; // snake
        case 80: return 99; // ladder
        case 88: return 25; // snake
        case 92: return 55; // snake
        case 97: return 79; // snake
        default: return position; 
    }
}