#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to initialize a BigInt from a string
BigInt* initBigInt(const char* str) {
    BigInt* num = (BigInt*)malloc(sizeof(BigInt));
    num->head = NULL;
    num->sign = 0; 

    int len = strlen(str);
    int startIdx = 0;

    // Check for a negative sign
    if (str[0] == '-') {
        num->sign = 1; // Negative
        startIdx = 1;
    }

    for (int i = startIdx; i < len; i++) {
        Node* newNode = createNode(str[i] - '0');
        newNode->next = num->head;
        num->head = newNode;
    }

    return num;
}

// Function to free memory used by a BigInt
void freeBigInt(BigInt* num) {
    while (num->head) {
        Node* temp = num->head;
        num->head = num->head->next;
        free(temp);
    }
    free(num);
}

// Function to print a BigInt
void printBigInt(BigInt* num) {
    if (num->sign == 1) {
        printf("-");
    }

    Node* current = num->head;
    while (current) {
        printf("%d", current->data);
        current = current->next;
    }

    printf("\n");
}
