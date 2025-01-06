#include <stdio.h> 
#include <stdarg.h>

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