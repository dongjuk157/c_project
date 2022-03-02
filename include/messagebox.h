#if !defined(__MESSAGE_BOX_H__)
#define __MESSAGE_BOX_H__

#define ID_OK 0x1234
#define ID_CANCLE 0x1122

#include "widget.h"

typedef Widget MessageBox;

int messageBox(Widget* mainWindow, int posy, int posx, char* message);

#endif // __MESSAGE_BOX_H__
