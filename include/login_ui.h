#if !defined(__LOGIN_H__)       
#define __LOGIN_H__

#include "widget.h"

typedef Widget LOGIN_UI;

LOGIN_UI* createLoginUI();

int renderLoginUI(LOGIN_UI* login, void *id);
#endif // __LOGIN_H__
