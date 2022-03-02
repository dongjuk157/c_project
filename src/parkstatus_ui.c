#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parkstatus_ui.h"
#include "parkstatus_detail.h"

PARKSTATUS_UI* createParkStatusUI(){

    PARKSTATUS_UI *parkStatus_UI = createWidget();

    // 기본 위젯 Position 세팅
    setWidgetPos(parkStatus_UI, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(parkStatus_UI, 25, 70);
    setWidgetType(parkStatus_UI, MAIN);
    arrayCreate(&(parkStatus_UI->label));

    // Label 세팅
    Label *title = createLabel();
    setLabelPos(title, 5, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 7, 31);
    setLabelText(subTitle,"주차 현황");

    Label *selectOne = createLabel();
    setLabelPos(selectOne, 10, 10);
    setLabelText(selectOne,"1. 전체 현황 조회");

    Label *selectTwo = createLabel();
    setLabelPos(selectTwo, 13, 10);
    setLabelText(selectTwo,"2. 층별 현황 조회");

    Label *selectTwo = createLabel();
    setLabelPos(selectTwo, 16, 10);
    setLabelText(selectTwo,"3. 타 주차장 현황 조회");

    Label *prompt = createLabel();
    setLabelPos(prompt, 20, 10);
    setLabelText(prompt,"기능을 선택하세요 >> ");

    // 세팅한 Label Widget.label 동적 배열에 담기
    addLabel(parkStatus_UI, title);
    addLabel(parkStatus_UI, subTitle);
    addLabel(parkStatus_UI, selectOne);
    addLabel(parkStatus_UI, selectTwo);
    addLabel(parkStatus_UI, prompt);

    return parkStatus_UI;
}

int renderParkStatusUI(PARKSTATUS_UI *parkStatus_UI){

    //UI 프레임 그리기
    renderWidget(parkStatus_UI);

    //prompt로 받을 선택넘버 | exit - home | 1,2 - 각 Page로 | 이외 - 다시입력 |
    char selectNumber[8];

    //User에게 입력받고 개행문자 제거
    fgets(selectNumber, 8, stdin);
    selectNumber[strlen(selectNumber)-1] = '\0';
    
    if(!strcmp("exit", selectNumber))
        return HOME;

    int num = atoi(selectNumber);
    if(num == 1){
        //all status
        PARK_DETAIL_UI* entry_detail = createParkDetailEntryUI();
        renderDetailEntry(entry_detail);
        clearWidget(entry_detail);
        getchar();
    } 
    else if(num == 2){
        //floor status
        PARK_DETAIL_UI* floor_detail = createParkDetailFloorUI();
        renderDetailFloor(floor_detail);
        clearWidget(floor_detail);
        getchar();
    }
    else if(num == 3){
        // other parkinglot status
        PARK_DETAIL_UI* other_entry = createOtherParkUI();
        renderDetailOther(other_entry);
        clearWidget(other_entry);
        getchar();
    }
    else return PARKSTATUS;
    
    return HOME;
}
