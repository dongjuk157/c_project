#include "enroll_ui.h"
#include "messagebox.h"
#include "info.h"
#include <stdio.h>
#include <string.h>
#include <join.h>

ENROLL_UI* createEnrollUI(){
    ENROLL_UI* enroll = createMainWidget(DEFAULT_POSY,DEFAULT_POSX,22,57);

    labelAdd(enroll,6,25,"회원가입", 0);
    labelAdd(enroll ,9,7, "┌──────────────────┬─────────────────────┐",0);
    labelAdd(enroll, 10,7,"│        ID        │                     │",0);
    labelAdd(enroll ,11,7,"├──────────────────┼─────────────────────┤",0);
    labelAdd(enroll ,12,7,"│     PASSWORD     │                     │",0);
    labelAdd(enroll ,13,7,"├──────────────────┼─────────────────────┤",0);
    labelAdd(enroll ,14,7,"│  PASSWORD CHECK  │                     │",0);
    labelAdd(enroll ,15,7,"└──────────────────┴─────────────────────┘",0);
    

    Widget* enrollBtn = createButton(17,7,20, "     회원가입     ",44);
    Widget* cancleBtn = createButton(17,29,20,"       취소       ",41);

    addWidget(enroll, enrollBtn);
    addWidget(enroll, cancleBtn);

    return enroll;
}

int renderEnrollUI(ENROLL_UI* enroll, void* id){
    
    renderWidget(enroll); //렌더링

    char password[20];  //비밀번호
    char passwordCheck[20]; //비밀번호 확인

    gotoxy(30,11);
    myGetline((char*)id, 20, stdin); //id 입력

    gotoxy(30,13);
    myGetline(password, 20, stdin); //비밀번호 입력 

    gotoxy(30,15);
    myGetline(passwordCheck, 20, stdin); //비밀번호 확인 입력

    if(!strcmp(password, passwordCheck)){ //비밀번호 비교(같을때)
        int res = join(id,password);
        if(res == JOIN_EOK){
            messageBox(enroll,7,9,"회원가입 완료");
            return SETTING;
        }
        else{
            joinErrorHandler(enroll,res);
            return LOGIN;
        }
    }
    else{   //다를때
        messageBox(enroll,7,9,"비밀번호가 서로 다릅니다.");
        return ENROLLUSER;
    }
    return ENROLLUSER;

}
