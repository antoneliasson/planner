#pragma once

typedef struct {
	int p;
	int q;
} ratnum_t;

typedef ratnum_t mpq_t[1];

void mpq_canonicalize (mpq_t op);
char *mpq_get_str(char *unused, int base, const mpq_t op);
void mpq_swap (mpq_t rop1, mpq_t rop2);
void mpq_sub (mpq_t difference, const mpq_t minuend, const mpq_t subtrahend);
int mpq_cmp (const mpq_t op1, const mpq_t op2);
int mpq_cmp_si (const mpq_t op1, long int num2, unsigned long int den2);
void mpq_set_si (mpq_t rop, signed long int op1, unsigned long int op2);
void mpq_set (mpq_t rop, const mpq_t op);
void mpq_div (mpq_t quotient, const mpq_t dividend, const mpq_t divisor);
void mpq_add (mpq_t sum, const mpq_t addend1, const mpq_t addend2);
void mpq_mul (mpq_t product, const mpq_t multiplier, const mpq_t multiplicand);

static inline int mpq_equal (const mpq_t op1, const mpq_t op2)
{
	return !mpq_cmp(op1, op2);
}

static inline int mpq_is_zero (const mpq_t op)
{
	return !mpq_cmp_si(op, 0, 1);
}

double mpq_get_d (const mpq_t op);
