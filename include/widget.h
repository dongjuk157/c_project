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

#define WIDGET_LABEL_NOT_CREATED -1003
#define WIDGET_SUB_WIDGET_NOT_CREATED -1002
#define WIDGET_TEXT_NOT_EXIST -1001
#define WIDGET_NOT_VALID_INPUT -1000
#define WIDGET_EOK 0

#define MAIN 0
#define SUB 1
#define MSGBOX 2

typedef struct Widget{
    int height;
    int width;
    int posx,posy;
    int type;
    LPARRAY label;
    LPARRAY subWidget;
}Widget;

Widget* createWidget();
int printWidget(Widget* widget);
int renderWidget(Widget* widget);
int addLabel(Widget *widget, Label *label);
int labelAdd(Widget* widget, int posy, int posx, const char* text, int color);
int addWidget(Widget *widget, Widget *subWidget);
int setWidgetPos(Widget *widget, int posy, int posx);
int setWidgetSize(Widget *widget, int height, int width);
int setWidgetType(Widget *Widget, int type);
int printLabel(Widget* widget, const Label* label);
int clearWidget(Widget* widget);
int renderEmpty(Widget *widget);
int printSiglelineWidget(Widget* widget,  int posy, int posx, const char* text, int color);
#endif // __WIDGET_H__
