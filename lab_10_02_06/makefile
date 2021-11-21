CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -pedantic -Iinc

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=out/%.o)

.PHONY: clean

app.exe: $(OBJS)
	@$(CC) -o $@ $^

$(OBJS): out/%.o: src/%.c
	@mkdir -p $(dir $@) && $(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf out app.exe
