#include "widget.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

Widget* createWidget()
{
    Widget* widget = (Widget*)malloc(sizeof(Widget));
    
    arrayCreate(&(widget->label));
    
    return widget;
}

void printWidget(Widget* widget)
{
    system("clear");
    gotoxy(widget->posx,widget->posy);
    printf("┏━");
    for (int i = 1; i < widget->width-1; i++) printf("━━");
    printf("━┓");

    for (int i = 1; i < widget->height-1; i++)
    {
       gotoxy(widget->posx, widget->posy + i + 1);
       printf("┃ ");
       gotoxy(widget->posx + widget->width * 2, widget->posy + i + 1);
       printf("┃");
    }
    printf("\n┗");
    for (int i = 1; i <widget->width; i++) printf("━━");
    printf("┛\n");
}

void render(Widget* widget)
{
    printWidget(widget);
    static int count = 0;
    for (int i = 0; i < arraySize(widget->label); i++,count++)
    {
        // printf("%d",count);
        printLabel((Label *)(widget->label->lpData)[i]);
    }
}
bool addLabel(Widget *widget, Label *label)
{
    if(widget->label == NULL) return False;

    arrayAdd(widget->label, label);
    return True;
}

void setWidgetPos(Widget *widget, int posy, int posx)
{
    widget -> posy = posy;
    widget -> posx = posx;
}

void setWidgetSize(Widget *widget, int height, int width)
{
    widget->height = height;
    widget->width = width;
}