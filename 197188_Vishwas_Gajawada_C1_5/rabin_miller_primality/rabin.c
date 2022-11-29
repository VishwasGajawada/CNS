#include <stdio.h>
#include <gmp.h>
#include <time.h>

// p-1 = 2^s * d
void find_s_d(mpz_t p, mpz_t s, mpz_t d) {
    mpz_t pm1;
    mpz_inits(pm1, NULL);
    mpz_sub_ui(pm1, p, 1);

    mpz_set_ui(s, 0);
    while(mpz_even_p(pm1)) {
        mpz_cdiv_q_ui(pm1, pm1, 2);
        mpz_add_ui(s, s, 1);
    }

    mpz_set(d, pm1);

    gmp_printf("%Zd - 1 = 2^(%Zd) * %Zd\n", p, s, d);
}

int main() {
    mpz_t p, s, d, pm1, a, x, j;
    mpz_inits(p, s, d, pm1, a, x, j, NULL);

    printf("Enter a prime(p > 3) to test Rabin-Miller primality\n");
    gmp_scanf("%Zd", p);

    if(mpz_cmp_ui(p, 4) < 0) {
        printf("Enter prime p > 3\n");
        return 1;
    }
    int k;
    printf("Number of times to run the test - ");
	scanf("%d", &k);

    // using random
	int seed = (int)time(NULL);
	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state, seed);

    // p-1 = 2^s * d
    find_s_d(p, s, d);

    mpz_sub_ui(pm1, p, 1);
    for(int i=0;i<k;) {
        // generate random a between [2, n-2]
        mpz_urandomm(a, state, pm1); // a is random from [0, p-2]
        if(mpz_cmp_ui(a, 2) < 0 ) continue; // if a is 0 or 1 ignore

        // x = a^d % p
        mpz_powm(x, a, d, p);
        if (mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, pm1) == 0) { // x == 1 or x == p-1
            i++;
			continue;
		}

        int prob_prime = 0;
        mpz_set_ui(j, 0);
        for(; mpz_cmp(j, s) < 0 ; mpz_add_ui(j, j, 1)) {
            mpz_powm_ui(x, x, 2, p);
            if(mpz_cmp(x, pm1) == 0) {
                prob_prime = 1;
                break;               
            }
        }
        if(prob_prime == 0) {
            gmp_printf("%Zd is a composite number\n", p);
            return 1;
        }
        i++;
    }
    gmp_printf("%Zd is probably prime number\n", p);
    return 0;
}