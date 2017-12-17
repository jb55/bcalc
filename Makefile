
BIN=bcalc
GEN=parser.tab.c parser.tab.h lex.yy.c
PREFIX ?= /usr/local
SRCS=num.c

all: $(BIN)

parser.tab.c parser.tab.h:	parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

install: $(BIN)
	mkdir -p $(PREFIX)/bin
	cp $(BIN) $(PREFIX)/bin

$(BIN): $(GEN)
	$(CC) -o $@ $(SRCS) parser.tab.c lex.yy.c

clean:
	rm -f $(GEN)
