#include <stdio.h>
#include <gmp.h>


int main() {
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	unsigned long seed = time(NULL);
	gmp_randseed_ui(state, seed);
	
	int bits = 1024;
	mpz_t a, prob_prime;
	mpz_inits(a, prob_prime, NULL);
	
	int maxiters = 1000;
	while(maxiters--) {
		// printf("temp\n");
		mpz_rrandomb(a, state, bits);
		int res = mpz_probab_prime_p(a, 25);
		if(res == 1) {
			// gmp_printf("The generated random number %Zd is probably prime\n", a);
			mpz_set(prob_prime, a);
		}else if(res == 2) {
			gmp_printf("The generated random number %Zd is prime\n", a);
			return 0;
		}
	}
	gmp_printf("The generated random number %Zd is probably prime\n", prob_prime);
	printf("\n");
	return 0;
}
