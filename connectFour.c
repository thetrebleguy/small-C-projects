#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define RED   "\x1B[31m"
#define BLUE  "\033[0;34m"
#define YELLOW "\033[0;33m"
#define RESET "\x1B[0m"

void printBoard(int map[][7]){
    for (int i = 0; i < 6; i++){
        printf("+---+---+---+---+---+---+---+\n");
        for (int j = 0; j < 7; j++){
            if (map[i][j] == 1){
                printf("| ");
                printf(RED "X " RESET);
            } else if (map[i][j] == 2){
                printf("| ");
                printf(BLUE "O " RESET);
            } else {
                printf("|   ");
            }
        };
        printf("|\n");
    };
    printf("+---+---+---+---+---+---+---+\n\n");
};

void previewDisc(int map[]){
        printf("+---+---+---+---+---+---+---+\n");
        for (int j = 0; j < 7; j++){
            if (map[j] == 1){
                printf("| ");
                printf(RED "X " RESET);
            } else if (map[j] == 2){
                printf("| ");
                printf(BLUE "O " RESET);
            } else {
                printf("|   ");
            }
        };
        printf("|\n");
    printf("+---+---+---+---+---+---+---+\n\n");
};

int checkWinner(int map[][7]){
    // CHECK if all cells are filled
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++){
            if (map[i][j] == 0){
                continue;
            } else if (i == 5 && j == 6 && map[i][j] != 0){
                return -1;
            }
        };
    };

    
    // HORIZONTALLY
    for (int i = 5; i >= 0; i--){
        for (int j = 0; j < 4; j++){
            if (map[i][j] == 0){
                continue;
            } else {
                // if sound the starting pivot, go to right 3 times
                int pivot = map[i][j];

                int foundWinner = 1;
                for (int check = 1; check <= 3; check++){
                    if (pivot != map[i][j + check]){
                        foundWinner = 0;
                        break;
                    }
                };
                
                if (foundWinner) return pivot;
            }
        };
    };

    // VERTICALLY
    for (int j = 0; j < 7; j++){
        for (int i = 5; i > 2; i--){
            if (map[i][j] == 0){
                continue;
            } else {
                int pivot = map[i][j];

                int foundWinner = 1;
                for (int check = 1; check <= 3; check++){
                    if (pivot != map[i - check][j]){
                        foundWinner = 0;
                        break;
                    }
                };
                
                if (foundWinner) return pivot;
            };
        };
    };

    // DIAGONAL BOTTOM LEFT TO TOP RIGHT
    for (int i = 5; i > 2; i--){
        for (int j = 0; j < 4; j++){
            if (map[i][j] == 0){
                continue;
            } else {
                int pivot = map[i][j];

                int foundWinner = 1;
                for (int check = 1; check <= 3; check++){
                    if (pivot != map[i - check][j + check]){
                        foundWinner = 0;
                        break;
                    }
                };
                
                if (foundWinner) return pivot;
            }
        };
    };

    // DIAGONAL TOP LEFT TO BOTTOM RIGHT
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 4; j++){
            if (map[i][j] == 0){
                continue;
            } else {
                int pivot = map[i][j];

                int foundWinner = 1;
                for (int check = 1; check <= 3; check++){
                    if (pivot != map[i + check][j + check]){
                        foundWinner = 0;
                        break;
                    }
                };
                
                if (foundWinner) return pivot;
            }
        };
    };

    return 0;
};

