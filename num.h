
#ifndef UNIT_H
#define UNIT_H

#include <stdint.h>

#define MSATOSHI 100000000000LL
#define SATOSHI  100000000LL
#define FINNEY   10000000LL
#define BITS     1000000LL
#define MBTC     1000LL

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
void num_print(struct num *num);

#endif /* UNIT_H */
