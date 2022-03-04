CC = gcc
#  CC = c:/sysgcc/raspberry/bin/arm-linux-gnueabihf-gcc.exe

SRC_DIR = src
OBJ_DIR = obj
DATASTRUCTURE_DIR = data_structure
UI_DIR = ui

INCLUDE_DIR = ../include
LIBARY_DIR = $(HOME)/lib

DATASTRUCTURE_SRCS = $(SRC_DIR)/$(DATASTRUCTURE_DIR)/hash.c  
DATASTRUCTURE_SRCS += $(SRC_DIR)/$(DATASTRUCTURE_DIR)/array.c 
DATASTRUCTURE_SRCS += $(SRC_DIR)/$(DATASTRUCTURE_DIR)/linkedlist.c


UI_SRCS = $(SRC_DIR)/$(UI_DIR)/enroll_ui.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/history_detail.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/history_ui.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/home_ui.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/info_ui.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/label.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/login_ui.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/manage_detail.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/manage_ui.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/messagebox.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/parkstatus_detail.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/parkstatus_ui.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/pay_ui.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/setting_ui.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/view.c
UI_SRCS += $(SRC_DIR)/$(UI_DIR)/widget.c
# UI_SRCS += $(SRC_DIR)/$(UI_DIR)/utils.c


DATASTRUCTURE_OBJS = $(DATASTRUCTURE_SRCS:src/data_structure%.c=$(OBJ_DIR)/data_structure/%.o)
UI_OBJS = $(UI_SRCS:$(SRC_DIR)/$(UI_DIR)%.c=$(OBJ_DIR)/$(UI_DIR)%.o)

TARGET_DATASTRUCTURE = libdatastucture.so
TARGET_UI = libui.so

CFLAGS = -I $(INCLUDE_DIR) -fPIC


all : make_file $(DATASTRUCTURE_OBJS) $(UI_OBJS)
	$(CC) -shared $(DATASTRUCTURE_OBJS) -o $(TARGET_DATASTRUCTURE)
	$(CC) -shared $(UI_OBJS) -o $(TARGET_UI)
	cp $(TARGET_DATASTRUCTURE) $(LIBARY_DIR)/$(TARGET_DATASTRUCTURE)
	cp $(TARGET_UI) $(LIBARY_DIR)/$(TARGET_UI)

$(OBJ_DIR)/$(DATASTRUCTURE_DIR)/%.o: src/$(DATASTRUCTURE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 
	
$(OBJ_DIR)/$(UI_DIR)/%.o: $(SRC_DIR)/$(UI_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

make_file :
	# -mkdir ~/lib
	-mkdir obj
	-mkdir obj/data_structure
	-mkdir obj/ui

clean:
	rm $(TARGET_DATASTRUCTURE) $(DATASTRUCTURE_OBJS)
	rm $(TARGET_UI) $(UI_OBJS)
	rm /usr/lib/$(TARGET_UI)
	rm /usr/lib/$(TARGET_DATASTRUCTURE)
	rm -r obj
	
