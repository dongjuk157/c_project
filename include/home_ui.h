#if !defined(__HOME_H__)
#define __HOME_H__

#include "widget.h"

typedef Widget HOME_UI;

HOME_UI* createHomeUI(); 

int renderHomeUI(HOME_UI* home);

#endif // __HOME_H__
