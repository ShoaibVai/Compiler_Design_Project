CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic
SRC=src/main.c src/lexer.c src/parser.c
TARGET=simple_compiler

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(TARGET).exe
