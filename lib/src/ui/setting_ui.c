#include "setting_ui.h"
#include "linkedlist.h"
#include "info.h"
#include "join.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

SETTING_UI* createSettingUI(){
    SETTING_UI* setting = createMainWidget(DEFAULT_POSY,DEFAULT_POSX,20,57);

    labelAdd(setting,6,15,"건물 내 주차장 상세정보 입력", 0);
    labelAdd(setting ,9,10, "┌───────────────┬────────────────────┐",0);
    labelAdd(setting, 10,10,"│  지상층 갯수  │                    │",0);
    labelAdd(setting ,11,10,"├───────────────┼────────────────────┤",0);
    labelAdd(setting ,12,10,"│  지하층 갯수  │                    │",0);
    labelAdd(setting ,13,10,"└───────────────┴────────────────────┘",0);
    

    Widget* nextBtn = createButton(15,15,10,"  다음  ",44);
    Widget* cancleBtn = createButton(15,31,10,"  취소  ",41);

    addWidget(setting, nextBtn);
    addWidget(setting, cancleBtn);

    return setting;
}

SETTING_UI* createSettingDetailUI(int floor){
    SETTING_UI* setting = createMainWidget(DEFAULT_POSY,DEFAULT_POSX,25,57);

    labelAdd(setting,6,15,"건물 내 주차장 상세정보 입력", 0);

    labelAdd(setting ,9, 9,"┌────────────────┬────────────────────┐",0);
    labelAdd(setting, 10,9,"│    현재 층     │                    │",0);
    labelAdd(setting ,11,9,"├────────────────┼────────────────────┤",0);
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

    return setting;
}

int renderSettingUI(SETTING_UI* setting, void *id){
    renderWidget(setting);
    int upperNum;
    int lowerNum;

    char buffer[20];

    gotoxy(30,11);
    fgets(buffer, 20, stdin);
    upperNum = atoi(buffer);    
    

    gotoxy(30,13);
    fgets(buffer, 20, stdin);
    lowerNum = -1 * atoi(buffer);

    LinkedList *list = create_linked_list_ptr();

    for (int i = upperNum; i >= lowerNum; i--)
    {
        if(i==0) continue;
        PARK* park = (PARK*)malloc(sizeof(PARK));
        park->floor = i;
        SETTING_DETAIL_UI* detail = createSettingDetailUI(i);
        renderSettingDetailUI(detail, &park); 
        
        list_push_back(list,(LPDATA)park);

        clearWidget(detail);
    }
    

    createParkingLot(id,list);

    return LOGIN;
}

int renderSettingDetailUI(SETTING_DETAIL_UI* detail, PARK** park){
    renderWidget(detail);
    int total, electric, light, handicapped;
    char buffer[20];

    gotoxy(30,13);
    myGetline(buffer, 20, stdin);
    total = atoi(buffer);   

    gotoxy(30,15);
    myGetline(buffer, 20, stdin);
    electric = atoi(buffer);   

    gotoxy(30,17);
    myGetline(buffer, 20, stdin);
    light = atoi(buffer);   

    gotoxy(30,19);
    myGetline(buffer, 20, stdin);
    handicapped = atoi(buffer);   

    (*park)->total = total;
    (*park)->electric_charge = electric;
    (*park)->light_car = light;
    (*park)->handicapped = handicapped;
    (*park)->total_car = 0;
    
    //valid check

    return 0;
}