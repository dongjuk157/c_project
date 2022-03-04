#ifndef __JOIN_H__
#define __JOIN_H__

#include "info.h"
#include "widget.h"

#define JOIN_EOK 0

#define ERR_JOIN_FILE_NOT_OPEN -200
#define ERR_JOIN_INVALID_PASSWORD -201
#define ERR_JOIN_INVALID_ID -202

#define ERR_JOIN_SAME_ID_EXIST -203



int loginCheck(char *id, char *password);
int join(char *id, char *password);
int createNewFiles(char *id); 
int createParkingLot(char *id, LinkedList* list); // before execute this, run createNewFiles first
int joinErrorHandler(Widget* widget, int errCode);

#endif