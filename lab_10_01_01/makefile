CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -pedantic -Iinc -O3 -Wno-incompatible-pointer-types
UNIT_FLAGS := -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

SRCS := $(filter-out src/main.c, $(wildcard src/*.c))
UNIT_SRCS := $(wildcard unit/*.c)
OBJS := $(SRCS:src/%.c=out/%.o)
UNIT_OBJS := $(UNIT_SRCS:unit/%.c=out/%.o)

.PHONY: clean

app.exe: $(OBJS) out/main.o
	@$(CC) -o $@ $^

unit: unit.exe
	@./unit.exe

unit.exe: $(OBJS) $(UNIT_OBJS)
	@$(CC) -o $@ $^ -lcheck

$(OBJS) out/main.o: out/%.o: src/%.c
	@mkdir -p $(dir $@) && $(CC) $(CFLAGS) -c -o $@ $^


$(UNIT_OBJS): CFLAGS+= $(UNIT_FLAGS)
$(UNIT_OBJS): out/%.o: unit/%.c
	@mkdir -p $(dir $@) && $(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf out unit.exe app.exe
