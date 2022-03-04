#include "widget.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

Widget* createWidget()
{
    Widget* widget = (Widget*)malloc(sizeof(Widget));
    setWidgetPos(widget,DEFAULT_POSY,DEFAULT_POSX);
    arrayCreate(&(widget->label));
    arrayCreate(&(widget->subWidget));

    return widget;
}

MAINWIDGET* createMainWidget(int posy, int posx, int height, int width){
    Widget* widget = createWidget();
    setWidgetSize(widget,height,width);
    setWidgetPos(widget,posy,posx);
    setWidgetType(widget, MAIN);
    return widget;
}
SUBWIDGET* createSubWidget(int posy, int posx, int height, int width){
    Widget* widget = createWidget();
    setWidgetSize(widget,height,width);
    setWidgetPos(widget,posy,posx);
    setWidgetType(widget, SUB);
    return widget;
}
MsgBox* createMsgBox(int posy, int posx){
    MsgBox* widget = createWidget();
    setWidgetSize(widget,10,40);
    setWidgetPos(widget,posy,posx);
    setWidgetType(widget, MSGBOX);
    return widget;
}
Button* createButton(int posy,int posx, int width, char *text, int color){
    Widget* widget = createWidget();
    setWidgetType(widget, BUTTON);
    setWidgetPos(widget,posy, posx);
    setWidgetSize(widget,3,width);
    labelAdd(widget,1,1,text,color);
    return widget;
}

int printMainWidget(MAINWIDGET *widget){
    //테두리 
    gotoxy(widget->posx,widget->posy);
    printf("┏"); for (int i = 1; i < widget->width-1; i++) printf("━"); printf("┓");

    for (int i = 1; i < widget->height-1; i++)
    {
        gotoxy(widget->posx, widget->posy + i);
        printf("┃");
        gotoxy(widget->posx + widget->width-1, widget->posy + i);
        printf("┃");
    }
    gotoxy(widget->posx, widget->posy + widget->height-1);
    printf("┗"); for (int i = 1; i <widget->width-1; i++) printf("━"); printf("┛");

    //상단 바
    gotoxy(widget->posx, widget->posy + 2);
    printf("┣"); for (int i = 0; i < widget->width-2; i++)printf("━");printf("┫");

    printf("\x1b[%dm",44); //색상 변경
    gotoxy(widget->posx + 1, widget->posy + 1);
    for (int i = 0; i < widget->width-8; i++) printf(" ");
    printf("━ ■ X ");
    printf("\x1b[0m"); //이전 색상 복구
    
    return WIDGET_EOK;
}

int printSubWidget(SUBWIDGET *widget){
    gotoxy(widget->posx,widget->posy); 
    printf("┌");for (int i = 1; i < widget->width-1; i++) printf("─"); printf("┐");
    for (int i = 1; i < widget->height-1; i++)
    {
        gotoxy(widget->posx, widget->posy + i);
        printf("│");
        gotoxy(widget->posx + widget->width-1, widget->posy + i);
        printf("│");
    }
    gotoxy(widget->posx, widget->posy + widget->height-1);
    printf("└"); for (int i = 1; i <widget->width-1; i++) printf("─");printf("┘");
    return WIDGET_EOK;
}

int printButton(Button *widget){
    gotoxy(widget->posx,widget->posy); 
    printf("┌");for (int i = 1; i < widget->width-1; i++) printf("─"); printf("┐");
    for (int i = 1; i < widget->height-1; i++)
    {
        gotoxy(widget->posx, widget->posy + i);
        printf("│");
        gotoxy(widget->posx + widget->width-1, widget->posy + i);
        printf("│");
    }
    gotoxy(widget->posx, widget->posy + widget->height-1);
    printf("└"); for (int i = 1; i <widget->width-1; i++) printf("─");printf("┘");
    return WIDGET_EOK;
}

int printMessageBox(MsgBox* widget){
     //테두리 
    gotoxy(widget->posx,widget->posy);
    printf("┏"); for (int i = 1; i < widget->width-1; i++) printf("━"); printf("┓");

    for (int i = 1; i < widget->height-1; i++)
    {
        gotoxy(widget->posx, widget->posy + i);
        printf("┃");
        gotoxy(widget->posx + widget->width-1, widget->posy + i);
        printf("┃");
    }
    gotoxy(widget->posx, widget->posy + widget->height-1);
    printf("┗"); for (int i = 1; i <widget->width-1; i++) printf("━"); printf("┛");

    //상단 바
    gotoxy(widget->posx, widget->posy + 2);
    printf("┣"); for (int i = 0; i < widget->width-2; i++)printf("━");printf("┫");

    printf("\x1b[%dm",44); //색상 변경
    gotoxy(widget->posx + 1, widget->posy + 1);
    for (int i = 0; i < widget->width-8; i++) printf(" ");
    printf("━ ■ X ");
    printf("\x1b[0m"); //이전 색상 복구
    return WIDGET_EOK;
}

