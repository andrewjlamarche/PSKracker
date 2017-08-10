prefix = /usr/local
bindir = $(prefix)/bin

PROGi = pskracker att
PROGa = pskracker
PROGb = att
SRCS =  pskracker.c att.c
OBJS = $(SRCS:.c=.o)

CFLAGS += -Wall -Wno-unused -D_GNU_SOURCE -std=c99

-include config.mak

all: $(PROGa) $(PROGb)

install: $(PROGa) $(PROGb)
	install -d $(DESTDIR)/$(bindir)
	install -D -m 755 $(PROGa) $(DESTDIR)/$(bindir)/$(PROGa)
	install -D -m 755 $(PROGb) $(DESTDIR)/$(bindir)/$(PROGb)
clean:
	rm -f $(PROGi)
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(PIC) -c -o $@ $<

$(PROGi): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

.PHONY: all clean install
