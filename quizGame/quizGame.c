#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char question[256];
    char answers[4][64];
    char answer;
} Question;

void mainDialogue(int *option);
void getQuestions(int startQuestionIndex);

int main(){
    int option = 0;
    int *pOption = &option;

    printf("---- QUIZ GAME ----\n");
    printf("by: thetrebleguy\n\n");
    Sleep(3000);

    mainDialogue(pOption);
    getQuestions((option - 1) * 5 + 1);
    return 0;
};

void mainDialogue(int* option){
    printf("Hello! Welcome to the quiz game!\n");
    while ((*option) != 1 && (*option) != 2 && (*option) != 3){
        printf("Which subject would you like to pick? \n\n");
        printf("1. PHYSICS\n2. CHEMISTRY\n3. BIOLOGY\n");
        printf("Your option: ");
        scanf("%d", &(*option));
        switch (*option){
            case 1: 
                printf("\nYou picked PHYSICS!\n");
                break;
            case 2: 
                printf("\nYou picked CHEMISTRY!\n");
                break;
            case 3: 
                printf("\nYou picked BIOLOGY!\n");
                break;
            default:
                printf("\nPlease pick a valid number\n\n");
                break;
        }
    }
}

void getQuestions(int startQuestionIndex){
    FILE *pF = fopen(".\\quizGameQuestions.txt", "r");
    char buffer[255];
    Question original_questions[5];
    int currentLine = 0;
    int questionCount = 0;
    int startLine = (startQuestionIndex - 1) * 6;

    if (pF == NULL){
        printf("Unable to fetch questions :(\n");
        return;
    }

    while (currentLine < startLine && fgets(buffer, sizeof(buffer), pF)){
        currentLine++;
    };

    while (questionCount < 5){
        // reads the question
        fgets(buffer, sizeof(buffer), pF);
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(original_questions[questionCount].question, buffer);

        for (int j = 0; j < 4; j++){
            fgets(buffer, sizeof(buffer), pF);
            buffer[strcspn(buffer, "\n")] = 0;
            strcpy(original_questions[questionCount].answers[j], buffer);
        }

        fgets(buffer, sizeof(buffer), pF);
        buffer[strcspn(buffer, "\n")] = 0;
        original_questions[questionCount].answer = buffer[0];

        questionCount++;
    }

    fclose(pF);
    int score = 0;

    for (int i = 0; i < 5; i++){
        char input = '\0';

        while (input != 'A' && input != 'B' && input != 'C' && input != 'D'){
            printf("\nQuestion %d:\n%s", i+1, original_questions[i].question);
            printf("\nA. %s\nB. %s\nC. %s\nD. %s\n", 
            original_questions[i].answers[0],
            original_questions[i].answers[1],
            original_questions[i].answers[2],
            original_questions[i].answers[3]);
            printf("What is the answer? ");
            scanf(" %c", &input);
            input = toupper(input);
            if (input != 'A' && input != 'B' && input != 'C' && input != 'D'){
                printf("\nPlease enter the valid answer!\n");
            }
        }
        
        if (input == original_questions[i].answer){
            printf("\nThat's correct!\n");
            score++;
        } else{
            printf("\nThat's incorrect! The correct answer is %c\n", original_questions[i].answer);
        }
    };

    printf("\nYour Final Score: ");
    Sleep(3000);
    printf("\n%d / 5 ", score);
    Sleep(2000);
    switch (score){
        case 0: 
            printf("\noof, nice try bro");
            break;
        case 1:
            printf("\nBetter than nothing, I guess?");
            break;
        case 2:
            printf("\nYou're getting there, still far though");
            break;
        case 3:
            printf("\nNot bad! Probably a C");
            break;
        case 4:
            printf("\nAlmost there!");
            break;
        case 5:
            printf("\nGoated");
            break;
        default:
            printf("\nWhat did you do bro");
            break;
    }
}