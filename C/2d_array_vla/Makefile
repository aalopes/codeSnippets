# General makefile
# Alexandre Lopes

CC      = gcc
OBJ     = $(pathsubst %.c, %.o, $(wildcard *.c))
TARGET  = test
INC_DIR =
LIB_DIR =

all: $(TARGET)

$(TARGET): $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -L$(LIB_DIR) $^ -o $@

clean:
	rm -rf $(TARGET)
