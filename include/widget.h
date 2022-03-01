#if !defined(__WIDGET_H__)
#define __WIDGET_H__
#include "array.h"
#include "utils.h"
#include "label.h"

#define DEFAULT_POSX 1
#define DEFAULT_POSY 1

#define EXIT -1
#define HOME 0
#define IOMANAGE 1
#define PAY 2
#define PARKSTATUS 3
#define CARINFO 4
#define PARKHISTORY 5
#define INPUTERROR -1000

#define MAIN 0
#define SUB 1

typedef struct Widget{
    int height;
    int width;
    int posx,posy;
    int type;
    LPARRAY label;
    LPARRAY subWidget;
}Widget;

Widget* createWidget();
void printWidget(Widget* widget);
int renderWidget(Widget* widget);
bool addLabel(Widget *widget, Label *label);
void setWidgetPos(Widget *widget, int posy, int posx);
void setWidgetSize(Widget *widget, int height, int width);
void setWidgetType(Widget *Widget, int type);
bool printLabel(Widget* widget, const Label* label);
int clearWidget(Widget* widget);
int renderEmpty(Widget *widget);
#endif // __WIDGET_H__