void mainGame(){
    int turn = 1;
    int running = 1;

    int map[6][7] = {{0}};
    int previewMapColumn = 3;
    int previewMap[7] = {0, 0, 0, 1, 0, 0, 0};

    while (running){
        // print the thingy
        system("cls");
        
        // PLAYER'S TURN
        if (turn == 1) printf(RED "Player 1's Turn\n\n" RESET);
        else printf(BLUE "Player 2's Turn\n\n" RESET);

        // PREVIEW DISC
        previewDisc(previewMap);

        // BOARD
        printBoard(map);

        // INSTRUCTIONS
        printf("Controls: [LEFT / RIGHT] to move | [SPACE] to drop | [ESC] to quit\n");
        printf(RED "X = Player 1          " RESET);
        printf(BLUE "O = Player 2\n" RESET);

        // CONTROLS
        int c = _getch();
        if (c == 224){
            c = _getch();

            if (c == 75){
                // LEFT
                previewMap[previewMapColumn] = 0;
                previewMapColumn = (previewMapColumn > 0 ? previewMapColumn - 1 : 0); 
                previewMap[previewMapColumn] = turn;
            } else if (c == 77){
                // RIGHT
                previewMap[previewMapColumn] = 0;
                previewMapColumn = (previewMapColumn < 6 ? previewMapColumn + 1 : 6);
                previewMap[previewMapColumn] = turn;
            }
        } else if (c == 27){
            // ESC
            running = 0;
            break;
        } else if (c == 32){
            // SPACE 
            int validMove = 0;
            
            for (int i = 5; i >= 0; i--){
                if (map[i][previewMapColumn] == 0){
                    map[i][previewMapColumn] = turn;
                    validMove = 1;
                    break;
                } else {
                    continue;
                };
            };

            if (validMove == 1){
                // check if there is a winner
                int winner = checkWinner(map);

                if (winner == 0){
                    // if there is no winner yet
                    turn = (turn == 1 ? 2 : 1); // change the turn
                    previewMap[previewMapColumn] = 0;
                    previewMap[3] = turn;
                    previewMapColumn = 3;
                } else {    
                    system("cls");
                    if (turn == 1) printf(RED "Player 1's Turn\n\n" RESET);
                    else printf(BLUE "Player 2's Turn\n\n" RESET);
                    previewDisc(previewMap);
                    printBoard(map);
                    printf("Controls: [LEFT / RIGHT] to move | [SPACE] to drop | [ESC] to quit\n");
                    printf(RED "X = Player 1          " RESET);
                    printf(BLUE "O = Player 2\n" RESET);

                    running = 0;
                    if (winner == 1) printf(RED "Player 1 WON the Game!\n" RESET);
                    else if (winner == 2) printf(BLUE "Player 2 WON the Game!\n" RESET);
                    else if (winner == -1) printf(YELLOW "It's a TIE!\n" RESET);
                    printf("Press any key to return to main menu...");
                    getch();
                }
            };
        };  
    };

    return;
};

void showInstructions(){
    int show = 1;
    while(show){
        system("cls");
        printf("+----------------------------------------------------------+\n");
        printf("|                                                          |\n");
        printf("|                        HOW TO PLAY                       |\n");
        printf("|                                                          |\n");
        printf("|                                                          |\n");
        printf("|   1. The game is played on a grid that's 7x6.            |\n");
        printf("|   2. Take turns dropping discs from the top.             |\n");
        printf("|   3. Connect 4 discs vertically, horizontally,           |\n");
        printf("|      or diagonally to win.                               |\n");
        printf("|   4. If the board fills up, it's a draw.                 |\n");
        printf("|                                                          |\n");
        printf("|                                                          |\n");
        printf("|            Press [ESC] or [ENTER] to return...           |\n");
        printf("+----------------------------------------------------------+\n");

        int c = _getch();
        if (c == 13 || c == 27){
            // ENTER and ESC
            show = 0;
        };
    };

    return;
};

int main(){
    int running = 1;
    int choice = 1;

    while (running){
        printf("l i n H K u p\n");
        printf("================\n");
        if (choice == 1){
            printf(">>   Start Game   <<\n");
            printf("    Instructions    \n");
            printf("        Exit        \n");
        } else if (choice == 2){
            printf("     Start Game     \n");
            printf(">>  Instructions  <<\n");
            printf("        Exit        \n");
        } else {
            printf("     Start Game     \n");
            printf("    Instructions    \n");
            printf(">>      Exit      <<\n");
        };

        int c = _getch();
        if (c == 224){
            c = _getch();

            if (c == 72){
                choice = choice > 1 ? choice - 1 : 1;
            } else if (c == 80){
                choice = choice < 3 ? choice + 1 : 3;
            } 
        } else if (c == 13){
            // enter key
            if (choice == 1){
                // enter the game
                mainGame();
            } else if (choice == 2){
                // show the instructions
                showInstructions();
            } else {
                // exit
                running = 0;
                continue;
            };
        };

        system("cls");
    };

    return 0;
}