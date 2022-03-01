#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "manage.h"
#include "manage_ui.h"

extern LPHASH user;
extern LinkedList current_list;
extern LinkedList current_car_list;


// 결제하기 기능 선택시 나타날 UI 제작 -> 제작한 Widget 구조체의 포인터 리턴
MANAGE_UI* createManageUI(){

    MANAGE_UI *manage = (MANAGE_UI *)malloc(sizeof(MANAGE_UI));

    // 기본 위젯 Position 세팅
    setWidgetPos(manage, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(manage, 25, 70);
    setWidgetType(manage, MAIN);
    arrayCreate(&(manage->label));

    // Label 세팅
    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 31);
    setLabelText(subTitle,"입출차 관리");

    Label *selectOne = createLabel();
    setLabelPos(selectOne, 13, 10);
    setLabelText(selectOne,"1. 입차");

    Label *selectTwo = createLabel();
    setLabelPos(selectTwo, 16, 10);
    setLabelText(selectTwo,"2. 출차");

    Label *prompt = createLabel();
    setLabelPos(prompt, 20, 10);
    setLabelText(prompt,"기능을 선택하세요 >> ");

    // 세팅한 Label Widget.label 동적 배열에 담기
    addLabel(manage, title);
    addLabel(manage, subTitle);
    addLabel(manage, selectOne);
    addLabel(manage, selectTwo);
    addLabel(manage, prompt);

    return manage;
}

int renderManageUI(MANAGE_UI *manage){
    //UI 프레임 그리기
    renderWidget(manage);
    
    //세팅된 label 출력
    for (int i = 0; i < arraySize(manage->label); i++)
        printLabel(manage, (Label *)(manage->label->lpData)[i]);

    //prompt로 받을 선택넘버 | exit - home | 1,2 - 각 Page로 | 이외 - 다시입력 |
    char selectNumber[8];

    //User에게 입력받고 개행문자 제거
    fgets(selectNumber, 8, stdin);
    selectNumber[strlen(selectNumber)-1] = '\0';
    
    if(!strcmp("exit", selectNumber))
        return HOME;

    int num = atoi(selectNumber);
    if(num == 1){
        // 입차
        getValuesUI('i');
        
    } else if(num == 2){
        // 출차
        getValuesUI('o');
    } else{
        system("clear");
    }
    return HOME;
}

int getValuesUI(char io){

}