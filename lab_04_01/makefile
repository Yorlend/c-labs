CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wredundant-decls -Wsign-conversion
FILES := $(shell find . -iname "*.c")
OBJECTS := $(FILES:.c=.o)

.PHONY: clean

all: test.exe
	./test.exe

test.exe: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(OBJECTS): %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm -rf test.exe *.o
