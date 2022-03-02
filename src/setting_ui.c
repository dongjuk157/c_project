#include "setting_ui.h"
#include <stdio.h>
#include <string.h>

SETTING_UI* createSettingUI(){
    SETTING_UI* setting = createWidget();
    setWidgetPos(setting, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(setting, 20, 57);
    setWidgetType(setting, MAIN);

    labelAdd(setting,6,15,"건물 내 주차장 상세정보 입력", 0);

    labelAdd(setting ,9,10, "┌───────────────┬────────────────────┐",0);
    labelAdd(setting, 10,10,"│  지상층 갯수  │                    │",0);
    labelAdd(setting ,11,10,"├───────────────┼────────────────────┤",0);
    labelAdd(setting ,12,10,"│  지하층 갯수  │                    │",0);
    labelAdd(setting ,13,10,"└───────────────┴────────────────────┘",0);
    

    Widget* nextBtn = createWidget();
    setWidgetPos(nextBtn, 15,15);
    setWidgetSize(nextBtn, 3,10);
    setWidgetType(nextBtn, SUB);

    Widget* cancleBtn = createWidget();
    setWidgetPos(cancleBtn, 15,31);
    setWidgetSize(cancleBtn, 3,10);
    setWidgetType(cancleBtn, SUB);

    labelAdd(nextBtn,1,1,"  다음  ",44);
    labelAdd(cancleBtn, 1,1,"  취소  ",41);

    addWidget(setting, nextBtn);
    addWidget(setting, cancleBtn);


    return setting;
}

SETTING_UI* createSettingDetailUI(int floor){
    SETTING_UI* setting = createWidget();
    setWidgetPos(setting, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(setting, 25, 57);
    setWidgetType(setting, MAIN);

    labelAdd(setting,6,15,"건물 내 주차장 상세정보 입력", 0);

    labelAdd(setting ,9, 9,"┌────────────────┬────────────────────┐",0);
    labelAdd(setting, 10,9,"│    현재 층     │                    │",0);
    labelAdd(setting ,11, 9,"├────────────────┼────────────────────┤",0);
    labelAdd(setting, 12,9,"│    주차공간    │                    │",0);
    labelAdd(setting ,13,9,"├────────────────┼────────────────────┤",0);
    labelAdd(setting ,14,9,"│     전기차     │                    │",0);
    labelAdd(setting ,15,9,"├────────────────┼────────────────────┤",0);
    labelAdd(setting, 16,9,"│      경차      │                    │",0);
    labelAdd(setting ,17,9,"├────────────────┼────────────────────┤",0);
    labelAdd(setting ,18,9,"│     장애인     │                    │",0);
    labelAdd(setting ,19,9,"└────────────────┴────────────────────┘",0);

    char buf[20];
    if(floor > 0){
        sprintf(buf,"지상 %d층", floor);
    }
    else if(floor < 0){
        sprintf(buf,"지하 %d층", floor*-1);
    }
    labelAdd(setting,10,29,buf,0);
    

    Widget* nextBtn = createWidget();
    setWidgetPos(nextBtn, 20,15);
    setWidgetSize(nextBtn, 3,10);
    setWidgetType(nextBtn, SUB);

    Widget* cancleBtn = createWidget();
    setWidgetPos(cancleBtn, 20,31);
    setWidgetSize(cancleBtn, 3,10);
    setWidgetType(cancleBtn, SUB);

    labelAdd(nextBtn,1,1,"  확인  ",44);
    labelAdd(cancleBtn, 1,1,"  취소  ",41);

    addWidget(setting, nextBtn);
    addWidget(setting, cancleBtn);


    return setting;
}

int renderSettingUI(SETTING_UI* setting){
    renderWidget(setting);
    int upperNum;
    int lowerNum;

    char buffer[20];

    gotoxy(30,11);
    fgets(buffer, 20, stdin);
    upperNum = atoi(buffer);    
    

    gotoxy(30,13);
    fgets(buffer, 20, stdin);
    lowerNum = atoi(buffer);

    for (int i = upperNum; i >= lowerNum; i--)
    {
        if(i==0)continue;
        SETTING_DETAIL_UI* detail = createSettingDetailUI(i);
        renderSettingDetailUI(detail); 
    }
    
    return HOME;
}

int renderSettingDetailUI(SETTING_DETAIL_UI* detail){
    renderWidget(detail);
    int total, electric, light, handicapped;
    char buffer[20];

    gotoxy(30,13);
    fgets(buffer, 20, stdin);
    total = atoi(buffer);   

    gotoxy(30,15);
    fgets(buffer, 20, stdin);
    electric = atoi(buffer);   

    gotoxy(30,17);
    fgets(buffer, 20, stdin);
    light = atoi(buffer);   

    gotoxy(30,19);
    fgets(buffer, 20, stdin);
    handicapped = atoi(buffer);   

}