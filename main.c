
#include "lib.h"

#include <stdio.h>


int main() {

    int base, exp, mod;

    printf("Write base:");
    scanf("%d", &base);

    printf("Write exp:");
    scanf("%d", &exp);
    
    printf("Write mod:");
    scanf("%d", &mod);
 
    uint64_t result = mod_exp(base, exp, mod);

    printf("Result: %ld\n", result);

    return 0;
}
