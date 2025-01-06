#include <stdio.h> 
#include <stdarg.h>

int mul(int n, ...) {
    int result = 1;
    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; i++) {
        result *= va_arg(args, int);
    }
    va_end(args);
    return result ;
}