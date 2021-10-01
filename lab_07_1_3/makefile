CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wredundant-decls -Wsign-conversion -Iinc
LDFLAGS := -lm
BASE_SRCS := $(shell find src -iname "*.c" ! -name "main.c")
BASE_OBJS := $(BASE_SRCS:src/%.c=out/%.o)
MAIN_SRCS := src/main.c
MAIN_OBJS := $(MAIN_SRCS:src/%.c=out/%.o)
UNIT_SRCS := $(wildcard unit_tests/*)
UNIT_OBJS := $(UNIT_SRCS:unit_tests/%.c=out/%.o)

.PHONY: unit func clean sort_analysis

release: CFLAGS += -DNDEBUG -O3
release: app.exe

debug: CFLAGS += -DDEBUG --coverage -O0
debug: LDFLAGS += --coverage
debug: app.exe

unit: LDFLAGS += -lcheck -lpthread -lsubunit -lrt -lm
unit: unit_tests.exe
	./unit_tests.exe

func: app.exe
	./test.sh

sort_analysis: CFLAGS += -DSORT_TIME
sort_analysis: app.exe
	:> out.txt && ./sort_time.sh

qsort_analysis: CFLAGS += -DSORT_TIME -DQSORT
qsort_analysis: app.exe
	:> qout.txt && ./sort_time.sh

app.exe: $(BASE_OBJS) $(MAIN_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

unit_tests.exe: $(BASE_OBJS) $(UNIT_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BASE_OBJS) $(MAIN_OBJS): out/%.o : src/%.c
	mkdir -p $(dir $@) && $(CC) $(CFLAGS) -o $@ -c $^

$(UNIT_OBJS): out/%.o : unit_tests/%.c
	mkdir -p $(dir $@) && $(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm -rf *.exe out
