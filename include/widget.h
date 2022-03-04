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
#define LOGIN 6
#define ENROLLUSER 7
#define SETTING 8

#define WIDGET_LABEL_NOT_CREATED -1003
#define WIDGET_SUB_WIDGET_NOT_CREATED -1002
#define WIDGET_TEXT_NOT_EXIST -1001
#define WIDGET_NOT_VALID_INPUT -1000
#define WIDGET_EOK 0

#define NONE -1
#define MAIN 0
#define SUB 1
#define MSGBOX 2
#define BUTTON 3l

#define OK_BTN 44
#define CANCLE_BTN 41
#define YES_BTN 44
#define NO_BTN 41

typedef struct Widget{
    int height; //위젯의 높이
    int width; //
    int posx,posy;
    int type; //위젯의 타입 0 : MAIN, 1 : SUB, 2 : MSGBOX 3 : BUTTON 
    LPARRAY label;  //라벨이 들어갈 동적배열
    LPARRAY subWidget; //서브 위젯이 들어갈 동적배열
}Widget;

typedef Widget MAINWIDGET;
typedef Widget Button;
typedef Widget SUBWIDGET;
typedef Widget MsgBox;


Widget* createWidget();
MAINWIDGET* createMainWidget(int posy, int posx, int height, int width);
SUBWIDGET* createSubWidget(int posy, int posx, int height, int width);
MsgBox* createMsgBox(int posy, int posx);
Button* createButton(int posy,int posx, int width, char *text, int color);

int printWidget(Widget* widget);
int printMainWidget(MAINWIDGET* widget);
int printSubWidget(SUBWIDGET *widget);
int printMessageBox(MsgBox* widget);
int printButton(Button *widget);


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
