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
    ok->color = 44;
    addLabel(okBtn, ok);

    Label* cancle = createLabel();
    setLabelPos(cancle,1,1);
    cancle->color = 0;
    setLabelText(cancle, "  취소  ");
    addLabel(cancleBtn, cancle);

    addWidget(msgBox, okBtn);
    addWidget(msgBox, cancleBtn);


    renderWidget(msgBox);

    printSiglelineWidget(msgBox, 4, 5, message, 0);

    clearWidget(msgBox);

    char key = 0;
    int type = ID_OK;
    while(key = getch()){
        if(key == '\n'){
            break;
        }
        else if(key == '\33'){
            key = getch();
            key = getch();
            if(key == 'D'){
                type=ID_OK;
                printSiglelineWidget(okBtn,1,1,"  확인  ",44);
                printSiglelineWidget(cancleBtn,1,1,"  취소  ",0);
            }
            else if(key == 'C'){
                type =ID_CANCLE;
                printSiglelineWidget(okBtn,1,1,"  확인  ",0);
                printSiglelineWidget(cancleBtn,1,1,"  취소  ",41);
            }
           
        }
    }

    return type;
}