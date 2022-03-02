#if !defined(__LABEL_H__)
#define __LABEL_H__
#include "utils.h"

#define LABEL_EOK 0
#define LABEL_NOT_VALID_INPUT -1000


typedef struct Label{
    int posx, posy;
    int color;
    char* text;
}Label;

Label* createLabel();
int setLabel(Label* label, int posy, int posx, const char* text, int color);
int setLabelPos(Label *label, int posy, int posx);
int setLabelText(Label *label, const char* text);
int setLabelBackgrounColor(Label *label, int color);


#endif // __LABEL_H__
