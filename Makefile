CC = gcc
#  CC = c:/sysgcc/raspberry/bin/arm-linux-gnueabihf-gcc.exe

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
LIBARY_DIR = lib

SRCS = $(SRC_DIR)/main.c  $(SRC_DIR)/utils.c  $(SRC_DIR)/info.c
SRCS += $(SRC_DIR)/join.c


# SRCS += $(SRC_DIR)/hash.c  $(SRC_DIR)/array.c $(SRC_DIR)/linkedlist.c

# SRCS +=  $(SRC_DIR)/label.c $(SRC_DIR)/widget.c
# SRCS += $(SRC_DIR)/home_ui.c $(SRC_DIR)/info_ui.c $(SRC_DIR)/history_ui.c
# SRCS += $(SRC_DIR)/pay_ui.c $(SRC_DIR)/view.c $(SRC_DIR)/parkstatus_ui.c
# SRCS += $(SRC_DIR)/history_detail.c
# SRCS += $(SRC_DIR)/manage_ui.c
# SRCS += $(SRC_DIR)/manage_detail.c
# SRCS += $(SRC_DIR)/parkstatus_detail.c
# SRCS += $(SRC_DIR)/messagebox.c
# SRCS += $(SRC_DIR)/login_ui.c
# SRCS += $(SRC_DIR)/enroll_ui.c
# SRCS += $(SRC_DIR)/setting_ui.c



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
	
