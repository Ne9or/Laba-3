CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

TARGET = app
SRC = src/main.c src/deque.c src/sort.c src/record.c src/parse.c src/utils.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ && mv app ./bin && mv $^ ./build

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
