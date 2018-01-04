#
# $Id: Makefile 12 2011-08-05 11:20:42Z janj $
# $HeadURL: svn://svn.it.su.se/sua-entropy/trunk/Makefile $
#

all: add-entropy

add-entropy:
	$(CC) $(CFLAGS) -o add-entropy add-entropy.c

install:
	install add-entropy $(DESTDIR)/local/entropy/libexec

