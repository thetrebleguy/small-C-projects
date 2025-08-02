#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

struct Customer {
    char name[15];
    char number[15];
    int usage;
    float totalBill;
};

struct Customer customerData[100];
int customerCount = 0;

void displayList();
void addRecord();
void viewRecords();
void modifyRecord(char input[]);
void viewPayment(char input[]);
void deleteRecord(char input[]);
int main(){
    int choice = 0;

    printf("Welcome to the Telegram Billing System!\n");
    printf("by: thetrebleguy\n");
    printf("-----------------------------------------\n\n");
    Sleep(3000);

    while(1){
        displayList();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        char input[15];

        switch(choice){
        case 1:
            addRecord();
            break;
        case 2:
            viewRecords();
            break;
        case 3:
            printf("\nEnter a phone number to modify record: ");
            scanf("%s", &input);
            modifyRecord(input);
            break;
        case 4:
            printf("\nEnter a phone number to view payment: ");
            scanf("%s", &input);
            viewPayment(input);
            break;
        case 5:
            printf("\nEnter a phone number to delete payment: ");
            scanf("%s", &input);
            deleteRecord(input);
            break;
        case 6:
            printf("\nThank you for using the telegram billing system!\n");
            return 0;
        default:
            printf("\nPlease pick a valid number!\n\n");
            break;
        }
    }
    return 0;
};

void displayList(){
    printf("What would you like to do?\n");
    printf("1. Add New Record\n");
    printf("2. View List of Records\n");
    printf("3. Modify Record\n");
    printf("4. View Payment\n");
    printf("5. Delete Record\n");
    printf("6. Exit\n");
};

void addRecord(){
    printf("\n-------------- NEW RECORD --------------\n");
    printf("Enter your name: ");
    scanf(" %[^\n]s", &customerData[customerCount].name);
    printf("Enter your phone number: ");
    scanf(" %[^\n]s", &customerData[customerCount].number);
    printf("Enter usage (in minutes): ");
    scanf(" %d", &customerData[customerCount].usage);
    customerData[customerCount].totalBill = customerData[customerCount].usage * 0.11;
    printf("Total Bill: $%.2f", customerData[customerCount].totalBill);
    customerCount++;
    printf("\n-----------------------------------------\n\n");
    Sleep(2000);
};

void viewRecords(){
    printf("\nName:               Phone Number:       Usage (minutes):     Total Bill:     \n");
    for (int i = 0; i < customerCount; i++){
        printf("%-20s%-20s%-21d$%.2f\n", customerData[i].name, customerData[i].number, customerData[i].usage, customerData[i].totalBill);
    };
    Sleep(5000);
    printf("\n");
};

void modifyRecord(char input[]){
    printf("\nSearching for phone number...\n");
    Sleep(3000);

    for (int i = 0; i < customerCount; i++){
        if (strcmp(input, customerData[i].number) == 0){
            printf("Enter new usage (in minutes) for %s: ", customerData[i].name);
            scanf(" %d", &customerData[i].usage);
            
            // calculate new total bill
            customerData[i].totalBill = customerData[i].usage * 0.11;

            printf("\n------------ MODIFIED RECORD ------------\n");
            printf("Name: %s\nPhone Number: %s\n", customerData[i].name, customerData[i].number);
            printf("Usage: %d minutes\nTotal Bill: $%.2f\n", customerData[i].usage, customerData[i].totalBill);
            printf("-----------------------------------------\n\n");
            Sleep(5000);
            return;
        };
    };
    printf("Cannot find number :(\n\n");
    Sleep(2000);
};

void viewPayment(char input[]){
    printf("\nSearching for payment...\n");
    Sleep(3000);

    for (int i = 0; i < customerCount; i++){
        if (strcmp(input, customerData[i].number) == 0){
            printf("\n---------------- RECORD ----------------\n");
            printf("Name: %s\nPhone Number: %s\n", customerData[i].name, customerData[i].number);
            printf("Usage: %d minutes\nTotal Bill: $%.2f\n", customerData[i].usage, customerData[i].totalBill);
            printf("-----------------------------------------\n\n");
            Sleep(5000);
            return;
        };
    };
    printf("Record not found :(\n\n");
    Sleep(2000);
};

void deleteRecord(char input[]){
    printf("\nSearching for payment...\n");
    Sleep(3000);
    char answer;

    for (int i = 0; i < customerCount; i++){
        if (strcmp(input, customerData[i].number) == 0){
            printf("\n---------------- RECORD ----------------\n");
            printf("Name: %s\nPhone Number: %s\n", customerData[i].name, customerData[i].number);
            printf("Usage: %d minutes\nTotal Bill: $%.2f\n", customerData[i].usage, customerData[i].totalBill);
            printf("-----------------------------------------\n\n");

            while(answer != 'Y' && answer != 'N'){
                printf("Are you sure you delete the record?\nThis action cannot be undone\n(Y/N): ");
                scanf(" %c", &answer);
                answer = toupper(answer);

                if (answer == 'Y'){
                    if (customerCount == 1){
                        strcpy(customerData[0].name, "");
                        strcpy(customerData[0].number, "");
                        customerData[0].usage = 0;
                        customerData[0].totalBill = 0; 
                    } else{
                        for (int j = i; j < customerCount - 1; j++) {
                            customerData[j] = customerData[j + 1];
                        };
                        customerCount--;
                    }
                    printf("\nRecord deleted successfully!\n\n");
                    Sleep(3000);
                } else if (answer == 'N'){
                    printf("Record deletion cancelled!\n\n");
                    Sleep(3000);
                } else{
                    printf("Please pick a valid choice!\n\n");
                    Sleep(2000);
                }
            }
            return;
        };
    };
    printf("Record not found :(\n\n");
    Sleep(2000);
}