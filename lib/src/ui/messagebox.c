#include "messagebox.h"
#include <stdio.h>

int messageBox(Widget* mainWindow, int posy, int posx ,char* message){
    MsgBox* msgBox = createMsgBox(posy,posx);
    renderEmpty(msgBox);

    Widget* okBtn = createButton(6,5,10,"  확인  ",OK_BTN);
    Widget* cancleBtn = createButton(6,25,10,"  취소  ",0);

    addWidget(msgBox, okBtn);
    addWidget(msgBox, cancleBtn);
    labelAdd(msgBox, 4, 5, message, 0);

    renderWidget(msgBox);

    char key = 0;
    int type = ID_OK;
    while(1){
        key = getch();
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
    clearWidget(msgBox);
    return type;
}