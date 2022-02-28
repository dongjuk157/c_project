#if !defined(__INFO_UI_H__)
#define __INFO_UI_H__
#define EOK 1
#define NFD 0
#define IDE -1
#define FOE -2

#include "widget.h"

typedef Widget INFO_UI;

INFO_UI* createInfoUI();
int renderInfoUI(INFO_UI* info);

#endif // __INFO_UI_H__
