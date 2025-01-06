#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

void bit_info(mode_t mode){
	
	printf("Битовое представление: ");
	printf((mode & S_IRUSR) ? "1" : "0");
	printf((mode & S_IWUSR) ? "1" : "0");
	printf((mode & S_IXUSR) ? "1" : "0");
	printf((mode & S_IRGRP) ? "1" : "0");
	printf((mode & S_IWGRP) ? "1" : "0");
	printf((mode & S_IXGRP) ? "1" : "0");
	printf((mode & S_IROTH) ? "1" : "0");
	printf((mode & S_IWOTH) ? "1" : "0");
	printf((mode & S_IXOTH) ? "1" : "0");
	printf("\n");
	
}

void symbol_info(mode_t mode){
	
	printf("Символьное представление: ");
	printf((mode & S_IRUSR) ? "r" : "-");
	printf((mode & S_IWUSR) ? "w" : "-");
	printf((mode & S_IXUSR) ? "x" : "-");
	printf((mode & S_IRGRP) ? "r" : "-");
	printf((mode & S_IWGRP) ? "w" : "-");
	printf((mode & S_IXGRP) ? "x" : "-");
	printf((mode & S_IROTH) ? "r" : "-");
	printf((mode & S_IWOTH) ? "w" : "-");
	printf((mode & S_IXOTH) ? "x" : "-");
	printf("\n");
	
}

mode_t symbol_to_number(const char* file_info){
	
	mode_t mode = 0;
	
	if(file_info[0] == 'r')
		mode = mode | S_IRUSR;
	if(file_info[1] == 'w')
		mode = mode | S_IWUSR;
	if(file_info[2] == 'x')
		mode = mode | S_IXUSR;
	if(file_info[3] == 'r')
		mode = mode | S_IRGRP;
	if(file_info[4] == 'w')
		mode = mode | S_IWGRP;
	if(file_info[5] == 'x')
		mode = mode | S_IXGRP;
	if(file_info[6] == 'r')
		mode = mode | S_IROTH;
	if(file_info[7] == 'w')
		mode = mode | S_IWOTH;
	if(file_info[8] == 'x')
		mode = mode | S_IXOTH;
	
	printf("mode: %o\n", mode);
	return mode;
}

mode_t modern_mode(mode_t mode_cur, char target, char mode_set, char operate)
{
	mode_t itog_mask = 0;
	mode_t temp_mask;
	
	
	switch(mode_set)
	{
		case 'r':
			temp_mask = S_IRUSR | S_IRGRP | S_IROTH;
		break;
		case 'w':
			temp_mask = S_IWUSR | S_IWGRP | S_IWOTH;
		break;
		case 'x':
			temp_mask = S_IXUSR | S_IXGRP | S_IXOTH;
		break;
		default:
			
			exit(EXIT_FAILURE);
	}
	
	
	if(target == 'a' || target == 'u') itog_mask |= temp_mask & (S_IRUSR | S_IWUSR | S_IXUSR);
	if(target == 'a' || target == 'g') itog_mask |= temp_mask & (S_IRGRP | S_IWGRP | S_IXGRP);
	if(target == 'a' || target == 'o') itog_mask |= temp_mask & (S_IROTH | S_IWOTH | S_IXOTH);
	
	
	switch (operate) {
		case '+':
			mode_cur |= itog_mask;
		break;
		case '-':
			mode_cur &= ~itog_mask;
		break;
		case '=':
			if (target == 'a') mode_cur = (mode_cur & ~0777) | itog_mask;
			else
			{
				if (target == 'u') mode_cur = (mode_cur & ~0777) | (itog_mask & 0700);
				if (target == 'g') mode_cur = (mode_cur & ~0777) | (itog_mask & 0070);
				if (target == 'o') mode_cur = (mode_cur & ~0777) | (itog_mask & 0007);
			}
		break;
	}
	
	
	return mode_cur;
}

int main(){
	
	mode_t examples;
	char mode;
	struct stat buf;
	int result;
	
	printf("Для того чтобы ввести права в цифровом формате, нажмите 2, в буквенном формате - 1\n");
	printf("Для того чтобы ввести имя файла нажмите 3\n");
	scanf(" %c", &mode);
	
	if(mode == '1'){
		
		char file_info[10];
		printf("Введите права доступа в буквенном формате: ");
		scanf("%9s", file_info);
		
		examples = symbol_to_number(file_info);
		bit_info(examples);
	}
	
	if(mode == '2'){
		
		printf("Введите права доступа в цифровом формате: ");
		scanf("%o", &examples);
		bit_info(examples);
	}
	
	if(mode == '3'){
		
		char name[30];
		
		printf("Введите имя файла: ");
		scanf("%19s", name);
		
		result = stat(name, &buf);
		
		if( result != 0 ){
			perror( "Problem get information" );
			switch (errno){
				case ENOENT:
				  printf("File %s not found\n", name);
				  exit(EXIT_FAILURE);
				  break;
				case EINVAL:
				  printf("Invalid parameter stat\n");
				  exit(EXIT_FAILURE);
				  break;
				default:
		          printf("Unexpected error stat\n");
				  exit(EXIT_FAILURE);
			}
       }
	   
	   else {
		  bit_info(buf.st_mode);
		  symbol_info(buf.st_mode);
		  
		  printf("Цифровое представление: %o\n", buf.st_mode & 0777);
	  }
		
	}
	
	char update_mode;
	printf("Хотите ли вы изменить права доступа? Если да нажмите 1, иначе 2\n");
	scanf(" %c", &update_mode);
	
	if(update_mode == '1'){
		mode_t new_mode;
		
		char target; char mode_set; char opearate;
		printf("Введите группу пользователя (a - все, u - владелец, g - группа, о - остальные)\n");
		scanf(" %c", &target);
		printf("Введите права (r - чтение, w - запись, x - выполнение)\n");
		scanf(" %c", &mode_set);
		printf("Введите действие ('+' - добавить, '-' - убрать, '=' - установить)\n");
		scanf(" %c", &opearate);
		
		
		if(mode == '1' || mode == '2')
			new_mode = modern_mode(examples, target, mode_set, opearate); 
		
		if(mode == '3')
			new_mode = modern_mode(buf.st_mode, target, mode_set, opearate); 
		
		
		printf("Новые права доступа: \n");
		bit_info(new_mode);
		symbol_info(new_mode);
		printf("Цифровое представление: %o\n", new_mode & 0777);
	}
	
	return 0;
}