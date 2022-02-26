CC = gcc

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/array.c $(SRC_DIR)/widget.c $(SRC_DIR)/utils.c $(SRC_DIR)/label.c
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
TARGET = main

CFLAGS = -c -g -Wall
CFLAGS += -I $(INCLUDE_DIR)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET) $(OBJS)
