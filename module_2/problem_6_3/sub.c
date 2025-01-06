#include <stdio.h> 
#include <stdarg.h>

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