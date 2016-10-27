#include <stdlib.h>
#include <stdio.h>

#include <glib.h>

#include "mygmp.h"

static int gcd(int a, int b) {
	int t;
	while (b != 0) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

void mpq_canonicalize (mpq_t op)
{
	if (op->p == 0) {
		op->q = 1;
	} else {
		int g = abs(gcd(op->p, op->q));
		op->p /= g;
		op->q /= g;
		if (op->q < 0) {
			op->p = -op->p;
			op->q = -op->q;
		}
	}
}

char *mpq_get_str(char *unused, int base, const mpq_t op)
{
	if (unused || base != 10) {
		g_warning("not implemented");
	}
	int size = 0;
	char *p = NULL;

	size = snprintf(p, 0, "%d/%d", op->p, op->q);
	if (size < 0)
		return NULL;

	size++;
	p = malloc(size);
	size = snprintf(p, size, "%d/%d", op->p, op->q);
	if (size < 0) {
		free(p);
		return NULL;
	}
	return p;
}

void mpq_swap (mpq_t rop1, mpq_t rop2)
{
	int t;
	t = rop1->p;
	rop1->p = rop2->p;
	rop2->p = t;
	t = rop1->q;
	rop1->q = rop2->q;
	rop2->q = t;
}

void mpq_sub (mpq_t difference, const mpq_t minuend, const mpq_t subtrahend)
{
	if (minuend->q == subtrahend->q) {
		difference->p = minuend->p - subtrahend->p;
		difference->q = minuend->q;
	} else {
		difference->p = minuend->p * subtrahend->q - subtrahend->p * minuend->q;
		difference->q = minuend->q * subtrahend->q;
	}
	mpq_canonicalize(difference);
}

int mpq_cmp (const mpq_t op1, const mpq_t op2)
{
	mpq_t t;
	mpq_sub(t, op1, op2);
	return t->p;
}

int mpq_cmp_si (const mpq_t op1, long int num2, unsigned long int den2)
{
	mpq_t t;
	t->p = num2;
	t->q = den2;
	return mpq_cmp(op1, t);
}

void mpq_set_si (mpq_t rop, signed long int op1, unsigned long int op2)
{
	rop->p = op1;
	rop->q = op2;
}

void mpq_set (mpq_t rop, const mpq_t op)
{
	rop->p = op->p;
	rop->q = op->q;
}

void mpq_div (mpq_t quotient, const mpq_t dividend, const mpq_t divisor)
{
	quotient->p = dividend->p * divisor->q;
	quotient->q = dividend->q * divisor->p;
	mpq_canonicalize(quotient);
}

void mpq_add (mpq_t sum, const mpq_t addend1, const mpq_t addend2)
{
	if (addend1->q == addend2->q) {
		sum->p = addend1->p + addend2->p;
		sum->q = addend1->q;
	} else {
		sum->p = addend1->p * addend2->q + addend2->p * addend1->q;
		sum->q = addend1->q * addend2->q;
	}
	mpq_canonicalize(sum);
}

void mpq_mul (mpq_t product, const mpq_t multiplier, const mpq_t multiplicand)
{
	product->p = multiplier->p * multiplicand->p;
	product->q = multiplier->q * multiplicand->q;
	mpq_canonicalize(product);
}
