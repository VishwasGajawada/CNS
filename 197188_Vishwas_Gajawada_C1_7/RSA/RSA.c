#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <stdbool.h>


gmp_randstate_t state;
unsigned long seed;

void initRand() {

    seed = time(NULL);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}

void genPrime(mpz_t x, int bits) {

    mpz_t rand_num;
    mpz_inits(x, rand_num, NULL);

    mpz_rrandomb(rand_num, state, bits);
    mpz_nextprime(x, rand_num);
}

void genPhi(mpz_t p, mpz_t q, mpz_t phi) {
    mpz_t p_1, q_1;
    mpz_inits(p_1, q_1, NULL);
    mpz_sub_ui(p_1, p, 1);
    mpz_sub_ui(q_1, q, 1);
    mpz_mul(phi, p_1, q_1);
}

void genPublicKey(mpz_t phi, mpz_t e) {
    // e : encryption key/ public key
    mpz_t phi_1, _gcd;
    mpz_inits(phi_1, _gcd, NULL);
    mpz_sub_ui(phi_1, phi, 1);
    while(true)
	{
		mpz_urandomm(e,state,phi_1);
		mpz_gcd(_gcd,e,phi);
		if(mpz_cmp_ui(_gcd,1)==0) {
			break;
		}
	}
}

void genPrivateKey(mpz_t phi, mpz_t pubkey, mpz_t privkey) {
    mpz_invert(privkey, pubkey, phi);
}

void encrypt(mpz_t plain, mpz_t ciph, mpz_t pubKey, mpz_t mod) {
    mpz_powm(ciph, plain, pubKey, mod);
}

void decrypt(mpz_t ciph, mpz_t dec, mpz_t privKey, mpz_t mod) {
    mpz_powm(dec, ciph, privKey, mod);
}

int main() {
    initRand();

    mpz_t p, q, n;
    genPrime(p, 1024);
    genPrime(q, 1024);
    mpz_init(n);
    mpz_mul(n, p, q);

    gmp_printf("p = %Zd\n\nq = %Zd\n\n", p, q);

    mpz_t phi, public_key, private_key, plain_text, cipher_text, decrypted_text;
    mpz_inits(phi, public_key, private_key,  plain_text, cipher_text, decrypted_text, NULL);

    genPhi(p, q, phi);
    genPublicKey(phi, public_key);
    genPrivateKey(phi, public_key, private_key);

    gmp_printf("e = %Zd\n\nd = %Zd\n\n", public_key, private_key);

    mpz_set_ui(plain_text, 19062002);
    encrypt(plain_text, cipher_text, public_key, n);
    decrypt(cipher_text, decrypted_text, private_key, n);

    gmp_printf("Plain text: %Zd\n\n"
                "Cipher text: %Zd\n\n"
                "Decrypted text : %Zd\n\n", plain_text, cipher_text, decrypted_text);
    return 0;
}