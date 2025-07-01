// defining linked list structure
// in each node: ds is a DataSet struct and next is pointer to next node

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// assume input file contains an infoHeader and all sections can be viewed as a ES struct
typedef struct DataSet {
    char uid[10];   // example "003"
    char name[100]; // example "Local Barre Fitness"
    char address[200]; // example "423 Avenue B S, Saskatoon, SK S7M 5N3, Canada"
    char rating[20]; // example "4.5"
} DS;

// linked list struct
typedef struct Node {
    DS ds;
    struct Node* next;
} Node;

// prototypes
Node* createNode(const char* uid, const char* name, const char* address, const char* rating);
void addNodeLast(Node** head, Node* newNode);
void printList(Node* head);
void freeList(Node* head);

int main() {
    Node* head = NULL;

    // testing entries..
    Node* node1 = createNode("001", "bruh Shop", "Bruh Main St, City, Country", "4.2");
    Node* node2 = createNode("002", "bruh Gym", "Burh Elm St, City, Country", "4.5");
    Node* node3 = createNode("003", "bruh Library", "Bhur Oak St, City, Country", "4.8");

    addNodeLast(&head, node1);
    addNodeLast(&head, node2);
    addNodeLast(&head, node3);

    printList(head);
    freeList(head);

    return 0;
}


// returns a pointer to a new node with the given data
Node* createNode(const char* uid, const char* name, const char* address, const char* rating) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    strcpy(newNode->ds.uid, uid);
    strcpy(newNode->ds.name, name);
    strcpy(newNode->ds.address, address);
    strcpy(newNode->ds.rating, rating);
    newNode->next = NULL;
    
    return newNode;
}

// accepts a pointer to the pointer of the head and a pointer to a new node
// , then adds the new node to the end of the list
void addNodeLast(Node** head, Node* newNode) {
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// given the pointer to head node, then print all ds-infos in every node
void printList(Node* head) {
    Node* current = head;
    int nodeChainIndex = 0;
    
    while (current != NULL) {
        printf("Index %d:\n", nodeChainIndex);
        printf("  UID: %s\n", current->ds.uid);
        printf("  Name: %s\n", current->ds.name);
        printf("  Address: %s\n", current->ds.address);
        printf("  Rating: %s\n\n", current->ds.rating);

        current = current->next;
        nodeChainIndex++;
    }
}

// free all
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}




