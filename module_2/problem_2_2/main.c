#include <stdio.h> 
#include "calc.h"

void test_sum(){
	printf("Результат сложения (1+2+3+4+5): %d\n", sum(5,1,2,3,4,5));
	printf("Результат сложения (111+222+333): %d\n", sum(3,111,222,333));
}

void test_sub(){
	printf("Результат вычитания (77-22-1-7-10): %d\n", sub(5,77,22,1,7,10));
	printf("Результат вычитания (111-222-333):  %d\n", sub(3,111,222,333));
}

void test_mul(){
	printf("Результат умножения (10*20*30): %d\n", mul(3,10,20,30));
	printf("Результат умножения (-1*-10*15): %d\n", mul(3,-1,-10,15));
}

void test_divis(){
	printf("Результат деления (72/2/4/3): %d\n", divis(4,72,2,4,3));
	printf("Результат деления (100,2,0,5,2):  %d\n", divis(5,100,2,0,5,2));
}


int main(){
    
    test_sum();
	test_sub();
	test_mul();
	test_divis();
	
	return 0;
}












// #include <stdio.h>
// #include <stdlib.h>
// #include <stdarg.h>

// typedef int (*operation_func)(int, ...);

// int sum(int n, ...) {
    // int result = 0;
    // va_list args;
    // va_start(args, n);
    // for (int i = 0; i < n; i++) {
        // result += va_arg(args, int);
    // }
    // va_end(args);
    // return result;
// }

// int sub(int n, ...) {
    // va_list args;
    // va_start(args, n);
    // int result = va_arg(args, int);
    // for (int i = 1; i < n; i++) {
        // result -= va_arg(args, int);
    // }
    // va_end(args);
    // return result;
// }

// operation_func operations[] = {sum, sub};

// void test_sum(){
	// printf("Результат сложения 1,2,3,4,5: %d\n", operations[0](5,1,2,3,4,5));
	// printf("Результат сложения 111,222,333: %d\n", operations[0](3,111,222,333));
// }

// void test_sub(){
	// printf("Результат вычитания (77-22-1-7-10): %d\n", operations[1](5,77,22,1,7,10));
	// printf("Результат вычитания (111-222-333):  %d\n", operations[1](3,111,222,333));
// }

// int main() {
    
    // test_sum();
	// test_sub();
    
    // return 0;
// }








