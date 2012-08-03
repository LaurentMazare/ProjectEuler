#ifndef __EULER_MATH_H__
#define __EULER_MATH_H__
#include<stdio.h>
#include<stdlib.h>

typedef long long int lli;
typedef unsigned long long int llu;

// Prime sieve: get_primes(max_p, &nb_primes)
// return an array with nb_primes elements containing
// all the primes between 2 and max_p (inclusive).
int* get_primes(int, int*);

// primality_check(x, primes, nb_primes)
// x has to be lower than the square of the largest prime
int primality_check(int, int*, int);

// GCD (using Euclide algorithm)
int gcd_int(int, int);
llu gcd_llu(llu, llu);

#endif
