// Vishwas Gajawada 197188

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

void genRand(mpz_t x, int bits ) {
    mpz_rrandomb(x, state, bits);
}

void genPrime(mpz_t x, int bits) {
    mpz_t rand_num;
    mpz_inits(x, rand_num, NULL);

    mpz_rrandomb(rand_num, state, bits);
    mpz_nextprime(x, rand_num);
}

void init(mpz_t p, mpz_t alpha, int bits) {
    mpz_t q, r, p_3, alpha_pow_q, alpha_pow_r;
    mpz_inits(q, r, p_3, alpha_pow_q, alpha_pow_r, NULL);
    genPrime(q, bits/2);
    genPrime(r, bits/2);

    mpz_mul(p, q, r);
    mpz_add_ui(p, p, 1); // p = q*r + 1
    genPrime(p, bits);
    genRand(alpha, bits);
    return;
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

void Sign(mpz_t S1,mpz_t S2,mpz_t a,mpz_t k,mpz_t q,mpz_t x,mpz_t m) {
    mpz_powm(S1,a,k,q);
    
    mpz_t q1,Kinv,t;
    mpz_inits(q1,Kinv,t,NULL);
    mpz_sub_ui(q1,q,1);
    
    mpz_invert(Kinv,k,q1);
    
    mpz_mul(t,x,S1);
    mpz_sub(t,m,t);
    mpz_mul(t,Kinv,t);
    
    mpz_mod(S2,t,q1);
    
    gmp_printf("\nSign in Message: %Zd\nS1 : %Zd\nS2: %Zd\n\n",m,S1,S2);
}

void Verify(mpz_t a,mpz_t m,mpz_t q,mpz_t y,mpz_t S1,mpz_t S2,mpz_t V1,mpz_t V2) {
    mpz_powm(V1,a,m,q);
    mpz_powm(V2,y,S1,q);
    mpz_t t;
    mpz_inits(t,NULL);
    mpz_powm(t,S1,S2,q);
    mpz_mul(V2,t,V2);
    mpz_mod(V2,V2,q);
}

int main() {
    initRand();
    mpz_t q, a, x, y, k, S1, S2, V1, V2, m;
    mpz_inits(q, a, x, y, k, S1, S2, V1, V2, m, NULL);
    init(q, a, 256);
    genRand(x, 256);
    
    
    // Geneate Public Key
    mpz_powm(y,a,x,q);
    
    // Generate Random number k
    genPrime(k,256);
    genRand(m,156);
    
    printf("Signing Message........\n");
    
    Sign(S1 ,S2, a, k, q, x, m);
    
    printf("Verifing Sign .......\n");
    Verify(a,m,q,y,S1,S2,V1,V2);
    
    gmp_printf("\nV1 : %Zd\nV2 : %Zd\n\n",V1,V2);
    
    if(mpz_cmp(V1,V2)==0)
    printf("\t\tV1 == V2 . Hence the signature is verified\n\n");
    else printf("V1 != V2 so the signature is not verfied\n\n");
    return 0;
}