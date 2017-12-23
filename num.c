
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
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

void
error_any() {
  fprintf(stderr, "error: --price argument required when using arbitrary units\n");
  exit(1);
}

static int64_t
num_to_msat(struct num *num) {
  double anyval = 1.0;

  if (num->type == TYPE_FLOAT) {
    double val = num->floatval;
    switch (num->unit) {
    case UNIT_OTHER:
      if (g_other.unit == UNIT_NONE) error_any();
      return (int64_t)val * (g_other.type == TYPE_FLOAT ? g_other.floatval
                                                      : (double)g_other.intval);
    case UNIT_MSATOSHI:
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
    case UNIT_NONE:
      assert(!"got UNIT_NONE in num_to_msat");
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
  case UNIT_OTHER:
    if (g_other.unit != UNIT_OTHER) error_any();
    anyval = g_other.type == TYPE_FLOAT?
      g_other.floatval : (double)g_other.intval;
  case UNIT_BTC:
    return (val/anyval) * BTC;
  case UNIT_NONE:
    assert(!"got UNIT_NONE in num_to_msat");
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

int64_t
unit_msat_multiple(enum unit format) {
  switch (format) {
  case UNIT_MSATOSHI: return MSATOSHI;
  case UNIT_SATOSHI:  return SATOSHI;
  case UNIT_FINNEY:   return FINNEY;
  case UNIT_BITS:     return BITS;
  case UNIT_MBTC:     return MBTC;
  case UNIT_OTHER:
    if (g_other.unit != UNIT_OTHER) error_any();
    return BTC / (g_other.type == TYPE_FLOAT
      ? g_other.floatval
      : g_other.intval);
  case UNIT_BTC:      return BTC;
  case UNIT_NONE:     assert(!"got UNIT_NONE in num_to_msat");
  }
}

void
num_mul(struct num *dst, struct num *a, struct num *b) {
  assert(b->unit == UNIT_NONE);
  dst->type = TYPE_INT;
  dst->unit = UNIT_MSATOSHI;
  int64_t num = num_to_msat(a);
  switch (b->type) {
  case TYPE_FLOAT:
    dst->intval = (int64_t)(num * b->floatval);
    double d = (double)num * b->floatval;
    // FIXME: floating point sucks
    if (d <= 1.000000000000001L && 0.99999999999999L <= d) dst->intval = 1LL;
    break;
  case TYPE_INT:
    dst->intval = num * b->intval;
    break;
  }
}

void
num_div(struct num *dst, struct num *a, struct num *b) {
  assert(b->unit == UNIT_NONE);
  dst->type = TYPE_INT;
  dst->unit = UNIT_MSATOSHI;
  dst->intval = num_to_msat(a) / (b->type == TYPE_FLOAT? b->floatval
                                                       : b->intval);
}

void
num_init_float(struct num *num, double d, enum unit unit) {
  num_init(num);
  num->floatval = d;
  num->type = TYPE_FLOAT;
  num->unit = unit;
  if (unit != UNIT_NONE) num_assign(num, num);
}

void
num_init_int(struct num *num, int64_t val, enum unit unit) {
  num_init(num);
  num->intval = val;
  num->type = TYPE_INT;
  num->unit = unit;
  if (unit != UNIT_NONE) num_assign(num, num);
}

void
num_assign(struct num *dst, struct num *a) {
  struct num num;
  num.type = TYPE_INT;
  num.unit = UNIT_MSATOSHI;
  num.intval = num_to_msat(a);
  *dst = num;
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
num_print(struct num *num, enum unit format, int print_unit) {
  static char buffer[255];
  int64_t msat_multiple = unit_msat_multiple(format);


  double d = num->type == TYPE_FLOAT? num->floatval : (double)num->intval;
  d /= (double)msat_multiple;
  sprintf (buffer, "%.11f", d);
  trim_zeros(buffer, 12);
  printf("%s", buffer);

  if (print_unit)
    printf(" %s", unit_name(format));
  printf("\n");
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
  case UNIT_OTHER:    return g_other_name;
  case UNIT_NONE:     assert(!"got UNIT_NONE in num_to_msat");
  default:
    assert(!"missing unit");
  }
}
