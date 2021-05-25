CC := gcc
CFLAGS := -std=c99 --coverage -Wall -Werror -Wpedantic -Wextra -Wvla -Wredundant-decls -Wsign-conversion
FILES := $(shell find . -iname "*.c")
OBJECTS := $(FILES:.c=.o)

.PHONY: clean

all: CFLAGS += -D DETAILED_OUTPUT
all: a.exe
	./a.exe input.bin
	

test: test.exe
	bash ./test.sh

a.exe: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

test.exe: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(OBJECTS): %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm -rf a.exe *.o *.gcda *.gcno temp.txt gcov *.txt .vscode
