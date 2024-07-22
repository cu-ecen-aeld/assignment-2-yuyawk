ifeq ($(CROSS_COMPILE), aarch64-none-linux-gnu-)
CC = aarch64-none-linux-gnu-gcc
else
CC = gcc
endif

CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = writer
SRC = finder-app/writer.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
