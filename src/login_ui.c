#include "login_ui.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
LOGIN_UI* createLoginUI(){
    LOGIN_UI* login = createWidget();
    setWidgetPos(login, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(login, 20, 57);
    setWidgetType(login, MAIN);

    labelAdd(login,6,25,"로그인", 0);

    labelAdd(login ,9,10, "┌────────────┬─────────────────────┐",0);
    labelAdd(login, 10,10,"│     ID     │                     │",0);
    labelAdd(login ,11,10,"├────────────┼─────────────────────┤",0);
    labelAdd(login ,12,10,"│  PASSWORD  │                     │",0);
    labelAdd(login ,13,10,"└────────────┴─────────────────────┘",0);
    

    Widget* loginBtn = createWidget();
    setWidgetPos(loginBtn, 15,15);
    setWidgetSize(loginBtn, 3,10);
    setWidgetType(loginBtn, SUB);

    Widget* enrollBtn = createWidget();
    setWidgetPos(enrollBtn, 15,31);
    setWidgetSize(enrollBtn, 3,10);
    setWidgetType(enrollBtn, SUB);

    labelAdd(loginBtn,1,1," 로그인 ",42);

    labelAdd(enrollBtn, 1,1,"회원가입",44);

    addWidget(login, loginBtn);
    addWidget(login, enrollBtn);


    return login;
}

int renderLoginUI(LOGIN_UI* login){
    renderWidget(login);
    char id[20];
    char password[20];
    gotoxy(27,11);
    fgets(id, 20, stdin);
    id[strlen(id)-1] = '\0';

    gotoxy(27,13);
    fgets(password, 20, stdin);
    password[strlen(password)-1] = '\0';
    
}