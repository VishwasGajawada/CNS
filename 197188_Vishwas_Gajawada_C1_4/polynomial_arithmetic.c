#include <stdio.h>

void print_poly(int co[], int n) {
	for(int i=n-1;i>=0;i--) {
		if(co[i]){
			printf("(x^%d) ", i);
		}
	}
}

int get_bit_rep(int co[], int n) {
	int res = 0;
	for(int i=n-1;i>=0;i--){
		res<<=1;
		res|=co[i];
	}
	return res;
}

void get_coef_rep(int bit_rep, int co[], int n) {
	for(int i=0;i<n;i++) {
		if((1<<i)&bit_rep) co[i] = 1;
		else co[i] = 0;
	}
}

void addition(int co1[], int co2[], int n) {
	int bit1 = get_bit_rep(co1, n);
	int bit2 = get_bit_rep(co2, n);
	
	int res = bit1^bit2; // bit1 xor bit2
	
	int res_arr[n];
	get_coef_rep(res, res_arr, n);
	
	printf("\n\naddition of polynomials is : ");
	print_poly(res_arr, n);
	printf("\n");
}

void subtraction(int co1[], int co2[], int n) {
	// since -1 mod 2  = 1, addition and subtraction results in same polynomial
	int bit1 = get_bit_rep(co1, n);
	int bit2 = get_bit_rep(co2, n);
	
	int res = bit1^bit2; // bit1 xor bit2
	
	int res_arr[n];
	get_coef_rep(res, res_arr, n);
	
	printf("\n\nsubtraction of polynomials is : ");
	print_poly(res_arr, n);
	printf("\n\n");
}

int irreducible_polynomial_bit(int n) {
	// x^n + x + 1
	int res = 3;
	if(n>1)res = (res | (1<<n));	
	return res;
}

void multiplication(int co1[], int co2[], int n) {
	int bit1 = get_bit_rep(co1, n);
	int bit2 = get_bit_rep(co2, n);
	
	printf("\nEnter coefficients(1/0) of m(x) (irreducible polynomial) from x^%d to x^0\n", n);
	int ir[n+1];
	for(int i=n;i>=0;i--) scanf("%d", &ir[i]);
	print_poly(ir, n+1);


	int irpt = get_bit_rep(ir, n+1);
	int xor_factor = irpt - (1<<n); // m(x) - x^n
	
	int xn_fx[n]; // x^n*f(x)
	xn_fx[0] = bit1;
	
	for(int i=1; i<n; i++) {
		int temp = xn_fx[i-1];
		temp <<= 1;
		// unset the nth bit if any
		if(temp&(1<<n)) {
			temp = temp & ((1<<n) - 1);
			temp = temp^xor_factor;
		}

		xn_fx[i] = temp;
	}
	
	int res = 0;
	for(int i=0;i<n;i++) if(co2[i]) res = res^xn_fx[i];
	
	int res_arr[n];
	get_coef_rep(res, res_arr, n);
	
	printf("\n\nmultiplication of polynomials is : ");
	print_poly(res_arr, n);
	printf("\n\n");
	
}

int main() {
	printf("Polynomial Arithmetic for polynomials defined over GF(2^n)\n\n");
	int n;
	printf("Enter degree n\n"); scanf("%d",&n);
	
	
	int co1[n], co2[n];
	printf("Enter coefficients(1/0) of first polynomial from x^%d to x^0\n", n-1);
	for(int i=n-1;i>=0;i--) scanf("%d", &co1[i]);
	print_poly(co1, n);

	printf("\nEnter coefficients(1/0) of second polynomial from x^%d to x^0\n", n-1);
	for(int i=n-1;i>=0;i--) scanf("%d", &co2[i]);
	print_poly(co2, n);
	
	addition(co1, co2, n);
	subtraction(co1, co2, n);
	multiplication(co1, co2, n);
	
	return 0;
}
