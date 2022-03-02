#if !defined(__SETTING_UI_H__)
#define __SETTING_UI_H__

#include "widget.h"

typedef Widget SETTING_UI;
typedef Widget SETTING_DETAIL_UI;

SETTING_UI* createSettingUI();
SETTING_DETAIL_UI* createSettingDetailUI();

int renderSettingUI(SETTING_UI* setting);
int renderSettingDetailUI(SETTING_DETAIL_UI* detail);

#endif // __SETTING_UI_H__
