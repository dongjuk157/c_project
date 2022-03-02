#ifndef MANAGE_UI_H
#define MANAGE_UI_H

#include "widget.h"
#include "info.h"
#define OK             0
#define FILE_ERROR     -1

typedef Widget MANAGE_UI;

MANAGE_UI* createManageUI();

int renderManageUI(MANAGE_UI *manage);
int getValuesUI(MANAGE_UI* manage, char io, CAR_INFO **car_info);
int searchUserUI(MANAGE_UI* manage,  char *car_number, USER_INFO **user_data);
int saveUserUI(MANAGE_UI* manage, char *car_number, USER_INFO **user_data);
int save();

#endif // MANAGE_UI_H
