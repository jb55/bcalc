
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

#endif /* UNIT_H */
