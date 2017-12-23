
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "commander/commander.h"
#include "num.h"

extern int yylex();
extern int yyparse();
extern enum unit g_output_format;
extern int g_print_unit;
struct num g_other;
char *g_other_name = "other";

void yyerror(const char* s);

struct settings {
  enum unit format;
  int print_unit;
};

#define format_setting(name, unit) static void name(command_t *self) { \
  ((struct settings*)self->data)->format = unit; \
}

static void no_print_unit(command_t *self) { \
  ((struct settings*)self->data)->print_unit = 0; \
}

format_setting(btc, UNIT_BTC)
format_setting(mbtc, UNIT_MBTC)
format_setting(bits, UNIT_BITS)
format_setting(finney, UNIT_FINNEY)
format_setting(sat, UNIT_SATOSHI)
format_setting(msat, UNIT_MSATOSHI)
format_setting(optother, UNIT_OTHER)

static void optusd(command_t *self) {
  struct settings *set = (struct settings*)self->data;
  set->format = UNIT_OTHER;
  g_other_name = "USD";
}

static void
setprice(command_t *cmd) {
  const char *p = cmd->arg;
  char *endptr;
  g_other.unit = UNIT_OTHER;
  g_other.type = TYPE_INT;
  g_other.intval = strtoull(p, &endptr, 10);

  // float?
  if (endptr) {
    if (*endptr == '.') {
      g_other.floatval = atof(p);
      g_other.type = TYPE_FLOAT;
      if (g_other.floatval == 0) {
        fprintf(stderr, "error: invalid --price value '%s'", p);
        exit(1);
      }
    }
  }
}

char *
join(char *strs[], int len, char *sep) {
  char *buf, *p;
  size_t alloc = 0;

  for(int i = 0; i < len; ++i)
    alloc += strlen(strs[i]);

  // 5 for some wiggle room
  alloc += len * strlen(sep) + 5;
  p = buf = (char*)malloc(alloc);

  for(int i = 0; i < len; ++i) {
    strcpy(p, strs[i]);
    p += strlen(strs[i]);
    if (i != len-1) {
      strcpy(p, sep);
      p += strlen(sep);
    }
  }

  return buf;
}

int main(int argc, char *argv[argc]) {
  command_t cmd;
  char *buffer, *p;
  int yybuffer;
  struct settings settings = { .print_unit = 1, .format = UNIT_SATOSHI };
  cmd.data = (void*)&settings;
  g_other.unit = UNIT_NONE;

  command_init(&cmd, argv[0], "0.0.1");

  command_option(&cmd, "-B", "--btc",       "output BTC", btc);
  command_option(&cmd, "-M", "--mbtc",      "output mBTC", mbtc);
  command_option(&cmd, "-b", "--bits",      "output bits", bits);
  command_option(&cmd, "-f", "--finney",    "output finneys", finney);
  command_option(&cmd, "-s", "--sat",       "output satoshis (default)", sat);
  command_option(&cmd, "-m", "--msat",      "output millisatoshis", msat);
  command_option(&cmd, "-P", "--price <arg>", "set price for arbitrary unit per BTC", setprice);
  command_option(&cmd, "-o", "--other",   "output arbitrary unit, set by --price", optother);
  command_option(&cmd, "-u", "--usd",     "output arbitrary usd units", optusd);
  command_option(&cmd, "-n", "--no-unit", "dont output the selected unit at the end",
                 no_print_unit);

  command_parse(&cmd, argc, argv);

  g_output_format = settings.format;
  g_print_unit = settings.print_unit;

  if (cmd.argc) {
    buffer = join(cmd.argv, cmd.argc, " ");
    p = &buffer[strlen(buffer)];
    *p++ = '\n';
    *p++ = '\0';
    yybuffer = yy_scan_string(buffer);
    yyparse();
    yy_delete_buffer(yybuffer);
    free(buffer);
  }
  else {
    do {
      yyparse();
    } while(!feof(stdin));
  }

  command_free(&cmd);
  return 0;
}

void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
  exit(1);
}
