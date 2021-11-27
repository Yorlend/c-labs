CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wredundant-decls -Wsign-conversion -Iinc
LDFLAGS := -lm
SRCS := $(shell find src -iname "*.c")
OBJS := $(SRCS:src/%.c=out/%.o)

.PHONY: clean

all: app.exe

app.exe: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJS): out/%.o: src/%.c
	mkdir -p $(dir $@) && $(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm -rf *.exe out
