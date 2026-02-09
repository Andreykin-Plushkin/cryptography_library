
#include "lib.h"

#include <stdio.h>


void test_mod_exp();
void test_gcd();


int main() {
   
    test_mod_exp();
    test_gcd();

    return 0;
}

void test_mod_exp() {
    
    int base, exp, m;

    printf("Write base:");
    scanf("%d", &base);

    printf("Write exp:");
    scanf("%d", &exp);

    printf("Write mod:");
    scanf("%d", &m);

    uint64_t result = mod_exp(base, exp, m);

    printf("[x^a mod p] result: %lu\n", result);
}

void test_gcd() {

    int a, b;

    printf("Write a:");
    scanf("%d", &a);

    printf("Write b:");
    scanf("%d", &b);

    printf("[GCD] result: %lu\n", gcd(a, b));
}
