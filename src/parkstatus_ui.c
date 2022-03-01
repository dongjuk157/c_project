#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parkstatus_ui.h"

PARKSTATUS_UI* createParkStatusUI(){

    PARKSTATUS_UI *parkStatus_UI = (PARKSTATUS_UI *)malloc(sizeof(PARKSTATUS_UI));

    // 기본 위젯 Position 세팅
    setWidgetPos(parkStatus_UI, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(parkStatus_UI, 25, 70);
    setWidgetType(parkStatus_UI, MAIN);
    arrayCreate(&(parkStatus_UI->label));

    // Label 세팅
    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 31);
    setLabelText(subTitle,"주차 현황");

    Label *selectOne = createLabel();
    setLabelPos(selectOne, 10, 10);
    setLabelText(selectOne,"1. 전체 현황 조회");

    Label *selectTwo = createLabel();
    setLabelPos(selectTwo, 13, 10);
    setLabelText(selectTwo,"2. 층별 현황 조회");

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

    REPEAT:
    {
    //UI 프레임 그리기
    renderWidget(parkStatus_UI);
    
    //세팅된 label 출력
    for (int i = 0; i < arraySize(parkStatus_UI->label); i++)
        printLabel(parkStatus_UI, (Label *)(parkStatus_UI->label->lpData)[i]);

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
    } else if(num == 2){
        //floor status
    } else{
        system("clear");
        goto REPEAT;
    }
    
    return HOME;
    }
}
