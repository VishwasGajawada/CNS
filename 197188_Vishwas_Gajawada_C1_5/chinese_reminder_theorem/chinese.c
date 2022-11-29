#include <stdio.h>
#include <gmp.h>
#include <time.h>

void print_mod_relations(mpz_t a[], mpz_t m[], int n) {
    for(int i=0;i<n;i++) gmp_printf("x ~ %Zd mod %Zd\n", a[i], m[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of congruent relations\n");
    scanf("%d", &n);

    mpz_t a[n], m[n], M[n], x[n], ans, bigM, temp;
    for(int i=0;i<n;i++) {
        mpz_inits(a[i], m[i], M[i], x[i], NULL);
    }
    mpz_inits(bigM, ans, temp, NULL);
    mpz_set_ui(bigM, 1);

    for(int i=0;i<n;i++) {
        printf("Enter a%d and m%d in x ~ a%d mod m%d\n", i+1, i+1, i+1, i+1);
        gmp_scanf("%Zd %Zd", a[i], m[i]);
        mpz_mul(bigM, bigM, m[i]);
    }

    print_mod_relations(a, m, n);
    gmp_printf("M = %Zd\n", bigM);

    for(int i=0; i<n ;i++) {
        mpz_cdiv_q(M[i], bigM, m[i]);
        gmp_printf("M%d = %Zd\n", i+1, M[i]);
    }

    // find multiplicative inverses of M[i] wrt to m[i], i.e M[i]*x[i] ~ 1 mod m[i]
    for(int i=0;i<n;i++) {
        mpz_invert(x[i], M[i], m[i]);
        gmp_printf("x%d = %Zd\t\t %Zd * %Zd ~ 1 mod %Zd\n", i+1, x[i], M[i], x[i], m[i]);

    }

    mpz_set_ui(ans, 0);
    for(int i=0;i<n;i++) {
        mpz_set_ui(temp, 1);
        mpz_mul(temp, temp, a[i]);
        mpz_mul(temp, temp, x[i]);
        mpz_mul(temp, temp, M[i]);

        mpz_add(ans, ans, temp);
    }
    mpz_fdiv_r(ans, ans, bigM); // x = ( +  + ) mod M

    gmp_printf("x = %Zd\n", ans);

    return 0;
}