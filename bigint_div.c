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

// Function to append a digit to the end of a BigInt
void appendDigit(BigInt* num, int digit) {
    Node* newNode = createNode(digit);
    
    if (num->head == NULL) {
        num->head = newNode;
    } else {
        Node* current = num->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to create a copy of a BigInt
BigInt* copyBigInt(BigInt* num) {
    BigInt* copy = (BigInt*)malloc(sizeof(BigInt));
    copy->head = NULL;
    copy->sign = num->sign;

    Node* current = num->head;
    Node* copyCurrent = NULL;

    while (current) {
        Node* newNode = createNode(current->data);
        if (copy->head == NULL) {
            copy->head = newNode;
            copyCurrent = copy->head;
        } else {
            copyCurrent->next = newNode;
            copyCurrent = copyCurrent->next;
        }
        current = current->next;
    }

    return copy;
}

//function to compare two BigIntegers
int compareBigInt(BigInt* num1, BigInt* num2) {
    if (num1->sign > num2->sign) return 1;
    if (num1->sign < num2->sign) return -1;

    Node* n1 = num1->head;
    Node* n2 = num2->head;

    // Skip leading zeros
    while (n1 && n1->data == 0) n1 = n1->next;
    while (n2 && n2->data == 0) n2 = n2->next;

    // Compare lengths
    while (n1 && n2) {
        if (n1->data > n2->data) return 1;
        if (n1->data < n2->data) return -1;
        n1 = n1->next;
        n2 = n2->next;
    }

    if (n1) return 1;
    if (n2) return -1;

    return 0; // Both are equal
}

// Function to subtract num2 from num1 if (num1 >= num2)
BigInt* subtract(BigInt* num1, BigInt* num2) {
    BigInt* result = (BigInt*)malloc(sizeof(BigInt));
    result->head = NULL;
    result->sign = 0; // Initialize the result as positive by default

    int borrow = 0;

    Node* n1 = num1->head;
    Node* n2 = num2->head;

    while (n1 || n2) {
        int digit1 = (n1) ? n1->data : 0;
        int digit2 = (n2) ? n2->data : 0;

        int difference = digit1 - digit2 - borrow;

        if (difference < 0) {
            difference += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        Node* newNode = createNode(difference);
        newNode->next = result->head;
        result->head = newNode;

        if (n1) n1 = n1->next;
        if (n2) n2 = n2->next;
    }

    // Remove leading zeros from the result
    while (result->head && result->head->data == 0) {
        Node* temp = result->head;
        result->head = result->head->next;
        free(temp);
    }

    // If the result is zero, set its sign to positive
    if (!result->head) {
        result->sign = 0;
    }

    return result;
}

// Function to divide two BigIntegers (integer division)
BigInt* divideBigInt(BigInt* num1, BigInt* num2) {
    BigInt* result = (BigInt*)malloc(sizeof(BigInt));
    result->head = NULL;
    result->sign = num1->sign ^ num2->sign; // Determine the sign of the result

    if (compareBigInt(num1, num2) < 0) {
        // If num1 < num2, the result is zero
        Node* newNode = createNode(0);
        result->head = newNode;
        return result;
    }

    BigInt* dividend = initBigInt("0");
    BigInt* divisor = copyBigInt(num2);

    Node* n1 = num1->head;

    while (n1) {
        appendDigit(dividend, n1->data);
        n1 = n1->next;

        int quotient = 0;

        while (compareBigInt(dividend, divisor) >= 0) {
            dividend = subtract(dividend, divisor);
            quotient++;
        }

        appendDigit(result, quotient);
    }

    freeBigInt(dividend);
    freeBigInt(divisor);

    // Remove leading zeros from the result
    while (result->head && result->head->data == 0) {
        Node* temp = result->head;
        result->head = result->head->next;
        free(temp);
    }

    // If the result is zero, set its sign to positive
    if (!result->head) {
        result->sign = 0;
    }

    return result;
}
