
#include "lib.h"

#include <stdio.h>


int main() {

    uint64_t base, exp, mod;

    printf("Write base:");
    scanf("%lu", &base);

    printf("Write exp:");
    scanf("%lu", &exp);
    
    printf("Write mod:");
    scanf("%lu", &mod);
 
    uint64_t result = mod_exp(base, exp, mod);

    printf("Result: %ld\n", result);

    return 0;
}
