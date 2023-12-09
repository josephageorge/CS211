#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node* left;
    struct Node* right;
    int data;
};

struct Node* parent = NULL;

void newNode(int data, struct Node* current) {
    current->data = data;
    current->right = NULL;
    current->left = NULL;
    printf("inserted\n");
}

void insert(int data) {
    if (parent == NULL) {
        parent = malloc(sizeof(struct Node));
        newNode(data, parent);
        return;
    }
    struct Node* previous = NULL;
    struct Node* ptr = parent;
    while (ptr != NULL) {
        previous = ptr;
        if (data < ptr->data)
            ptr = ptr->left;
        else if (data > ptr->data)
            ptr = ptr->right;
        else {
            printf("not inserted\n");
            return;
        }
    }
    ptr = malloc(sizeof(struct Node));
    newNode(data, ptr);
    if (previous != NULL) {
        if (data < previous->data)
            previous->left = ptr;
        else if (data > previous->data)
            previous->right = ptr;
    }
}
void search(int data) {
    struct Node* ptr = parent;
    while (ptr != NULL) {
        if (ptr->data == data) {
            printf("present\n");
            return;
        }
        else if (data > ptr->data) {
            ptr = ptr->right;
        }
        else if (data < ptr->data) {
            ptr = ptr->left;
        }
    }
    printf("absent\n");
}

struct Node* delete(int data, struct Node* parent) {
    if (parent == NULL) {
        printf("absent\n");
        return parent;
    }

    if (data < parent->data)
        parent->left = delete(data, parent->left);
    else if (data > parent->data)
        parent->right = delete(data, parent->right);
    else {
        if (parent->left == NULL) {
            struct Node* temp = parent->right;
            free(parent);
            printf("deleted\n");
            return temp;
        } else if (parent->right == NULL) {
            struct Node* temp = parent->left;
            free(parent);
            printf("deleted\n");
            return temp;
        }

        struct Node* temp = parent->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        parent->data = temp->data;

        parent->right = delete(temp->data, parent->right);
    }
    return parent;
}

void print(struct Node* printed) {
    if (printed != NULL) {
        printf("(");
        print(printed->left);
        printf("%d", printed->data);
        print(printed->right);
        printf(")");
    }
}

void clean(struct Node* parent) {
    if (parent->left != NULL) {
        clean(parent->left);
    }
    if (parent->right != NULL) {
        clean(parent->right);
    }
    free(parent);
}
int main(int argc, char* argv[]) {
    char bst[10];
    int data;
    while (fscanf(stdin, "%s", bst) > 0) {
        if (bst[0] == 'i') {
            fscanf(stdin, "%d", &data);
            insert(data);
        }
        if (bst[0] == 's') {
            fscanf(stdin, "%d", &data);
            search(data);
        }
        if (bst[0] == 'd') {
            fscanf(stdin, "%d", &data);
            parent = delete(data, parent);
        }
        if (bst[0] == 'p') {
            print(parent);
            printf("\n");
        }
    }

    clean(parent);

    return 0;
}
