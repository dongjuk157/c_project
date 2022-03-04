#include "login_ui.h"
#include "join.h"
#include "info.h"
#include "messagebox.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

LOGIN_UI* createLoginUI(){
    LOGIN_UI* login = createMainWidget(DEFAULT_POSY,DEFAULT_POSX,20, 57);

    labelAdd(login,6,25,"로그인", 0);
    labelAdd(login ,9,10, "┌────────────┬─────────────────────┐",0);
    labelAdd(login, 10,10,"│     ID     │                     │",0);
    labelAdd(login ,11,10,"├────────────┼─────────────────────┤",0);
    labelAdd(login ,12,10,"│  PASSWORD  │                     │",0);
    labelAdd(login ,13,10,"└────────────┴─────────────────────┘",0);
    
    Widget* loginBtn = createButton(15,15,10," 로그인 ",44);
    Widget* enrollBtn = createButton(15,31,10,"회원가입",0);

    addWidget(login, loginBtn);
    addWidget(login, enrollBtn);

    return login;
}

int renderLoginUI(LOGIN_UI* login, void *id){
    renderWidget(login);
    memset((char *)id,0,20);
    // char id[20];
    char password[20];
    char key = 0;
    int type = 0;
    while(1){
        key = getch();
        if(key == '\n'){
            break;
        }
        else if(key == '\33'){
            key = getch();
            key = getch();
            if(key == 'D'){
                type=0;
                printSiglelineWidget(login,16,16," 로그인 ",44);
                printSiglelineWidget(login,16,32,"회원가입",0);

            }
            else if(key == 'C'){
                type =1;
                printSiglelineWidget(login,16,16," 로그인 ",0);
                printSiglelineWidget(login,16,32,"회원가입",44);
            }
           
        }

    }

    if(type == ENROLL_BTN){ 
        return ENROLLUSER;
    }

    gotoxy(27,11);
    myGetline(id, 20, stdin);

    gotoxy(27,13);
    myGetline(password, 20, stdin);

    int res = loginCheck(id,password);
    if(res == JOIN_EOK){
        messageBox(login,7,9,"로그인 성공");
        return HOME;
    }
    else{
        joinErrorHandler(login, res);
        return LOGIN;
    }
    return HOME;
}