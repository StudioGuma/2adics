CC     = gcc
C_FILE = $(wildcard *.c)
TARGET = $(patsubst %.c,%,$(C_FILE))
CFLAGS = -Os -Wall -Werror -Wextra -pedantic-errors

all:
	$(CC) $(CFLAGS) $(C_FILE) -o $(TARGET) -lm

clean:
#	del /q $(TARGET).exe
	rm -f $(TARGET)
