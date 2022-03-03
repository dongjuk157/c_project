#if !defined(__SETTING_UI_H__)
#define __SETTING_UI_H__

#include "widget.h"
#include "info.h"

typedef Widget SETTING_UI;
typedef Widget SETTING_DETAIL_UI;

SETTING_UI* createSettingUI();
SETTING_DETAIL_UI* createSettingDetailUI();

int renderSettingUI(SETTING_UI* setting, void *id);
int renderSettingDetailUI(SETTING_DETAIL_UI* detail, PARK **park);

#endif // __SETTING_UI_H__
