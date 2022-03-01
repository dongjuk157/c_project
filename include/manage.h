#ifndef MANAGE_H
#define MANAGE_H

#include "info.h"

#define OK            0
#define FILE_ERROR    -1
#define FORMAT_ERROR  -2

#define SIMPLE_LOG_FILE_PATH    "../data/history.log"
#define USER_DATA_FILE_PATH     "../data/user.dat"
#define HISTORY_DATA_FILE_PATH     "../data/history.dat"


int manage_in_out(void);
int get_values(char io, CAR_INFO **car_info);
int save_log(char io, CAR_INFO *car_info);
// int save_log(char io, char* car_number);
int search_user(char *car_number, USER_INFO **user_data);
int save_user(char *car_number, USER_INFO **user_data);
int update_current(char io, CAR_INFO *car_info, USER_INFO *user_data); 
int update_history(char io, CAR_INFO *car_info, USER_INFO *user_data);

#endif