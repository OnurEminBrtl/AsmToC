#include <stdio.h>

void write9digits(int number) {
    int digits = 100000000;
    int is_negative = 0;
    
    if (number < 0) {
        is_negative = 1;
        number = -number;
    }
    
    if (is_negative) {
        putchar('-');
    } else {
        putchar(' ');
    }
    
    int i = 0;
    
label:
    int digit = number / digits;
    putchar(digit + '0');
    number %= digits;
    digits /= 10;
    
    i++;
    
    if (i < 9) {
        goto label;
    }
    
    putchar('\n');
}

int main() {
    const int numberCount = 8;
    int numbers[] = {321762410, 9, 2943018, 0, 19371039, 18, -76241, -208424};
   
    
    for (int j = 0; j < numberCount; j++) {
        write9digits(numbers[j]);
    }
    
    return 0;
} 

