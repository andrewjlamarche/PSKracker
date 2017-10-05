PREFIX ?= $(DESTDIR)/usr/local
BINDIR = $(PREFIX)/bin

PROG = pskracker
SRCS = pskracker.c att.c xfinity.c
OBJS = $(SRCS:.c=.o)

CFLAGS += -Wno-unused

all: $(PROG)

install:
	install -D -m 755 $(PROG) $(BINDIR)/$(PROG)

clean:
	$(RM) $(PROG)
	$(RM) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(PIC) -c -o $@ $<

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

.PHONY: all clean install
