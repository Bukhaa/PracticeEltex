#include <stdio.h> 
#include <stdarg.h>
#include <stdlib.h> 
#include <dlfcn.h> 

typedef int (*foopointer)(int n, ...);

typedef struct operations{
	char name;
	foopointer p;
}operations;

int main(){
	
    foopointer sum, sub, mul, divis;
	
	void* handle_sum; void* handle_sub; void* handle_mul; void* handle_divis;
	
    char op;
    
	handle_sum = dlopen("./sum.so", RTLD_LAZY);
	handle_sub = dlopen("./sub.so", RTLD_LAZY);
	handle_mul = dlopen("./mul.so", RTLD_LAZY);
	handle_divis = dlopen("./divis.so", RTLD_LAZY);
		
		if(!handle_sum || !handle_sub || !handle_mul || !handle_divis ){
			fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
			exit(1);
		}
		
		sum = (foopointer) dlsym(handle_sum, "sum");
		sub = (foopointer) dlsym(handle_sub, "sub");
		mul = (foopointer) dlsym(handle_mul, "mul");
		divis = (foopointer) dlsym(handle_divis, "divis");
		
		operations array_operation[] = {
			{'+', sum},
			{'-', sub},
			{'*', mul},
			{'/', divis}
		};
		
    while(1){
		
    printf("Введите операцию (+,-,*,/): ");
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
			break;
		}
			
		    
	}
	
	
	
	}
	
	dlclose(handle_sum);
	dlclose(handle_sub);
	dlclose(handle_mul);
	dlclose(handle_divis);
	return 0;
}
	
	
	
	
