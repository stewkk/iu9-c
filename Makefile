
CC = gcc
CFLAGS = -std=c17 -g -Wall -Wextra -O2 -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion \
-Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align \
-fsanitize=address -fsanitize=undefined -lm
CDEBUGFLAGS = -std=c17 -g -Wall -Wextra -Og -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion \
-Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -lm
OBJDIR = bin

sources := $(wildcard *.c)
binaries := $(addprefix $(OBJDIR)/,$(basename $(sources)))
debug_binaries := $(addsuffix .d,$(binaries))

all: $(binaries)
$(binaries): | $(OBJDIR)
$(OBJDIR)/% : %.c
	$(CC) $(CFLAGS) $< -o $@

d: $(debug_binaries)
$(debug_binaries): | $(OBJDIR)
$(OBJDIR)/%.d : %.c
	$(CC) $(CDEBUGFLAGS) $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean
clean:
	rm -rf bin/ input_file gen correctAnswer a a.out brute code myAnswer d
