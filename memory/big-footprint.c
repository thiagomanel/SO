#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *my_memory[1024];
    size_t dezeseis_mega = 1024*1024*16;
    
    if (argc != 2) {
        fprintf(stderr, "sintaxe: %s size\n", argv[0]);
        exit(0);
    }
    
    fprintf(stderr, "Alocando memória: ");
    for (int i=0; i<atoi(argv[1]); i++) {
        my_memory[i] = malloc(dezeseis_mega);
    
        for (int j=0; j<dezeseis_mega; j++) {
            *my_memory[i]++ = ((i*j % 62) + 65);
        }
        fprintf(stderr, "%dG ", 16*(i+1)/1024);
        
    }
    fprintf(stderr, "\n");
    getchar();
}
