CC=gcc
CFLAGS=-Wall -std=c99 -g -O2 -I./include
LDFLAGS=
OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
TESTDIR=./test
INCDIR=./include

OBJS=$(OBJDIR)/gift_generate.o $(OBJDIR)/gift_utils.o \
	$(OBJDIR)/gift_key_schedule.o \
	$(OBJDIR)/gift_core.o \
	$(OBJDIR)/main.o

TARGET=$(BINDIR)/a.out

.PHONY: all clean dir rebuild

all: dir $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(OBJS:.o=.d)

clean:
	rm -f $(OBJS) $(TARGET) $(OBJDIR)/*.d

dir:
	@mkdir -p $(OBJDIR) $(BINDIR)

rebuild: clean all

run:
	(cd bin && ./a.out)

leak: 
	(cd bin && valgrind --leak-check=full --show-leak-kinds=all ./a.out)

cycle:
	(cd bin && ./a.out > cycle.txt)
	(cd bin && mv cycle.txt ../view/)
	(cd view && python3 compare_cycle.py)