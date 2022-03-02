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

int printWidget(Widget* widget)
{
    if(widget->type == MAIN || widget->type == MSGBOX){
        gotoxy(widget->posx,widget->posy);
        printf("┏");
        for (int i = 1; i < widget->width-1; i++) printf("━");
        printf("┓");

        for (int i = 1; i < widget->height-1; i++)
        {
        gotoxy(widget->posx, widget->posy + i);
        printf("┃");
        gotoxy(widget->posx + widget->width-1, widget->posy + i);
        printf("┃");
        }
        printf("\n");
        gotoxy(widget->posx, widget->posy + widget->height-1);
        printf("┗");
        for (int i = 1; i <widget->width-1; i++) printf("━");
        printf("┛\n");


        gotoxy(widget->posx, widget->posy + 2);
        printf("┣");
        
        for (int i = 0; i < widget->width-2; i++){
            printf("━");
        }

        printf("┫");

        printf("\x1b[%dm",44);
        gotoxy(widget->posx + 1, widget->posy + 1);
        for (int i = 0; i < widget->width-8; i++)
        {   
            printf(" ");
        }
        printf("━ ■ X ");
        printf("\x1b[0m");
    }
    else if(widget->type == SUB){
        gotoxy(widget->posx,widget->posy);
        printf("┌");
        for (int i = 1; i < widget->width-1; i++) printf("─");
        printf("┐");

        for (int i = 1; i < widget->height-1; i++)
        {
        gotoxy(widget->posx, widget->posy + i);
        printf("│");
        gotoxy(widget->posx + widget->width-1, widget->posy + i);
        printf("│");
        }
        printf("\n");
        gotoxy(widget->posx, widget->posy + widget->height-1);
        printf("└");
        for (int i = 1; i <widget->width-1; i++) printf("─");
        printf("┘\n");
    }
    return WIDGET_EOK;
}

int renderWidget(Widget* widget)
{
    if(widget->type == MAIN) system("clear");
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
    if(type != MAIN && type != SUB && type != MSGBOX) return WIDGET_NOT_VALID_INPUT;
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
