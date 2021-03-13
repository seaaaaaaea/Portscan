CC = gcc
CFLAGS = -Wall -o


portscan: portscan.c
	$(CC) -Wall -o bin/portscan portscan.c

clean:
	rm -f bin/portscan

install:
	cp bin/portscan /usr/local/sbin/portscan

