#include<stdio.h>
#include<stdlib.h>
#include "bigint.h"

int main() {
    char *input1=NULL;
    char* input2=NULL;

    size_t input_size=1000;
    input1=(char*)malloc(input_size);
    input2=(char*)malloc(input_size);

    if(input1==NULL || input2==NULL)
    {
       fprintf(stderr,"Memory allocation failed.\n");
       return 1;
    }
   
    printf("Enter the first big integer: ");
    if (scanf("%999s", input1) != 1) {
        fprintf(stderr, "Failed to read input.\n");
        free(input1);
        free(input2);
        return 1;
    }

    BigInt *num1 = initBigInt(input1);

    printf("Enter the second big integer: ");
    if (scanf("%999s", input2) != 1) {
        fprintf(stderr, "Failed to read input.\n");
        free(input1);
        free(input2);
        freeBigInt(num1);
        return 1;
    }

    BigInt *num2 = initBigInt(input2);

    printf("num1: ");
    printBigInt(num1);

    printf("num2: ");
    printBigInt(num2);

    BigInt* sum = addBigInt(num1, num2);
    printf("Sum: ");
    printBigInt(sum);

    BigInt* diff = subtractBigInt(num1,num2);
    printf("Difference: ");
    printBigInt(diff);
  
    BigInt* multiply=multiplyBigInt(num1,num2);
    printf("Multiplication: ");
    printBigInt(multiply);

    BigInt* divide=divideBigInt(num1,num2);
    printf("Division: ");
    printBigInt(divide);

    free(input1);
    free(input2);
    freeBigInt(num1);
    freeBigInt(num2);
    freeBigInt(sum);
    freeBigInt(diff);
    freeBigInt(multiply);
    freeBigInt(divide);

    return 0;
}
