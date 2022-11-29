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

int main() {
	mpz_t a, b, g, x_final, y_final;
	mpz_inits(a, b, g, x_final, y_final, NULL);
	
	printf("Enter a and b to find their bezout coefficients\n");
	gmp_scanf("%Zd %Zd", a, b);
	
	extended_euclid(a, b, g, x_final, y_final);
	
	gmp_printf("\nGCD is %Zd\n", a);
	gmp_printf("Bezout coefficients x = %Zd, and y = %Zd\n\n", x_final, y_final);
	
	return 0;
}
