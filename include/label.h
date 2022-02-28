#if !defined(__LABEL_H__)
#define __LABEL_H__
#include "utils.h"

typedef struct Label{
    int posx, posy;
    char text[100];
}Label;

Label* createLabel();
void labelCreate(Label* label);

bool setLabelPos(Label *label, int posy, int posx);
bool setLabelText(Label *label, const char* text);


#endif // __LABEL_H__
