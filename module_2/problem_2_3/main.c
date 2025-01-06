#include <stdio.h> 
#include <stdarg.h>
#include <stdlib.h> 

typedef int (*foopointer)(int n, ...);

int sum(int n, ...) {
    int result = 0;
    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; i++) {
        result += va_arg(args, int);
    }
    va_end(args);
    return result;
}

int sub(int n, ...) {
    va_list args;
    va_start(args, n);
    int result = va_arg(args, int);
    for (int i = 1; i < n; i++) {
        result -= va_arg(args, int);
    }
    va_end(args);
    return result;
}

int mul(int n, ...) {
    int result = 1;
    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; i++) {
        result *= va_arg(args, int);
    }
    va_end(args);
    return result;
}

int divis(int n, ...) {  
	
	va_list args;  
	va_start(args, n);  
	int delimoe = va_arg(args, int);
	
	for(int i = 1; i < n; i++) { 
		int del = va_arg(args, int);
		
		if(del != 0)
			delimoe /= del;  
		else
			continue;
	} 
	va_end(args); 

	return delimoe; 
}

typedef struct operations{
	char name;
	foopointer p;
}operations;

operations array_operation[] = {
	{'+', sum},
	{'-', sub},
	{'*', mul},
	{'/', divis}
};

int main(){
    
    char op;
    
    while(1){
    
		printf("Введите операцию (+,-,*./): ");
		scanf(" %c", &op);
		
		if(op == '0')
			break;
			
		int count = 5;
		printf("\nВведите 5 аргументов: ");
		int array[count];
		
		for(int i = 0; i < count; ++i){
			int elem;
			scanf("%d", &elem);
			array[i] = elem;
		}
		
		for(size_t i = 0; i < count; ++i){
			if(op == array_operation[i].name){
				int res = array_operation[i].p(5, array[0], array[1], array[2], array[3], array[4]);
				printf("%d\n", res);
			}
		}	

    }
	
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








