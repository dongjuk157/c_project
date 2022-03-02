#ifndef VIEW_H
#define VIEW_H

#include "widget.h"
#include "info.h"
#define OK             0
#define FILE_ERROR     -1

int renderFeeView();
int printFeeDetailView(char *carNumber, int fee, int hasTicket);

int renderTicketView();
int renderExtendTicketDetailView(USER_INFO *foundInfo);
int renderNewTicketDetailView(USER_INFO *foundInfo);

int printSingleLineView(char *currentMenu, char *defaultText);
int printTicketView();
int printSaveUserInfoView();
#endif
