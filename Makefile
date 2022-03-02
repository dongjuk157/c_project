CC = gcc
#  CC = c:/sysgcc/raspberry/bin/arm-linux-gnueabihf-gcc.exe

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/array.c $(SRC_DIR)/widget.c $(SRC_DIR)/utils.c $(SRC_DIR)/label.c 
SRCS += $(SRC_DIR)/home_ui.c $(SRC_DIR)/info_ui.c $(SRC_DIR)/history_ui.c
SRCS += $(SRC_DIR)/pay_ui.c $(SRC_DIR)/view.c $(SRC_DIR)/parkstatus_ui.c
SRCS += $(SRC_DIR)/history_detail.c
SRCS += $(SRC_DIR)/linkedlist.c
SRCS += $(SRC_DIR)/hash.c
SRCS += $(SRC_DIR)/info.c
SRCS += $(SRC_DIR)/manage.c
SRCS += $(SRC_DIR)/manage_ui.c
SRCS += $(SRC_DIR)/manage_detail.c
SRCS += $(SRC_DIR)/parkstatus_detail.c

OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
TARGET = main

CFLAGS = -c -g -Wall
CFLAGS += -I $(INCLUDE_DIR)
CFLAGS += -D TEST

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm $(TARGET) $(OBJS)
