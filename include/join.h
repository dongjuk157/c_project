#ifndef __JOIN_H__
#define __JOIN_H__

#include "info.h"

int loginCheck(char *id, char *password);
int join(char *id, char *password);
int createNewFiles(char *id); 
int createParkingLot(char *id, LinkedList* list); // before execute this, run createNewFiles first


#endif