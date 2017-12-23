
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "commander/commander.h"
#include "num.h"

extern int yylex();
extern int yyparse();
extern enum unit g_output_format;
extern int g_print_unit;

void yyerror(const char* s);

struct settings {
  enum unit format;
  int print_unit;
};

#define format_setting(name, unit) static void name(command_t *self) { \
  ((struct settings*)self->data)->format = unit; \
}

static void print_unit(command_t *self) { \
  ((struct settings*)self->data)->print_unit = 1; \
}

format_setting(btc, UNIT_BTC)
format_setting(mbtc, UNIT_MBTC)
format_setting(bits, UNIT_BITS)
format_setting(finney, UNIT_FINNEY)
format_setting(sat, UNIT_SATOSHI)
format_setting(msat, UNIT_MSATOSHI)

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
  struct settings settings = { .print_unit = 0, .format = UNIT_SATOSHI };
  cmd.data = (void*)&settings;

  command_init(&cmd, argv[0], "0.0.1");

  command_option(&cmd, "-B", "--btc",       "output BTC", btc);
  command_option(&cmd, "-M", "--mbtc",      "output mBTC", mbtc);
  command_option(&cmd, "-b", "--bits",      "output bits", bits);
  command_option(&cmd, "-f", "--finney",    "output finneys", finney);
  command_option(&cmd, "-s", "--sat",       "output satoshis (default)", sat);
  command_option(&cmd, "-m", "--msat",      "output millisatoshis", msat);
  command_option(&cmd, "-p", "--print-unit", "output the selected unit at the end",
                 print_unit);

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
