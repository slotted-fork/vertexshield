CC ?= gcc
CFLAGS += -Wall -Wextra -g -fsanitize=undefined
CFLAGS += $(shell pkg-config --cflags raylib)
LDFLAGS += $(shell pkg-config --libs raylib)

EXE = vertexshield

.PHONY: all clean

all: $(EXE)

clean:
	rm -f $(EXE)
