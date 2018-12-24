xfer: xfer.c
	gcc -o xfer xfer.c

install: xfer
	cp xfer ~/bin/xfer
