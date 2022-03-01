#include "widget.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

Widget* createWidget()
{
    Widget* widget = (Widget*)malloc(sizeof(Widget));
    setWidgetPos(widget,DEFAULT_POSY,DEFAULT_POSX);
    arrayCreate(&(widget->label));
    
    return widget;
}

void printWidget(Widget* widget)
{
    if(widget->type == MAIN){
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
   
}

int renderWidget(Widget* widget)
{
    if(widget->type == MAIN) system("clear");
    printWidget(widget);
    for (int i = 0; i < arraySize(widget->label); i++)
    {
        printLabel(widget,(Label *)(widget->label->lpData)[i]);
    }
    return True;
}

bool addLabel(Widget *widget, Label *label)
{
    if(widget->label == NULL) return False;

    arrayAdd(widget->label, label);
    return True;
}

bool printLabel(Widget* widget, const Label* label){
    if(label->text==NULL) return False;

    gotoxy(widget->posx + label->posx,widget->posy + label->posy);
    printf("%s",label->text);    

    return True;
}


void setWidgetPos(Widget *widget, int posy, int posx)
{
    // if(posx<=0 || posy<=0) return;
    widget -> posy = posy;
    widget -> posx = posx;
}

void setWidgetSize(Widget *widget, int height, int width)
{
    widget->height = height;
    widget->width = width;
}

void setWidgetType(Widget *Widget, int type){
    Widget->type = type;
}

int clearWidget(Widget* widget){
    arrayDestroy(widget->label);

    free(widget);
}