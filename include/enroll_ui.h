#if !defined(__ENROLL_UI_H__)
#define __ENROLL_UI_H__

#include "widget.h"
typedef Widget ENROLL_UI;

ENROLL_UI* createEnrollUI();
int renderEnrollUI(ENROLL_UI* enroll, void *id);

#endif // __ENROLL_UI_H__
