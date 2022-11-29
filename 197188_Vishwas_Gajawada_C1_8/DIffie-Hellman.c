
/* code for Diffie Hellman Key exchange */
#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <stdbool.h>

unsigned long seed;
gmp_randstate_t state;

void initRand() {
    seed = (time(NULL));
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}

void genPrime(mpz_t x, int bits) {
    mpz_t rand_num;
    mpz_inits(x, rand_num, NULL);

    mpz_rrandomb(rand_num, state, bits);
    mpz_nextprime(x, rand_num);
}

void init(mpz_t p, mpz_t alpha) {
    mpz_t q, r, p_3, alpha_pow_q, alpha_pow_r;
    mpz_inits(q, r, p_3, alpha_pow_q, alpha_pow_r, NULL);
    genPrime(q, 512);
    genPrime(r, 512);

    mpz_mul(p, q, r);
    mpz_add_ui(p, p, 1); // p = q*r + 1

    mpz_sub_ui(p_3, p, 3);

    // now calculation of alpha (generator)
    while(true) {
        mpz_urandomm(alpha, state, p_3); // alpha [0, p-3]
        mpz_add_ui(alpha, alpha, 2); // alpha [2, p-1]

        mpz_powm(alpha_pow_q, alpha, q, p);
        mpz_powm(alpha_pow_r, alpha, r, p);

        if(mpz_cmp_ui(alpha_pow_q, 1)!=0 && mpz_cmp_ui(alpha_pow_r, 1)!=0) {
            break;
        }        
    }

    gmp_printf("p = %Zd\n\nalpha = %Zd\n\n", p, alpha);
}

void genPrivateKeys(mpz_t xa, mpz_t xb, mpz_t p) {
    mpz_urandomm(xa, state, p);
    mpz_urandomm(xb, state, p);
}

void genPublicKeys(mpz_t ya, mpz_t yb, mpz_t xa, mpz_t xb, mpz_t p, mpz_t alpha) {
    mpz_powm(ya,alpha,xa,p);
    mpz_powm(yb,alpha,xb,p);
}
void computeSharedKey(mpz_t ka, mpz_t kb, mpz_t xa, mpz_t xb, mpz_t ya, mpz_t yb, mpz_t p) {
    mpz_powm(ka, yb, xa, p);
    mpz_powm(kb, ya, xb, p);
}

int main() {
    initRand();
    mpz_t p, alpha, xa, xb, ya, yb, ka, kb;
    mpz_inits(p, alpha, xa, xb, ya, yb, ka, kb, NULL);
    init(p, alpha);
    
    genPrivateKeys(xa, xb, p);
    genPublicKeys(ya, yb, xa, xb, p, alpha);

    gmp_printf("xa = %Zd\n\nxb=%Zd\n\n"
               "ya = %Zd\n\nyb=%Zd\n\n", xa, xb, ya, yb);
               
               
    computeSharedKey(ka, kb, xa, xb, ya, yb, p);
    
    gmp_printf("shared key computed by a = %Zd\n\n"
                "shared key computed by b = %Zd\n\n", ka, kb);
                
    if(mpz_cmp(ka, kb) == 0) {
        gmp_printf("Shared key computed by a and b is same\n");
    }
    return 0;
}