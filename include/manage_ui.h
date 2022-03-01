#ifndef MANAGE_UI_H
#define MANAGE_UI_H
#include "widget.h"
#include OK             0
#include FILE_ERROR     -1
typedef Widget MANAGE_UI;

MANAGE_UI* createManageUI();
int renderManageUI(MANAGE_UI *manage);
int getValuesUI();
int save()

#endif // MANAGE_UI_H
