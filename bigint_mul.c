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

//function to shift a BigInt to the left
void shiftLeft(BigInt* num, int numDigits) {
    while (numDigits > 0) {
        Node* newNode = createNode(0);
        newNode->next = num->head;
        num->head = newNode;
        numDigits--;
    }
}

BigInt* multiplyBigInt(BigInt* num1, BigInt* num2) {
    BigInt* result = (BigInt*)malloc(sizeof(BigInt));
    result->head = NULL;
    result->sign = num1->sign ^ num2->sign; // Determine the sign of the result

    Node* n1 = num1->head;
    
    while (n1) {
        int digit1 = n1->data;
        Node* n2 = num2->head;
        BigInt* tempResult = (BigInt*)malloc(sizeof(BigInt));
        tempResult->head = NULL;
        tempResult->sign = 0;

        int carry = 0;

        while (n2) {
            int digit2 = n2->data;
            int product = digit1 * digit2 + carry;
            carry = product / 10;
            product = product % 10;
            
            Node* newNode = createNode(product);
            newNode->next = tempResult->head;
            tempResult->head = newNode;

            n2 = n2->next;
        }

        if (carry > 0) {
            Node* newNode = createNode(carry);
            newNode->next = tempResult->head;
            tempResult->head = newNode;
        }

        // Shift the temporary result to the left based on the position of n1
        shiftLeft(tempResult, n1->data);

        // Add the temporary result to the final result
        result = addBigInt(result, tempResult);

        freeBigInt(tempResult);

        n1 = n1->next;
    }

    return result;
}
