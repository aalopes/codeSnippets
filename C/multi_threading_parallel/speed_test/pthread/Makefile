# General makefile
# Alexandre Lopes

CC      = gcc
OBJ     = $(patsubst %.c, %.o, $(wildcard *.c))
TARGET  = main
INC_DIR =
LIB_DIR =
LDFLAGS = -pthread -lm

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS)  -I$(INC_DIR) -L$(LIB_DIR) -c $< -o $@ $(LDFLAGS)

clean:
	rm -rf $(TARGET) $(OBJ)
