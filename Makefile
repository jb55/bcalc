
BIN=bcalc
DEPS=$(wildcard deps/*/*.c) $(GEN)
PREFIX ?= /usr/local

DEPS = $(wildcard deps/*/*.c)
OBJS = $(DEPS:.c=.o) parser.tab.o lex.yy.o
GEN=parser.tab.c parser.tab.h lex.yy.c $(OBJS)


all: $(BIN)

parser.tab.c parser.tab.h:	parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

install: $(BIN)
	mkdir -p $(PREFIX)/bin
	cp $(BIN) $(PREFIX)/bin

$(BIN): $(OBJS)
	$(CC) -o $@ num.c $(OBJS)

clean:
	rm -f $(GEN)