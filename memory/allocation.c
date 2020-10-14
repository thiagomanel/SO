#include <stdio.h>
#include <stdlib.h>

int n_turns = 5;    // variável global iniciada (static)
int i_global;       // variável global não iniciada (bss)
     
void add_all(int *i_dynamic)
{
    int i_local = 0; // variável local (stack)
    
    printf ("i_global: %d, i_local: %d, i_dynamic: %d\n", i_global, i_local, *i_dynamic);
    i_global++;
    i_local++;
    (*i_dynamic)++;
}
     
int main() {
    int *i_dynamic;                     // variável local (stack)
    i_dynamic = malloc(sizeof(int));    // memória alocada dinamicamente (heap)
    *i_dynamic = 0;
    
    for(int j=0; j<n_turns; j++) {
        add_all(i_dynamic);
    }
}
