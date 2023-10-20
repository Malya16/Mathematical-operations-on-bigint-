#include<stdio.h>
#include<stdlib.h>
#include "bigint.h"

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to add two BigIntegers
BigInt* addBigInt(BigInt* num1, BigInt* num2) {
    BigInt* result = (BigInt*)malloc(sizeof(BigInt));
    result->head = NULL;
    result->sign = 0; // Initialize the result as positive by default

    int carry = 0;

    Node* n1 = num1->head;
    Node* n2 = num2->head;

    while (n1 || n2) {
        int digit1 = (n1) ? n1->data : 0;
        int digit2 = (n2) ? n2->data : 0;

        int sum = digit1 + digit2 + carry;

        carry = sum / 10;
        sum = sum % 10;

        Node* newNode = createNode(sum);
        newNode->next = result->head;
        result->head = newNode;

        if (n1) n1 = n1->next;
        if (n2) n2 = n2->next;
    }

    // If there's a carry left after adding all digits, add it as a new digit
    if (carry > 0) {
        Node* newNode = createNode(carry);
        newNode->next = result->head;
        result->head = newNode;
    }

    return result;
}
