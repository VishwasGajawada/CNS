/* code for elgamal encryption using gmp library*/

/* Vishwas Gajawada, 197188 */

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

    gmp_printf("p = %Zd\n\ng = %Zd\n\n", p, alpha);
}

void genKeys(mpz_t alice_private, mpz_t  alice_public, mpz_t p, mpz_t g) { 
    mpz_t p_1;
    mpz_inits(p_1, NULL);
    mpz_sub_ui(p_1, p, 1);
    mpz_urandomm(alice_private, state, p_1);
    mpz_powm(alice_public, g, alice_private, p);
}

void genRandom(mpz_t x, mpz_t p) {
    mpz_t p_1;
    mpz_inits(p_1, NULL);
    mpz_sub_ui(p_1, p, 1);
    mpz_urandomm(x, state, p_1);
}

void encryption(mpz_t M, mpz_t k, mpz_t c1, mpz_t c2, mpz_t p, mpz_t g, mpz_t apub) {
    printf("Encryption :: \n");
    genRandom(M, p);
    genRandom(k, p);
    
    mpz_powm(c1, g, k, p);
    mpz_powm(c2, apub, k, p);
    mpz_mul(c2, c2, M);
    mpz_mod(c2, c2, p);
    
    gmp_printf("M = %Zd\n\nc1 = %Zd\n\nc2 = %Zd\n\n", M, c1, c2);
}

void decryption(mpz_t c1, mpz_t c2, mpz_t pri, mpz_t pub, mpz_t p, mpz_t dec) {
    printf("Decryption :: \n");
    mpz_t c1_pow_x, c1_pow_x_inv, message;
    mpz_inits(c1_pow_x, c1_pow_x_inv, message, NULL);
    
    mpz_powm(c1_pow_x, c1, pri, p);
    // gmp_printf("c1_pow_x = %Zd\n", c1_pow_x);
    mpz_invert(c1_pow_x_inv, c1_pow_x, p);
    
    // gmp_printf("c1_pow_x_inv = %Zd\n", c1_pow_x_inv);
    mpz_mul(message, c2, c1_pow_x_inv);
    mpz_mod(message, message, p);
    
    gmp_printf("Decrypted message M is \n%Zd\n", message);
    mpz_set(dec, message);
}

int main() {
    initRand();
    mpz_t p, g, alice_private, alice_public, ka, kb;
    mpz_inits(p, g, alice_private, alice_public, ka, kb, NULL);
    
    /*** ALICE **/
    init(p, g);
    genKeys(alice_private, alice_public, p, g);
    printf("sending Alice's public key (y, p, g) to Bob\n\n");
    
    /** BOB **/
    printf("Bob recieves Alice's public key (y, p, g)\n\n");
    mpz_t M, k, c1, c2;
    mpz_inits(M, k, c1, c2, NULL);
    encryption(M, k, c1, c2, p, g, alice_public);
    
    printf("Bob sends (c1, c2) to Alice\n"
            "Alice recieves (c1, c2) from Bob\n\n");
            
    /** ALICE **/
    mpz_t dec;
    mpz_init(dec);
    decryption(c1, c2, alice_private, alice_public, p, dec);
    
    if(mpz_cmp(M, dec) == 0) {
        printf("The message is succesfully decrypted\n");
    }
    
    
}
