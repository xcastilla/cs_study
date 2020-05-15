CC      = gcc
CFLAGS  = -Wall -Wextra -g -O0 -fPIC -fPIC -Iinclude
LDFLAGS = -shared
RM      = rm -f
.PHONY: all clean

TARGET  = malloc.so
SOURCES = src/malloc.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)
clean:
	$(RM) *.o *.so

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

$(SOURCES:.c=.d):%.d:%.c
	$(CC) $(CFLAGS)  -MM $< >$@

include $(SOURCES:.c=.d)
