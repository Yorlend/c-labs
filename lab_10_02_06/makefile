CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -pedantic -Iinc

SRCS := $(filter-out src/main.c, $(wildcard src/*.c))
UNIT_SRCS := $(wildcard unit/*.c)
OBJS := $(SRCS:src/%.c=out/%.o)
UNIT_OBJS := $(UNIT_SRCS:unit/%.c=out/%.o)

.PHONY: clean unit

all: app.exe

run: app.exe
	./app.exe

unit: unit_tests.exe
	@./unit_tests.exe

app.exe: $(OBJS) out/main.o
	@$(CC) -o $@ $^

unit_tests.exe: $(OBJS) $(UNIT_OBJS)
	@$(CC) -o $@ $^ -lcheck -lpthread -lrt -lm

$(OBJS) out/main.o: out/%.o: src/%.c
	@mkdir -p $(dir $@) && $(CC) $(CFLAGS) -c -o $@ $^

$(UNIT_OBJS): out/%.o: unit/%.c
	@mkdir -p $(dir $@) && $(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf out app.exe unit_tests.exe
