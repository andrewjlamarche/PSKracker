prefix = /usr/local
bindir = $(prefix)/bin

PROGi = pskracker att xfinity
PROGa = pskracker
PROGb = att
SRCS =  pskracker.c att.c xfinity.c
OBJS = $(SRCS:.c=.o)

CFLAGS += -Wno-unused

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
	$(CC) $(CFLAGS) $(INC) $(PIC) -c -o $@ $<

$(PROGi): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

.PHONY: all clean install
