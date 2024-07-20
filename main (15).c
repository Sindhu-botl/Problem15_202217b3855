#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

// Structure for each entry in the hash table
struct Node {
    char key[50];
    char value[50];
    struct Node* next;
};

// Hash table structure
struct HashTable {
    struct Node* table[SIZE];
};

// Function to create a new node
struct Node* createNode(char key[], char value[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->key, key);
    strcpy(newNode->value, value);
    newNode->next = NULL;
    return newNode;
}

// Function to compute hash index
int hashFunction(char key[]) {
    // Simple hash function: sum of ASCII values of characters modulo SIZE
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % SIZE;
}

// Function to insert key-value pair into hash table
void insert(struct HashTable* ht, char key[], char value[]) {
    int index = hashFunction(key);
    struct Node* newNode = createNode(key, value);

    // If bucket is empty
    if (ht->table[index] == NULL) {
        ht->table[index] = newNode;
    } else {
        // Collision handling: insert at the beginning of the list
        newNode->next = ht->table[index];
        ht->table[index] = newNode;
    }
}

// Function to search for a key in the hash table
char* search(struct HashTable* ht, char key[]) {
    int index = hashFunction(key);
    struct Node* current = ht->table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL; // Key not found
}

// Function to delete a key from the hash table
void delete(struct HashTable* ht, char key[]) {
    int index = hashFunction(key);
    struct Node* current = ht->table[index];
    struct Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                // If first node is the match
                ht->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to print all key-value pairs in the hash table
void printHashTable(struct HashTable* ht) {
    for (int i = 0; i < SIZE; i++) {
        struct Node* current = ht->table[i];
        while (current != NULL) {
            printf("%s\n", current->value);
            current = current->next;
        }
    }
}

int main() {
    // Create a hash table
    struct HashTable ht;
    for (int i = 0; i < SIZE; i++) {
        ht.table[i] = NULL;
    }

    // Insert key-value pairs
    insert(&ht, "Manish", "Manish");
    insert(&ht, "Anjali", "Anjali");
    insert(&ht, "Vartika", "Vartika");
    insert(&ht, "Mayank", "Mayank");
    insert(&ht, "BITS", "BITS");

    // Search for key-value pairs
    printf("%s\n", search(&ht, "Manish"));
    printf("%s\n", search(&ht, "Anjali"));
    printf("%s\n", search(&ht, "Vartika"));
    printf("%s\n", search(&ht, "Mayank"));
    printf("%s\n", search(&ht, "BITS"));
    printf("%s\n", search(&ht, "Sakshi")); // Should print "Oops! No data found."

    // Delete a key from hash table
    delete(&ht, "Manish");

    // After deletion, search for deleted key
    printf("\nAfter deletion :\n");
    printf("%s\n", search(&ht, "Manish")); // Should print "Oops! No data found."

    return 0;
}