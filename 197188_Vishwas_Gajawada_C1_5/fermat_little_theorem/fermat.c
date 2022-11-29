#include <stdio.h>
#include <gmp.h>
#include <time.h>

int main() {
    mpz_t p, a, pm1; // p -1
    mpz_inits(p, a, pm1, NULL);

    printf("Enter a prime to test Fermat primality\n");
    gmp_scanf("%Zd", p);

    int k;
    printf("Number of times to run the test - ");
	scanf("%d", &k);

    // using random
	int seed = (int)time(NULL);
	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state, seed);

    mpz_sub_ui(pm1, p, 1);
    for(int i=0;i<k;) {
        // generate random a between [2, n-2]
        mpz_urandomm(a, state, pm1); // a is random from [0, p-2]
        if(mpz_cmp_ui(a, 2) < 0 ) continue; // if a is 0 or 1 ignore
        // generate a^(p-1) % p
        mpz_powm(a, a, pm1, p);

        if(mpz_cmp_ui(a, 1) != 0 ) {
            gmp_printf("%Zd is a composite number\n", p);
            return 1;
        }
        i++;
    }
    gmp_printf("%Zd is probably prime number\n", p);

    return 0;
}