#include "enroll_ui.h"
#include "messagebox.h"
#include <stdio.h>
#include <string.h>
#include <join.h>

ENROLL_UI* createEnrollUI(){
    ENROLL_UI* enroll = createWidget();
    setWidgetPos(enroll, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(enroll, 22, 57);
    setWidgetType(enroll, MAIN);

    labelAdd(enroll,6,25,"회원가입", 0);

    labelAdd(enroll ,9,7, "┌──────────────────┬─────────────────────┐",0);
    labelAdd(enroll, 10,7,"│        ID        │                     │",0);
    labelAdd(enroll ,11,7,"├──────────────────┼─────────────────────┤",0);
    labelAdd(enroll ,12,7,"│     PASSWORD     │                     │",0);
    labelAdd(enroll ,13,7,"├──────────────────┼─────────────────────┤",0);
    labelAdd(enroll ,14,7,"│  PASSWORD CHECK  │                     │",0);
    labelAdd(enroll ,15,7,"└──────────────────┴─────────────────────┘",0);
    

    Widget* enrollBtn = createWidget();
    setWidgetPos(enrollBtn, 17,7);
    setWidgetSize(enrollBtn, 3,20);
    setWidgetType(enrollBtn, SUB);

    labelAdd(enrollBtn, 1,1,"     회원가입     ",44);

    Widget* cancleBtn = createWidget();
    setWidgetPos(cancleBtn, 17,29);
    setWidgetSize(cancleBtn, 3,20);
    setWidgetType(cancleBtn, SUB);

    labelAdd(cancleBtn, 1,1,"       취소       ",41);

    addWidget(enroll, enrollBtn);
    addWidget(enroll, cancleBtn);


    return enroll;

}

int renderEnrollUI(ENROLL_UI* enroll){
    renderWidget(enroll);
    char id[20];
    char password[20];
    char passwordCheck[20];
    gotoxy(30,11);
    fgets(id, 20, stdin);
    id[strlen(id)-1] = '\0';

    gotoxy(30,13);
    fgets(password, 20, stdin);
    password[strlen(password)-1] = '\0';

    gotoxy(30,15);
    fgets(passwordCheck, 20, stdin);
    passwordCheck[strlen(passwordCheck)-1] = '\0';

    if(!strcmp(password, passwordCheck)){
        int res = join(id,password);
        if(res == -2) {
            messageBox(enroll,"해당 아이디가 이미 존재합니다.");
            return ENROLLUSER;
        }
        else if(res == 0){
            messageBox(enroll,"회원가입 완료");
        }
    }
    else{
        messageBox(enroll,"비밀번호가 서로 다릅니다.");
        return ENROLLUSER;
    }

    return HOME;
}
