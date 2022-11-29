#include <gmp.h>
#include <stdio.h>

// (a * x_final) + (b * y_final) = g
void extended_euclid(mpz_t a, mpz_t b, mpz_t g, mpz_t x_final, mpz_t y_final) {
	mpz_t prev_x, x, cur_x, prev_y, y, cur_y, q, r, new_x, new_y, temp;
	mpz_inits(prev_x, x, cur_x, prev_y, y, cur_y, q, r, new_x, new_y, temp, NULL);
	
	
	mpz_set_ui(prev_x, 1); mpz_set_ui(prev_y, 0);
	mpz_set_ui(x, 0); mpz_set_ui(y, 1);
	
	while(mpz_cmp_ui(b, 0) != 0) {
		mpz_fdiv_qr(q, r, a, b);
		
		mpz_set(new_x, prev_x);
		mpz_mul(temp, q, x);
		mpz_sub(new_x, new_x, temp); //  new_x = prev_x - q*x
		
		mpz_set(new_y, prev_y);
		mpz_mul(temp, q, y);
		mpz_sub(new_y, new_y, temp); //  new_y = prev_y - q*y
		
		mpz_set(temp, b);
		mpz_mod(b, a, b);
		mpz_set(a, temp); // a = b, b = a mod b
		
		mpz_set(prev_x, x); mpz_set(x, new_x);
		mpz_set(prev_y, y); mpz_set(y, new_y);		
	}
	
	mpz_set(g, a);
	mpz_set(x_final, prev_x);
	mpz_set(y_final, prev_y);
}

void find_inverse(mpz_t a, mpz_t m, mpz_t inv) {
	mpz_t g, x_final, y_final, acopy, mcopy;
	mpz_inits(g, x_final, y_final, acopy, mcopy, NULL);
	
	mpz_set(acopy, a); mpz_set(mcopy, m);
	extended_euclid(acopy, mcopy, g, x_final, y_final);
	
	if(mpz_cmp_ui(g, 1) != 0) {
		printf("Inverse does not exist since a and m are not coprimes\n\n");
		mpz_set_si(inv, -1);
	}else {
		if(mpz_cmp_si(x_final, 0) < 0) {
			mpz_fdiv_r(x_final, x_final, m);
			mpz_add(x_final, x_final, m);
			mpz_fdiv_r(x_final, x_final, m);
		}
		mpz_set(inv, x_final);
	}
	
}
int main() {
	mpz_t a, m, inv, g, x_final, y_final;
	mpz_inits(a, m, inv, g, x_final, y_final, NULL);
	
	printf("Enter a and m to find inverse x such that a*x ~ 1 mod m\n");
	gmp_scanf("%Zd %Zd", a, m);
	
	find_inverse(a, m, inv);
	
	if(mpz_cmp_si(inv, -1) != 0) {
		gmp_printf("inverse is x = %Zd\n\n", inv);
	}
	
	return 0;
}
