prefix = /usr/local
bindir = $(prefix)/bin

PROG = pskracker att
SRCS =  pskracker.c att.c
OBJS = $(SRCS:.c=.o)

CFLAGS += -Wall -Wno-unused -D_GNU_SOURCE -std=c99

-include config.mak

all: $(PROG)

install: $(PROG)
	install -d $(DESTDIR)/$(bindir)
	install -D -m 755 $(PROG) $(DESTDIR)/$(bindir)/$(PROG)

clean:
	rm -f $(PROG)
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(PIC) -c -o $@ $<

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

.PHONY: all clean install