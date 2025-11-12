CC = gcc
CFLAGS = -Wall -g -std=c99
TARGET = batalha_naval
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, %.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: src/%.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f *.o $(TARGET)