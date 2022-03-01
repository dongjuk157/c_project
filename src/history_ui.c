#include "history_ui.h"
#include "history_detail.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*FP)(Widget*);

HISTORY_UI* createHistoryUI(){

    HISTORY_UI* history = (HISTORY_UI*)malloc(sizeof(HISTORY_UI));
    setWidgetPos(history, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(history, 25, 70);
    setWidgetType(history, MAIN);
    arrayCreate(&(history->label));

    Label* title = createLabel();
    setLabelPos(title,5, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label* subTitle = createLabel();
    setLabelPos(subTitle,7,28);
    setLabelText(subTitle,"주차 이력 조회");

    Label* carNumber = createLabel();
    setLabelPos(carNumber,12,10);
    setLabelText(carNumber,"1. 차량 번호로 조회");

    Label* notPaid = createLabel();
    setLabelPos(notPaid,12, 40);
    setLabelText(notPaid,"2. 미정산 이력 조회");

    Label* inDate = createLabel();
    setLabelPos(inDate,16,10);
    setLabelText(inDate,"3. 날짜별 조회(입차)");

    Label* outDate = createLabel();
    setLabelPos(outDate,16,40);
    setLabelText(outDate,"4. 날짜별 조회(출차)");

    Label* input = createLabel();
    setLabelPos(input, 20, 10);
    setLabelText(input,"조회 방식 입력 >> ");

    addLabel(history, title);
    addLabel(history, subTitle);
    addLabel(history, carNumber);
    addLabel(history, notPaid);
    addLabel(history, inDate);
    addLabel(history, outDate);
    addLabel(history,input);

    return history;
}

int renderHistoryUI(HISTORY_UI* history){
    renderWidget(history);
    char init[20];

    fgets(init,20,stdin);
    init[strlen(init)-1] = '\0';

    if(!strcmp("exit", init)) return HOME;
    else{
        HISTORY_DETAIL_UI* history_detail;
        FP render;
        if(!strcmp("1", init)){
            history_detail = createHistoryDetailUI(1);
            render = renderHistoryDetailByCarNum;
        }
        else if(!strcmp("2", init)){
            history_detail = createHistoryDetailUI(2);
            render = renderHistoryDetailByNotPaid;
        }
        else if(!strcmp("3", init)){
            history_detail = createHistoryDetailUI(3);
            render = renderHistoryDetailByDate;
        }
        else if(!strcmp("4", init)){
            history_detail = createHistoryDetailUI(4);
            render = renderHistoryDetailByDate;
        }
        else return HOME;

        render(history_detail);

        clearWidget(history_detail);
    }
    
    return HOME;
}