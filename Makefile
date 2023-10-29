CC     = gcc
C_FILE = $(wildcard *.c)
TARGET = $(patsubst %.c,%,$(C_FILE))
CFLAGS = -O3 -Wall -Werror -pedantic-errors
OS     = windows

ifeq ($(OS), windows)
	RM = del
else
	RM = rm -f
endif

all:
	$(CC) $(CFLAGS) $(C_FILE) -o $(TARGET)
clean:
	$(RM) $(TARGET) $(TARGET).exe
