CCFLAGS ?= -std=c99 -O3

TARGET = pskracker
SOURCE = $(TARGET).c
PREFIX ?= $(DESTDIR)/usr
BINDIR = $(PREFIX)/bin

all:
	$(CC) $(CFLAGS) $(CCFLAGS) $(CPPFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)

debug:
	$(CC) $(CLFAGS) $(CCFLAGS) $(CPPFLAGS) -DDEBUG -o $(TARGET) $(SOURCE) $(LDFLAGS)

install:
	rm -f $(BINDIR)/$(TARGET)
	install -d $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)

uninstall:
	rm -f $(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET)
