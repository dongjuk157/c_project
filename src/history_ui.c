#include "history_ui.h"
#include "history_detail.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


HISTORY_UI* createHistoryUI(){

    HISTORY_UI* history = createWidget();
    setWidgetPos(history, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(history, 25, 70);
    setWidgetType(history, MAIN);

    labelAdd(history,5,26,"주차 관리 프로그램", 0);
    labelAdd(history,7,28,"주차 이력 조회", 0);
    labelAdd(history,12,10,"1. 차량 번호로 조회", 0);
    labelAdd(history,12,40,"2. 미정산 이력 조회", 0);
    labelAdd(history,16,10,"3. 날짜별 조회(입차)", 0);
    labelAdd(history,16,40,"4. 날짜별 조회(출차)", 0);
    labelAdd(history,20,10,"조회 방식 입력 >> ", 0);

    return history;
}

int renderHistoryUI(HISTORY_UI* history, void *data){

    renderWidget(history);
    char init[20];

    fgets(init,20,stdin);
    init[strlen(init)-1] = '\0';

    if(!strcmp("exit", init)) return HOME;
    else{
        HISTORY_DETAIL_UI* history_detail;
        int type = atoi(init);
        if(type < 1 || type > 4) return PARKHISTORY;
        else{
            history_detail = createHistoryDetailUI(type);
            renderHistoryDetail(history_detail, type);
            clearWidget(history_detail);
        }
    }

    return HOME;
}