
#ifndef UNIT_H
#define UNIT_H

#include <stdint.h>

// multiples of msat
#define MSATOSHI 1LL
#define SATOSHI  1000LL
#define FINNEY   10000LL
#define BITS     100000LL
#define MBTC     100000000LL
#define BTC      100000000000LL

enum unit {
  UNIT_BTC,
  UNIT_MBTC,
  UNIT_BITS,
  UNIT_FINNEY,
  UNIT_SATOSHI,
  UNIT_MSATOSHI,
};

enum num_type {
  TYPE_INT,
  TYPE_FLOAT
};

struct num
{
  enum num_type type;
  enum unit unit;
  union {
    int64_t intval;
    double floatval;
  };
};



void num_add(struct num *dst, struct num *a, struct num *b);
void num_sub(struct num *dst, struct num *a, struct num *b);
void num_mul(struct num *dst, struct num *a, struct num *b);
void num_div(struct num *dst, struct num *a, struct num *b);
void num_assign(struct num *dst, struct num *a);
void num_init(struct num *num);
void num_print(struct num *num, enum unit unit, int print_unit);
char *unit_name(enum unit unit);

#endif /* UNIT_H */
