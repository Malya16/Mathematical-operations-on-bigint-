#ifndef BIGINT_H
#define BIGINT_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int sign; // 0 for positive, 1 for negative
} BigInt;

// Function to initialize a BigInt from a string
BigInt* initBigInt(const char* str);

// Function to free memory used by a BigInt
void freeBigInt(BigInt* num);

// Function to add two BigIntegers
BigInt* addBigInt(BigInt* num1, BigInt* num2);

// Function to subtract two BigIntegers
BigInt* subtractBigInt(BigInt* num1, BigInt* num2);

// Function to multiply two BigIntegers
BigInt* multiplyBigInt(BigInt* num1, BigInt* num2);

// Function to divide two BigIntegers (integer division)
BigInt* divideBigInt(BigInt* num1, BigInt* num2);

// Function to print a BigInt
void printBigInt(BigInt* num);

#endif
