#

all: add-entropy

add-entropy:
	$(CC) $(CFLAGS) -o add-entropy add-entropy.c

install:
	install add-entropy $(DESTDIR)/local/entropy/libexec

