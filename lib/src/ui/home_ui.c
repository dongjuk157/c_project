#include "home_ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"
#include "messagebox.h"
HOME_UI* createHomeUI(){
    HOME_UI* home = createMainWidget(0,0,25,75);

    labelAdd(home,5,28,"주차 관리 프로그램", 0);
    labelAdd(home,12,10,"1. 출입 차량 관리", 0);
    labelAdd(home,12,30,"2. 결제 기능", 0);
    labelAdd(home,12,50,"3. 주차 현황", 0);
    labelAdd(home,16,10,"4. 차량 조회", 0);
    labelAdd(home,16,30,"5. 주차 이력", 0);
    labelAdd(home,16,50,"6. 다른 계정으로 로그인", 0);

    labelAdd(home,20,10,"메뉴를 선택해주세요 >> ", 0);

    return home;
}

int checkinit(char *init){
    if(!strcmp("exit", init)) return EXIT;
    else{
        int num = atoi(init);
        // if(num == HOME) return HOME;
        if(num == IOMANAGE) return IOMANAGE;
        else if(num == PAY) return PAY;
        else if(num == PARKSTATUS) return PARKSTATUS;
        else if(num == CARINFO) return CARINFO;
        else if(num == PARKHISTORY) return PARKHISTORY;
        else if(num == LOGIN) return LOGIN;
        // else if(num == ENROLLUSER) return ENROLLUSER;
        // else if(num == SETTING) return SETTING;
        #ifdef TEST
        else if(num == 9) return 9;
        #endif
        else{
            messageBox(NULL,7,17,"잘못된 입력입니다.");
            return HOME;
        }
    }
}

int renderHomeUI(HOME_UI* home, void *data){
    renderWidget(home);
    char init[20];

    fgets(init,20,stdin);
    init[strlen(init)-1] = '\0';

    return checkinit(init);
}
