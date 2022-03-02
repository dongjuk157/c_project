#include "messagebox.h"
#include <stdio.h>

int messageBox(Widget* mainWindow, int posy, int posx ,char* message){
    Widget* msgBox = createWidget();
    setWidgetSize(msgBox, 10,40);
    setWidgetPos(msgBox,posy,posx);
    setWidgetType(msgBox,MSGBOX);
    renderEmpty(msgBox);

    Widget* okBtn = createWidget();
    setWidgetPos(okBtn,6,5);
    setWidgetSize(okBtn,3,10);
    setWidgetType(okBtn,SUB);

    Widget* cancleBtn = createWidget();
    setWidgetPos(cancleBtn,6,25);
    setWidgetSize(cancleBtn,3,10);
    setWidgetType(cancleBtn,SUB);

    Label* ok = createLabel();
    setLabelPos(ok,1,1)  ;
    setLabelText(ok, "  확인  ");
    ok->color = 42;
    addLabel(okBtn, ok);

    Label* cancle = createLabel();
    setLabelPos(cancle,1,1);
    cancle->color = 41;
    setLabelText(cancle, "  취소  ");
    addLabel(cancleBtn, cancle);

    addWidget(msgBox, okBtn);
    addWidget(msgBox, cancleBtn);


    renderWidget(msgBox);

    printSiglelineWidget(msgBox, 4, 5, message, 0);

    clearWidget(msgBox);

    char key = getchar();

    if(key == '\n'){
        return ID_OK;
    }
    else{
        return ID_CANCLE;
    }

}