#include <stdio.h>
#include "array.h"
#include "widget.h"
#include "label.h"
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    Widget* frame = createWidget();
    setWidgetPos(frame, 0, 0);
    setWidgetSize(frame, 25, 50);

    Label* label = createLabel();
    setLabelPos(label,10, 30);
    setLabelText(label,"----------------");
    
    Label* label2 = createLabel();
    setLabelPos(label2,5, 20);
    setLabelText(label2,"Hello world");


    addLabel(frame, label);
    addLabel(frame, label2);

    while(1){
        usleep(1000 * 100);
        render(frame);
       
    }

    return 0;
}
