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
int primality_check(llu, int*, int);

// resieve(lo, size, primes, nb_primes) returns an array starting
// at lo such that out[i] is equal to 0 if lo + i is a multiple
// of an element of primes, 1 otherwise. up is not included in
// the array.
char* resieve(lli, lli, int*, int);

// A list of int values
typedef struct int_list {
  int il_head;
  struct int_list* il_tail;
} int_list;

int_list* il_push(int, int_list*);
int_list* il_pop(int*, int_list*);
int il_empty(int_list*);
void il_print(int_list*);

// get_factors(n) returns an array a of size n+1 such that a[i]
// is the list of all prime factors of i.
int_list** get_prime_factors(int);

// Check that a number is practical using the characterization
// from http://en.wikipedia.org/wiki/Practical_number
int is_practical(llu, int*, int);

// GCD (using Euclide algorithm)
int gcd_int(int, int);
llu gcd_llu(llu, llu);

// Euler totient function
int phi_int(int);
int phi_with_primes(int, int*, int);

int sort_llu(const void *, const void *);
#endif
