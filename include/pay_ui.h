#ifndef PAY_UI_H
#define PAY_UI_H
#include "widget.h"
#include "info.h"
#define OK             0
#define FILE_ERROR     -1

typedef Widget PAY_UI;

PAY_UI* createPayUI();
int renderPayUI(PAY_UI *pay, void *data);
int payParkingFee();
int calcFee(char *carNumber);
int buyTicket();
int checkRecentTicket(USER_INFO *foundInfo);
int extendTicket(USER_INFO *foundInfo);
int newTicket(USER_INFO *foundInfo);
int saveUser(char *carNumber, USER_INFO **foundInfo);

#endif // __PAY_UI_H__
