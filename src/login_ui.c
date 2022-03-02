#include "login_ui.h"
#include "join.h"
#include "messagebox.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char globalId[20];

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

    labelAdd(loginBtn,1,1," 로그인 ",44);

    labelAdd(enrollBtn, 1,1,"회원가입",0);

    addWidget(login, loginBtn);
    addWidget(login, enrollBtn);


    return login;
}

int renderLoginUI(LOGIN_UI* login, char *id){
    renderWidget(login);
    // char id[20];
    char password[20];
    char key = 0;
    int type = 0;
    while(key = getch()){
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

    if(type == 1){
        return ENROLLUSER;
    }

    gotoxy(27,11);
    fgets(id, 20, stdin);
    id[strlen(id)-1] = '\0';

    gotoxy(27,13);
    fgets(password, 20, stdin);
    password[strlen(password)-1] = '\0';

    int res = loginCheck(id,password);
    if(res == -3){
        messageBox(login,7,9,"잘못된 아이디 입니다.");
        return LOGIN;
    }
    else if(res == -2){
        messageBox(login,7,9,"비밀번호를 다시 입력해주세요.");
        return LOGIN;
    }
    else if(res == 0){
        messageBox(login,7,9,"로그인 성공");
        strcpy(globalId,id);
    }
    
    return HOME;
}