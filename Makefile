
BIN=bcalc
DEPS=$(wildcard deps/*/*.c) $(GEN)
PREFIX ?= /usr/local

CFLAGS = -O2 -std=c99
SRC  = num.c
DEPS = $(wildcard deps/*/*.c) $(SRC) parser.tab.c lex.yy.c
OBJS = $(DEPS:.c=.o)
GEN  = parser.tab.c parser.tab.h lex.yy.c $(OBJS) $(BIN)


all: $(BIN)

parser.tab.c parser.tab.h:	parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

install: $(BIN) bcalc.1
	mkdir -p $(PREFIX)/bin $(PREFIX)/share/man/man1
	gzip < bcalc.1 > $(PREFIX)/share/man/man1/bcalc.1.gz
	cp $(BIN) $(PREFIX)/bin

check: $(BIN) fake
	@sh -c "cd test && ./run"

TAGS: fake
	etags -o - *.c > $@

$(BIN): $(DEPS) bcalc.c
	$(CC) $(CFLAGS) -Ideps -o $@ $^

clean: fake
	rm -f $(GEN)


.PHONY: fake
