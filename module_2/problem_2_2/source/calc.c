#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h> 
#include "calc.h"

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