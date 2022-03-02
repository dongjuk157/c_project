#ifndef MANAGE_H
#define MANAGE_H

#include "info.h"
#include "hash.h"
#include "linkedlist.h"

#define OK            0
#define FILE_ERROR    -1
#define FORMAT_ERROR  -2

// #define CURRENT_DATA_FILE_PATH          "./data/Current.dat"
// #define SIMPLE_LOG_FILE_PATH    		"./data/history.log"
// #define USER_DATA_FILE_PATH     		"./data/User.dat"
// #define HISTORY_DATA_FILE_PATH     		"./data/History.dat"
// #define PARKINGLOT_SETTINGS_FILE_PATH   "./data/ParkingLot.dat"

int manage_in_out(LPHASH user_table, LinkedList *current_park, LinkedList *current_car);
int get_values(char io, CAR_INFO **car_info);
int save_log(char io, CAR_INFO *car_info);
int search_user(LPHASH user_table, char *car_number, USER_INFO **user_data);
int save_user(LPHASH user_table, char *car_number, USER_INFO **user_data);
int update_current(char io, CAR_INFO *car_info, LinkedList *current_park, LinkedList *current_car); 
int update_history(char io, CAR_INFO *car_info, USER_INFO *user_data);

#endif