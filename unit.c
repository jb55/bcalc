
#include <assert.h>
#include "num.h"

void
num_init(struct num *num) {
  num->type = TYPE_INT;
  num->unit = UNIT_BTC;
  num->intval = 0LL;
}

static int64_t
num_to_msat(struct num *num) {
  if (num->type == TYPE_FLOAT) {
    double val = num->floatval;
    switch (num->unit) {
    case UNIT_MSATOSHI:
      assert("fractional millisatoshis are not yet supported");
      return (int64_t)val;
    case UNIT_SATOSHI:
      return (int64_t)(val * 1000);
    case UNIT_FINNEY:
      return (int64_t)(val * 10000);
    case UNIT_BITS:
      return (int64_t)(val * 100000);
    case UNIT_MBTC:
      return (int64_t)(val * 100000000);
    case UNIT_BTC:
      return (int64_t)(val * 100000000000);
    }
  }

  int64_t val = num->intval;
  switch (num->unit) {
  case UNIT_MSATOSHI:
    return val;
  case UNIT_SATOSHI:
    return val * 1000;
  case UNIT_FINNEY:
    return val * 10000;
  case UNIT_BITS:
    return val * 100000;
  case UNIT_MBTC:
    return val * 100000000;
  case UNIT_BTC:
    return val * 100000000000;
  }
}


int64_t
num_add(struct num *a, struct num *b) {
  return (num_to_msat(a) + num_to_msat(b));
}
