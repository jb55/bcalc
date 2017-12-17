
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>
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
      return (int64_t)(val * SATOSHI);
    case UNIT_FINNEY:
      return (int64_t)(val * FINNEY);
    case UNIT_BITS:
      return (int64_t)(val * BITS);
    case UNIT_MBTC:
      return (int64_t)(val * MBTC);
    case UNIT_BTC:
      return (int64_t)(val * BTC);
    }
  }

  int64_t val = num->intval;
  switch (num->unit) {
  case UNIT_MSATOSHI:
    return val;
  case UNIT_SATOSHI:
    return val * SATOSHI;
  case UNIT_FINNEY:
    return val * FINNEY;
  case UNIT_BITS:
    return val * BITS;
  case UNIT_MBTC:
    return val * MBTC;
  case UNIT_BTC:
    return val * BTC;
  }
}

#define num_op (op)

void
num_add(struct num *dst, struct num *a, struct num *b) {
  dst->type = TYPE_INT;
  dst->unit = UNIT_MSATOSHI;
  dst->intval = num_to_msat(a) + num_to_msat(b);
}


void
num_sub(struct num *dst, struct num *a, struct num *b) {
  dst->type = TYPE_INT;
  dst->unit = UNIT_MSATOSHI;
  dst->intval = num_to_msat(a) - num_to_msat(b);
}

void
num_mul(struct num *dst, struct num *a, struct num *b) {
  dst->type = TYPE_INT;
  dst->unit = UNIT_MSATOSHI;
  dst->intval = num_to_msat(a) * num_to_msat(b);
}

void
num_div(struct num *dst, struct num *a, struct num *b) {
  dst->type = TYPE_INT;
  dst->unit = UNIT_MSATOSHI;
  dst->intval = num_to_msat(a) / num_to_msat(b);
}

void
num_assign(struct num *dst, struct num *a) {
  struct num num;
  num.type = TYPE_INT;
  num.unit = UNIT_MSATOSHI;
  num.intval = num_to_msat(a);
  *dst = num;
}

int64_t
unit_msat_multiple(enum unit format) {
  switch (format) {
  case UNIT_MSATOSHI: return MSATOSHI;
  case UNIT_SATOSHI:  return SATOSHI;
  case UNIT_FINNEY:   return FINNEY;
  case UNIT_BITS:     return BITS;
  case UNIT_MBTC:     return MBTC;
  case UNIT_BTC:      return BTC;
  }
}


static void
trim_zeros (char *s, int n)
{
  char *p;
  int count;

  p = strchr (s,'.');         // Find decimal point, if any.
  if (p != NULL) {
    count = n;              // Adjust for more or less decimals.
    while (count >= 0) {    // Maximum decimals allowed.
      count--;
      if (*p == '\0')    // If there's less than desired.
        break;
      p++;               // Next character.
    }

    *p-- = '\0';            // Truncate string.
    while (*p == '0')       // Remove trailing zeros.
      *p-- = '\0';

    if (*p == '.') {        // If all decimals were zeros, remove ".".
      *p = '\0';
    }
  }
}

void
num_print(struct num *num, enum unit format) {
  static char buffer[255];
  int64_t msat_multiple = unit_msat_multiple(format);

  if (format) {
  }

  double d = num->type == TYPE_FLOAT? num->floatval : (double)num->intval;
  d /= (double)msat_multiple;
  sprintf (buffer, "%.11f", d);
  trim_zeros(buffer, 12);
  printf("%s", buffer);
}



char *
unit_name(enum unit unit) {
  switch (unit) {
  case UNIT_MSATOSHI: return "msat";
  case UNIT_SATOSHI:  return "sat";
  case UNIT_FINNEY:   return "finney";
  case UNIT_BITS:     return "bits";
  case UNIT_MBTC:     return "mBTC";
  case UNIT_BTC:      return "BTC";
  }
}
