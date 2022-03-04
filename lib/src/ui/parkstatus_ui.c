#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parkstatus_ui.h"
#include "parkstatus_detail.h"
#include "info.h"

PARKSTATUS_UI* createParkStatusUI(){

    // 기본 위젯 Position 세팅
    PARKSTATUS_UI *parkStatus_UI = createMainWidget(DEFAULT_POSY,DEFAULT_POSX,25,70);

    // Label 세팅
    labelAdd(parkStatus_UI, 5,26, "주차 관리 프로그램", 0);
    labelAdd(parkStatus_UI, 7,31, "주차 현황", 0);
    labelAdd(parkStatus_UI, 10,10, "1. 전체 현황 조회", 0);
    labelAdd(parkStatus_UI, 13,10, "2. 층별 현황 조회", 0);
    labelAdd(parkStatus_UI, 16,10, "3. 타 주차장 현황 조회", 0);
    labelAdd(parkStatus_UI, 20,10, "기능을 선택하세요 >> ", 0);

    return parkStatus_UI;
}

int renderParkStatusUI(PARKSTATUS_UI *parkStatus_UI, void *data){

    //UI 프레임 그리기
    renderWidget(parkStatus_UI);

    //prompt로 받을 선택넘버 | exit - home | 1,2 - 각 Page로 | 이외 - 다시입력 |
    char selectNumber[8];

    //User에게 입력받고 개행문자 제거
    myGetline(selectNumber, 8, stdin);
    
    if(!strcmp("exit", selectNumber))
        return HOME;

    int num = atoi(selectNumber);
    if(num == PARK_STATUS_ENTRY){
        //all status
        PARK_DETAIL_UI* entry_detail = createParkDetailEntryUI();
        renderDetailEntry(entry_detail);
        clearWidget(entry_detail);
        getchar();
    } 
    else if(num == PARK_STATUS_FLOOR){
        //floor status
        PARK_DETAIL_UI* floor_detail = createParkDetailFloorUI();
        renderDetailFloor(floor_detail);
        clearWidget(floor_detail);
        getchar();
    }
    else if(num == PARK_STATUS_OTHER){
        // other parkinglot status
        PARK_DETAIL_UI* other_entry = createParkDetailOtherUI();
        renderDetailOther(other_entry);
        clearWidget(other_entry);
        // getchar();
    }
    else return PARKSTATUS;
    
    return HOME;
}
