CFLAGS=-O2 -Wall -Wextra
PREFIX=/usr/local
MKDIR=mkdir -p
INSTALL=install -D
FILES=libtester.a libtester.so

.PHONY: all
all: static shared

.PHONY: static
static: libtester.a
libtester.a: tester.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: shared
shared: libtester.so
libtester.so: tester.c
	$(CC) $(CFLAGS) -fPIC -shared $< -o $@

example: example.c static
	$(CC) $(CFLAGS) -L. -ltester $< -o $@ -static


.PHONY: clean
clean:
	$(RM) $(FILES) example

.PHONY: install
install: all
	$(INSTALL) -m 644 libtester.a  "$(PREFIX)/lib/"
	$(INSTALL) -m 644 libtester.so "$(PREFIX)/lib/"
	$(INSTALL) -m 644 tester.h     "$(PREFIX)/include/"
