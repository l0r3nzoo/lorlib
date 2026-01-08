CC = gcc

CFLAGS = -g -O0 -Wall

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

SRCS = main.c stack.c vector.c dictionary.c queue.c observable_vector.c file.c directory.c

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = $(BUILD_DIR)/main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
