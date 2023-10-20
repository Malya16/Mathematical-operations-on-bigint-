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

// Function to subtract two BigIntegers
BigInt* subtractBigInt(BigInt* num1, BigInt* num2) {
    BigInt* result = (BigInt*)malloc(sizeof(BigInt));
    result->head = NULL;
    result->sign = 0; // Initialize the result as positive by default

    int borrow = 0;

    Node* n1 = num1->head;
    Node* n2 = num2->head;

    while (n1 || n2) {
	int digit1;
	if (n1) 
	{
   	   digit1 = n1->data;
	} 
 	else {
   	   digit1 = 0;
	}

        int digit2;
	if(n2)
	{
	   digit2=n2->data;
	}
	else {
	   digit2=0;
	}
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
