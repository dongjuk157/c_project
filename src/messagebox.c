#include "messagebox.h"

int messageBox(Widget* mainWindow, char* message){
    Widget* msgBox = createWidget();
    setWidgetSize(msgBox, 10,32);
    setWidgetPos(msgBox,7,22);
    setWidgetType(msgBox,MSGBOX);
    renderEmpty(msgBox);

    Widget* okBtn = createWidget();
    setWidgetPos(okBtn,6,5);
    setWidgetSize(okBtn,3,10);
    setWidgetType(okBtn,SUB);

    Widget* cancleBtn = createWidget();
    setWidgetPos(cancleBtn,6,17);
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

    printSiglelineWidget(msgBox, 4,5,message);

    clearWidget(msgBox);

    char key = getch();

    if(key == '\n'){
        return ID_OK;
    }
    else{
        return ID_CANCLE;
    }

}