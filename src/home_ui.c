#include "home_ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HOME_UI* createHomeUI(){
    HOME_UI* home = (HOME_UI*)malloc(sizeof(HOME_UI));
    setWidgetPos(home, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(home, 25, 75);
    setWidgetType(home, MAIN);
    arrayCreate(&(home->label));

    Label* title = createLabel();
    setLabelPos(title,5, 28);
    setLabelText(title,"주차 관리 프로그램");

    Label* io_manage = createLabel();
    setLabelPos(io_manage,12,10);
    setLabelText(io_manage,"1. 출입 차량 관리");

    Label* pay_manage= createLabel();
    setLabelPos(pay_manage,12,30);
    setLabelText(pay_manage,"2. 정산 기능");

    Label* park_status = createLabel();
    setLabelPos(park_status,12,50);
    setLabelText(park_status,"3. 주차 현황");

    Label* vehicle_inquiry = createLabel();
    setLabelPos(vehicle_inquiry,16,10);
    setLabelText(vehicle_inquiry,"4. 차량 조회");

    Label* park_history = createLabel();
    setLabelPos(park_history,16,30);
    setLabelText(park_history,"5. 주차 이력");

    #ifdef TEST
    
    Label* dummy = createLabel();
    setLabelPos(dummy,16,50);
    setLabelText(dummy,"6. 더미데이터 입력");
    addLabel(home, dummy);

    #endif // TEST
    
   

    Label* input = createLabel();
    setLabelPos(input, 20, 10);
    setLabelText(input,"메뉴를 선택해주세요 >> ");


    addLabel(home, title);
    addLabel(home,io_manage);
    addLabel(home,pay_manage);
    addLabel(home,park_status);
    addLabel(home,vehicle_inquiry);
    addLabel(home,park_history);
    addLabel(home,input);

    return home;
}

int checkinit(char *init){
    if(!strcmp("exit", init)) return EXIT;
    else{
        int num = atoi(init);
        if(num == HOME) return HOME;
        else if(num == IOMANAGE) return IOMANAGE;
        else if(num == PAY) return PAY;
        else if(num == PARKSTATUS) return PARKSTATUS;
        else if(num == CARINFO) return CARINFO;
        else if(num == PARKHISTORY) return PARKHISTORY;
        #ifdef TEST
        else if(num == 6) return 6;
        #endif
        else return INPUTERROR;
    }
}

int renderHomeUI(HOME_UI* home){
    renderWidget(home);
    char init[20];

    fgets(init,20,stdin);
    init[strlen(init)-1] = '\0';

    return checkinit(init);
}