
CDEBUGFLAGS= -g -Wall -Wextra -O0 -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion

all: 1

1:
	gcc $(CDEBUGFLAGS) pderive.c -o pderive && ./pderive

2:
	gcc $(CDEBUGFLAGS) fibinc.c -o fibinc && ./fibinc

3:
	gcc $(CDEBUGFLAGS) rangeset.c -o rangeset && ./rangeset

4:
	gcc $(CDEBUGFLAGS) commonletters.c -o commonletters && ./commonletters

5:
	gcc $(CDEBUGFLAGS) maxksum.c -o maxksum && ./maxksum
