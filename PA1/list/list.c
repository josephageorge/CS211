#include <stdio.h>
#include <stdlib.h>

/* Define the Node struct */
struct Node {
    int value;
    struct Node* next;
};

/* Function to create a new Node */
struct Node* createNode(int num) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = num;
    newNode->next = NULL;
    return newNode;
}

/* Function to insert a node into the linked list */
void insert(struct Node** head, int num) {
    struct Node* newNode = createNode(num);

    if (*head == NULL) { /* If there are zero nodes */
        *head = newNode;
        return;
    }

    struct Node* current = *head;
    struct Node* previous = NULL;

    while (current != NULL) {
        if (current->value == num) { /* Check for duplicates */
            free(newNode);
            return;
        }
        if (current->value > num) { /* Insert in the middle of the list */
            newNode->next = current;
            if (previous != NULL) {
                previous->next = newNode;
            } else {
                *head = newNode; /* Update the head if inserting at the beginning */
            }
            return;
        }
        if (current->next == NULL) { /* Reached the end of the list */
            current->next = newNode;
            return;
        }
        previous = current;
        current = current->next;
    }
}

/* Function to print the linked list */
void printList(struct Node* head) {
    struct Node* current = head;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    printf("%d :", count);

    current = head;
    while (current != NULL) {
        printf(" %d", current->value);
        current = current->next;
    }
    printf("\n");
}

void deleteNode(struct Node** head, int num) {
    if (*head == NULL) { /* Check for zero nodes */
        return;
    }

    struct Node* current = *head;
    struct Node* previous = NULL;

    while (current != NULL) {
        if (current->value == num) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                *head = current->next; /* Update the head if deleting the first node */
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void deleteAllNodes(struct Node** head) {
    struct Node* current = *head;

    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    *head = NULL;
}

int main() {
    struct Node* head = NULL;

    int check = 1;
    while (check) {
        char command;
        int number;
        check = scanf(" %c %i", &command, &number);

        if (check == EOF) {
            break;
        }

        if (command == 'i') {
            insert(&head, number);
            printList(head);
        } else if (command == 'd') {
            deleteNode(&head, number);
            printList(head);
        }
    }

    deleteAllNodes(&head); /* Clean up memory */

    return 0;
}
