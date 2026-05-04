// saving this bcs i dont wanna write it agen limao
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNewNode(int val){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = val;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
};

void pushHead(Node** head, Node** tail, int val){
    Node* newNode = createNewNode(val);

    if (*head == NULL){
        (*head) = (*tail) = newNode;
        return;
    };

    newNode->next = (*head);
    (*head)->prev = newNode;
    (*head) = newNode;
};

void pushTail(Node** head, Node** tail, int val){
    Node* newNode = createNewNode(val);

    if (*head == NULL){
        (*head) = (*tail) = newNode;
        return;
    };

    (*tail)->next = newNode;
    newNode->prev = (*tail);
    (*tail) = newNode;
};

void pushMid(Node** head, Node** tail, int val){
    Node* newNode = createNewNode(val);

    if (*head == NULL){
        pushHead(head, tail, val);
    } else if (val < (*head)->value){
        pushHead(head, tail, val);
    } else if (val > (*tail)->value){
        pushTail(head, tail, val);
    } else {
        Node* current = (*head);
        while (current && (current->value < val)){
            current = current->next;
        };

        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
};

void popHead(Node** head, Node** tail){
    if ((*head) == NULL){
        printf("Linked List is Empty\n");
        return;
    };

    Node* temp = (*head);
    if ((*head) == (*tail)){
        (*head) = (*tail) = NULL;
    } else {
        (*head) = (*head)->next;
        (*head)->prev = NULL;
    };

    free(temp);
};

void popTail(Node** head, Node** tail){
    if ((*head) == NULL){
        printf("Linked List is Empty\n");
        return;
    };

    Node* temp = (*tail);
    if ((*head) == (*tail)){
        (*head) = (*tail) = NULL;
    } else {
        (*tail) = (*tail)->prev;
        (*tail)->next = NULL;
    };

    free(temp);
};

void popMid(Node** head, Node** tail, int val){
    // CONDITIONS
    // 1. linked list empty
    // 2. head->val == val, popHead
    // 3. tail->val == val, popTail
    // 4. popMid (search the value first)

    if ((*head) == NULL){
        printf("Linked List is Empty\n");
        return;
    } else if (val == (*head)->value){
        popHead(head, tail);
    } else if (val == (*tail)->value){
        popTail(head, tail);
    } else{
        Node *current = (*head);
        while (current && val != current->value){
            current = current->next;
        };

        if (current){
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
        };
    };
};

void display(Node* head){
    if (head == NULL){
        printf("Linked List is Empty!\n");
    };

    Node *current = head;
    while (current){
        printf("[%d] <=> ", current->value);
        current = current->next;
    };
    printf("\n");
};

int main(){
    Node *head = NULL;
    Node *tail = NULL;

    pushHead(&head, &tail, 10);
    pushHead(&head, &tail, 5);
    pushTail(&head, &tail, 20);
    pushTail(&head, &tail, 30);
    pushTail(&head, &tail, 45);
    pushTail(&head, &tail, 67);
    pushTail(&head, &tail, 70);
    pushHead(&head, &tail, 3);
    pushMid(&head, &tail, 15);
    display(head);

    popHead(&head, &tail);
    popHead(&head, &tail);
    popTail(&head, &tail);
    display(head);

    popMid(&head, &tail, 45);
    display(head);
    return 0;
}