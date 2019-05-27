
BIN=bcalc
DEPS=$(wildcard deps/*/*.c) $(GEN)
PREFIX ?= /usr/local

CFLAGS = -O0 -g -std=c99
SRC  = num.c
DEPS = $(wildcard deps/*/*.c) $(SRC)
OBJS = $(DEPS:.c=.o) parser.tab.o lex.yy.o
GEN  = parser.tab.c parser.tab.h lex.yy.c $(OBJS)


all: $(BIN)

parser.tab.c parser.tab.h:	parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

install: $(BIN) bcalc.1
	mkdir -p $(PREFIX)/bin
	mkdir -p $(PREFIX)/share/man/man1
	gzip < bcalc.1 > $(PREFIX)/share/man/man1/bcalc.1.gz
	cp $(BIN) $(PREFIX)/bin

check: $(BIN) fake
	@sh -c "cd test && ./run"

TAGS: fake
	etags -o - *.c > $@

$(BIN): $(OBJS) bcalc.c num.h
	$(CC) $(CFLAGS) -Ideps -o $@ bcalc.c $(OBJS)

clean: fake
	rm -f $(GEN)


.PHONY: fake
