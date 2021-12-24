
CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -O2 -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion \
-Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align \
-fsanitize=address -fsanitize=undefined -lm
CDEBUGFLAGS = -std=c99 -g -Wall -Wextra -Og -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion \
-Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -lm
OBJDIR = bin

all: $(OBJDIR)/searchlist
$(OBJDIR)/searchlist: elem.c searchlist.c | $(OBJDIR)
	$(CC) $(CFLAGS) elem.c searchlist.c -o $(OBJDIR)/searchlist

d: $(OBJDIR)/searchlist.d
$(OBJDIR)/searchlist.d: elem.c searchlist.c | $(OBJDIR)
	$(CC) $(CDEBUGFLAGS) elem.c searchlist.c -o $(OBJDIR)/searchlist.d

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean
clean:
	rm -rf bin/ input_file gen correctAnswer a a.out brute code myAnswer d
