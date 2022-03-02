#ifndef VIEW_H
#define VIEW_H

#include "widget.h"
#include "info.h"

int renderFeeView();
int printFeeDetailView(char *carNumber, int fee, int hasTicket);

int renderTicketView();
int renderExtendTicketDetailView(USER_INFO *foundInfo);
int renderNewTicketDetailView(USER_INFO *foundInfo);

int printSingleLineView(char *currentMenu, char *defaultText);

#endif