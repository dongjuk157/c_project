#ifndef PAY_UI_H
#define PAY_UI_H
#include "widget.h"

typedef Widget PAY_UI;

PAY_UI* createPayUI();
int renderPayUI(PAY_UI *pay);
int payParkingFee();
int calcFee(char *carNumber);
int buyTicket();

#endif // __PAY_UI_H__
