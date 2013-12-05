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

.PHONY: example
example: example_static example_shared

example_static: example.c static
	$(CC) $(CFLAGS) -L. -ltester $< -o $@ -static

example_shared: example.c shared
	$(CC) $(CFLAGS) -L. -ltester $< -o $@


.PHONY: clean
clean:
	$(RM) $(FILES) example_static example_shared

.PHONY: install
install: all
	$(INSTALL) -m 644 libtester.a  "$(PREFIX)/lib/"
	$(INSTALL) -m 644 libtester.so "$(PREFIX)/lib/"
	$(INSTALL) -m 644 tester.h     "$(PREFIX)/include/"
