#ifndef MANAGE_UI_H
#define MANAGE_UI_H

#include "widget.h"
#include "info.h"
#define OK             0
#define FILE_ERROR     -1

#define IN_CAR 'i'
#define OUT_CAR 'o'

#define MANAGE_EOK 0

#define ERR_MANAGE_INVALID_INPUT -2
#define ERR_MANAGE_FLOOR_NOT_EXIST -3
#define ERR_MANAGE_TOO_MUCH_CAR -4
#define ERR_MANAGE_SAME_CAR_IN_PAKR -5
#define ERR_MANAGE_CAR_NOT_EXIST -6
#define ERR_MANAGE_USER_NOT_EXIST -7


typedef Widget MANAGE_UI;

MANAGE_UI* createManageUI();

int renderManageUI(MANAGE_UI *manage, void *data);
int getValuesUI(MANAGE_UI* manage, char io, CAR_INFO **car_info);
int searchUserUI(MANAGE_UI* manage,  char *car_number, USER_INFO **user_data, char io);
int saveUserUI(MANAGE_UI* manage, char *car_number, USER_INFO **user_data);
int save();
int save_log(char io, CAR_INFO *car_info);
int update_current(char io, CAR_INFO *car_info, LinkedList *current_park, LinkedList *current_car);
int update_history(char io, CAR_INFO *car_info, USER_INFO *user_data);
int manageErrHandler(Widget* widget, int errorCode);
#endif // MANAGE_UI_H
