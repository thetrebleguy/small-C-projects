#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <conio.h>
#include <windows.h>

typedef struct Trie {
    struct Trie* children[256]; // 256 to fit all the ascii characters
    char description[101]; // stores the description
    bool terminal; // end of the node
} Trie;

Trie* createNewTrie(char* description){
    // allocate the new trie
    Trie* newTrie = (Trie*)malloc(sizeof(Trie));

    for (int i = 0; i < 256; i++){
        newTrie->children[i] = NULL;
    };

    strcpy(newTrie->description, description);
    newTrie->terminal = false;
    return newTrie;
};

void insertNewSlang(Trie** root) {
    system("cls"); 
    char slangWord[51]; 
    char slangWordDescription[101];
    int moreThanOneCharacter = 0;
    int noSpace = 0;

    // insert a new slang word
    do {
        noSpace = 1;
        moreThanOneCharacter = 0; 

        printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
        scanf("%[^\n]", slangWord); getchar();

        int strLength = strlen(slangWord);
        for (int i = 0; i < strLength; i++){
            if (slangWord[i] == ' '){
                noSpace = 0;
                break;
            };
        };

        // check if it has more than 1 character, if it doesn't, it is invalid
        if (strLength <= 1) moreThanOneCharacter = 0;
        else moreThanOneCharacter = 1;
    } while (!moreThanOneCharacter || !noSpace);

    // insert the description
    int amountOfSpace = 0;

    do {
        amountOfSpace = 0; 
        printf("Input a new slang word description [Must be more than 2 words]: ");
        scanf("%[^\n]", slangWordDescription); getchar(); 

        int strLength = strlen(slangWordDescription);
        for (int i = 0; i < strLength; i++){
            if (slangWordDescription[i] == ' ') amountOfSpace++;
        };
    } while (amountOfSpace < 1);
    
    // if the root doesnt exists, then set it to the new trie
    if (*root == NULL) {
        (*root) = createNewTrie(slangWordDescription);
    };

    // make the new trie
    Trie* temp = (*root);
    int length = strlen(slangWord);

    for (int i = 0; i < length; i++){
        if (temp->children[slangWord[i]] == NULL){
            temp->children[slangWord[i]] = createNewTrie(slangWordDescription);
        };
        temp = temp->children[slangWord[i]];
    };
    
    if (temp->terminal){
        printf("Successfully released new slang word.\n");
        printf("Press enter to continue...\n");
        getch();
    } else {
        printf("Successfully released new slang word.\n");
        printf("Press enter to continue...\n");
        getch();
        temp->terminal = true;
    };

    return;
};

void printTrieRec(Trie* node, char* prefix, int length){
    char newPrefix[length + 2];
    memcpy(newPrefix, prefix, length);
    newPrefix[length + 1] = 0;

    if (node->terminal){
        printf("-> %s\n", prefix);
    };

    for (int i = 0; i < 256; i++){
        if (node->children[i] != NULL){
            newPrefix[length] = i;
            printTrieRec(node->children[i], newPrefix, length + 1);
        };
    };
};

void searchSlangWord(Trie* root){
    system("cls");
    char slangWord[51];
    int moreThanOneCharacter = 0;
    int noSpace = 0;

    // insert a new slang word
    do {
        noSpace = 1;
        moreThanOneCharacter = 0;

        printf("Input slang word to search [Must be more than 1 characters and contains no space]: ");
        scanf("%[^\n]", slangWord); getchar();

        int strLength = strlen(slangWord);
        for (int i = 0; i < strLength; i++){
            if (slangWord[i] == ' '){
                noSpace = 0;
                break;
            };
        };

        if (strLength <= 1) moreThanOneCharacter = 0;
        else moreThanOneCharacter = 1;
    } while (!moreThanOneCharacter || !noSpace);

    // check if the trie is empty
    if (root == NULL) {
        printf("\nThere is no word \"%s\" in the dictionary\n", slangWord);
        printf("Press enter to continue...\n");
        getch();
        return;
    };

    // if the trie is not empty, traverse
    Trie* current = root;
    int strLength = strlen(slangWord);

    for (int i = 0; i < strLength; i++){
        char c = slangWord[i];

        if (current->children[c] == NULL) {
            printf("\nThere is no word \"%s\" in the dictionary\n", slangWord);
            printf("Press enter to continue...\n");
            getch();
            return;
        };
        current = current->children[c];
    };

    if (current->terminal){
        printf("Slang word: %s\n", slangWord);
        printf("Description: %s\n", current->description);
    }
    else printf("\nThere is no word \"%s\" in the dictionary\n", slangWord);
    
    printf("Press enter to continue...\n");
    getch();
    return;
};

void searchPrefixWord(Trie* root){
    system("cls");
    char prefixWord[51];

    printf("Input a prefix to be searched: ");
    scanf("%[^\n]", prefixWord); getchar();

    int prefixLength = strlen(prefixWord);
    Trie* current = root;

    for (int i = 0; i < prefixLength; i++){
        char c = prefixWord[i];
        
        if (current == NULL || current->children[c] == NULL) {
            printf("\nThere is no prefix \"%s\" in the dictionary.\n", prefixWord);
            printf("Press enter to continue...\n");
            getch();
            return;
        }
        current = current->children[c];
    };
    
    printf("Words starts with \"%s\":\n", prefixWord);
    
    char buffer[51];
    strcpy(buffer, prefixWord);
    
    printTrieRec(current, buffer, prefixLength);

    printf("\nPress enter to continue...\n");
    getch();
    return;
};

void viewAllSlangWord(Trie* root){
    system("cls");
    if (root == NULL){
        printf("There is no slang word yet in the dictionary.\n");
        printf("Press enter to continue...\n");
        getch();
        return;
    };

    printf("List of all slang words in the dictionary:\n");
    printTrieRec(root, NULL, 0);
    printf("Press enter to continue...\n");
    getch();
    return;
};

void exitMessage(){
    system("cls");
    printf("Thank you... Have a nice day :)\n");  
};

int main(){
    Trie *root = NULL;
    int choice;

    do {
        system("cls");
        printf("=====================================\n");
        printf("B O O G L E\n");
        printf("=====================================\n");
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf(">> ");
        scanf("%d", &choice); getchar();

        switch (choice) {
            case 1:
                insertNewSlang(&root);
                break;
            case 2:
                searchSlangWord(root);
                break;
            case 3:
                searchPrefixWord(root);
                break;
            case 4:
                viewAllSlangWord(root);
                break;
            case 5:
                exitMessage();
                break;
            default:
                break;
        };
    } while (choice != 5);

    return 0;
}