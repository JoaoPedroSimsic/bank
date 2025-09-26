CC = gcc

CFLAGS = -Wall -g

TARGET = bank

SOURCES = main.c client.c

OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-rm -f $(TARGET) $(OBJECTS)

.PHONY: all
all: $(TARGET)
