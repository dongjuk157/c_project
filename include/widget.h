#if !defined(__WIDGET_H__)
#define __WIDGET_H__
#include "array.h"
#include "utils.h"
#include "label.h"

typedef struct Widget{
    int height;
    int width;
    int posx,posy;
    LPARRAY label;
}Widget;

Widget* createWidget();
void printWidget(Widget* widget);
void render(Widget* widget);
bool addLabel(Widget *widget, Label *label);
void setWidgetPos(Widget *widget, int posy, int posx);
void setWidgetSize(Widget *widget, int height, int width);


#endif // __WIDGET_H__
