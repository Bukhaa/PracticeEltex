#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

uint32_t ip_to_uint32(const char* ip){
	
	uint32_t val = 0;
	uint8_t octet;
	char* ip_copy = strdup(ip);
	char* token = strtok(ip_copy, ".");
	
	for(size_t i = 0; i < 4; ++i){
		if(token != NULL){
			octet = (uint8_t)atoi(token);
			val = (val << 8) | octet;
			token = strtok(NULL, ".");
		}
	}
	free(ip_copy);
	return val;
}

int chek_ip (uint32_t ip_gw_i, uint32_t mask_i, uint32_t ip_adr_i ){
    
    if((ip_gw_i & mask_i) == (ip_adr_i & mask_i))
        return 1;
    
    else
        return 0;
}

int main(int argc, char* argv[]){
	
	if(argc != 4)
	{
		printf("Not all arguments!\n");
		abort();
	}
	
	uint32_t ip_gw = ip_to_uint32(argv[1]);
    uint32_t mask = ip_to_uint32(argv[2]);
	int count = atoi(argv[3]);
	
	double sum = 0;
	 srand(time(NULL));
    for(int i = 0; i < count; i++) { 
	
        uint32_t random_ip = (rand() % 255) << 24 | (rand() % 255) << 16 | (rand() % 255) << 8 | (rand() % 255);
        printf("Сгенерированный IP: %u.%u.%u.%u  \n", (random_ip >> 24) & 0xFF, (random_ip >> 16) & 0xFF, (random_ip >> 8) & 0xFF, random_ip & 0xFF);
        sum +=chek_ip(ip_gw, mask, random_ip);
		
    }
	
	double res = sum/count;
	printf("Результат: %f \n", res);
	
    
	return  0;
}