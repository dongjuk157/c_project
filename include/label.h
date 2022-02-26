#if !defined(__LABEL_H__)
#define __LABEL_H__
#include "utils.h"
typedef struct Label{
    int posx, posy;
    char *text;
}Label;

Label* createLabel();

bool setLabelPos(Label *label, int posy, int posx);
bool setLabelText(Label *label, const char* text);
bool printLabel(const Label* label);

#endif // __LABEL_H__
