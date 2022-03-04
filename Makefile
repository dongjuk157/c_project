CC = gcc
# CC = c:/sysgcc/raspberry/bin/arm-linux-gnueabihf-gcc.exe

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
LIBARY_DIR = $(HOME)/lib

SRCS = $(SRC_DIR)/main.c  $(SRC_DIR)/utils.c  $(SRC_DIR)/info.c
SRCS += $(SRC_DIR)/join.c

OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
TARGET = main
LIBS = -lui -ldatastucture 

CFLAGS = -c -g -Wall
CFLAGS += -I $(INCLUDE_DIR)
# CFLAGS += -D TEST

	

$(TARGET) : $(OBJS)
	cd lib; make
	$(CC) -o $@ $(OBJS) -L$(LIBARY_DIR) $(LIBS)

$(OBJ_DIR)/%.o: src/%.c
	-mkdir obj
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	cd lib; make clean
	rm $(TARGET) $(OBJS)
	rm -r obj