int printWidget(Widget* widget)
{
    switch (widget->type)
    {
    case MAIN:
        printMainWidget(widget);
        break;
    case SUB:
        printSubWidget(widget);
        break;
    case MSGBOX:
        printMessageBox(widget);
        break;
    case BUTTON:
        printSubWidget(widget);
        break;
    default:
        break;
    }
    return WIDGET_EOK;
}

int renderWidget(Widget* widget)
{   
    if(widget->type == MAIN) system("clear");

    renderEmpty(widget);
    printWidget(widget);

    for (int i = 0; i < arraySize(widget->label); i++)
    {
        printLabel(widget,(Label *)(widget->label->lpData)[i]);
    }
    for (int i = 0; i < arraySize(widget->subWidget); i++)
    {
        renderWidget((Widget *)(widget->subWidget->lpData)[i]);
    }
    return WIDGET_EOK;
}

int addLabel(Widget *widget, Label *label)
{
    if(widget->label == NULL) return WIDGET_LABEL_NOT_CREATED;

    arrayAdd(widget->label, label);
    return WIDGET_EOK;
}

int labelAdd(Widget* widget, int posy, int posx, const char* text, int color){
    Label *newLabel = createLabel();
    setLabelPos(newLabel, posy, posx);
    setLabelText(newLabel, text);
    setLabelBackgrounColor(newLabel, color);
    addLabel(widget, newLabel);
    return WIDGET_EOK;
}

int addWidget(Widget *widget, Widget *subWidget){
    if(widget->subWidget == NULL) return WIDGET_SUB_WIDGET_NOT_CREATED;

    setWidgetPos(subWidget,widget->posy + subWidget->posy, widget->posx + subWidget->posx);
    arrayAdd(widget->subWidget, subWidget);
    return WIDGET_EOK;
}

int printLabel(Widget* widget, const Label* label){
    if(label->text == NULL) return WIDGET_TEXT_NOT_EXIST;

    gotoxy(widget->posx + label->posx, widget->posy + label->posy);
    if(label->color != 0){
        printf("\x1b[%dm",label->color);
    }
    printf("%s",label->text);    
    printf("\x1b[0m");

    return WIDGET_EOK;
}

int setWidgetPos(Widget *widget, int posy, int posx)
{
    if(posx<=0 || posy<=0) return WIDGET_NOT_VALID_INPUT;
    widget -> posy = posy;
    widget -> posx = posx;
    return WIDGET_EOK;
}

int setWidgetSize(Widget *widget, int height, int width)
{
    if(height < 0 || width < 0) return WIDGET_NOT_VALID_INPUT;
    widget->height = height;
    widget->width = width;
    return WIDGET_EOK;
}

int setWidgetType(Widget *Widget, int type){
    if(type != MAIN && type != SUB && type != MSGBOX && type != BUTTON) return WIDGET_NOT_VALID_INPUT;
    Widget->type = type;
    return WIDGET_EOK;
}

int renderEmpty(Widget *widget){
    for (int i = 0; i < widget->height; i++)
    {
        gotoxy(widget->posx,widget->posy + i);
        for (int j = 0; j < widget->width; j++)
        {
            printf(" ");
        }
    }
    return WIDGET_EOK;
}

int clearWidget(Widget* widget){
    arrayDestroy(widget->label);
    for (int i = 0; i < arraySize(widget->subWidget); i++)
    {
        Widget *tmp;
        arrayGetAt(widget->subWidget,i,(LPDATA *)&tmp);
        arrayDestroy(tmp->label);
        arrayDestroy(tmp->subWidget);
    }
    arrayDestroy(widget->subWidget);
    free(widget);
    return WIDGET_EOK;
}

int printSiglelineWidget(Widget* widget, int posy, int posx, const char* text, int color){
    Label buf;
    setLabel(&buf, posy, posx, text, color);
    printLabel(widget,&buf);
    return WIDGET_EOK;
}
