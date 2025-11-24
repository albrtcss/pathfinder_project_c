CC=gcc
CFLAGS=-Iinclude -std=c11 -Wall -Wextra
SRCS=src/grid.c src/run_example.c
TARGET=build/run_example

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:
	rm -rf build
