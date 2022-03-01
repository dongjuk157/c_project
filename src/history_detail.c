#include "history_detail.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HISTORY_DETAIL_UI* createHistoryDetailUI(int type){

    HISTORY_DETAIL_UI* history = (HISTORY_DETAIL_UI*)malloc(sizeof(HISTORY_DETAIL_UI));
    setWidgetPos(history, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(history, 25, 81);
    setWidgetType(history, MAIN);
    arrayCreate(&(history->label));

    Label* title = createLabel();
    setLabelPos(title,5, 31);
    setLabelText(title,"주차 관리 프로그램");

    Label* subTitle = createLabel();
    setLabelPos(subTitle,7,33);
    setLabelText(subTitle,"주차 이력 조회");
    
    addLabel(history, title);
    addLabel(history, subTitle);

    Label* input = createLabel();
    setLabelPos(input, 10, 10);

    if(type == BY_CAR_NUMBER){
        setLabelText(input,"차량번호 입력(띄어쓰기 X) >> ");
    }
    else if(type == BY_NOT_PAID){
        setLabelPos(input,10,26);
        setLabelText(input,"미정산 주차 이력");
    }
    else if(type == BY_DATE_IN){
        setLabelText(input,"입차 날짜 입력(2022-02-12) >> ");
    }
    else if(type == BY_DATE_OUT){
        setLabelText(input,"출차 날짜 입력(2022-02-12) >>");
    }
    
    else{
        clearWidget(history);
    }
   
    addLabel(history, input);

    return history;
}
Widget* createHistoryDetailSub(){
    Widget* historyData = createWidget();
    setWidgetPos(historyData,13,5);
    setWidgetSize(historyData,11, 73);
    setWidgetType(historyData,SUB);

    Label* columnBarTop = createLabel();
    Label* columns = createLabel();
    Label* columnBarBottom = createLabel();

    setLabelPos(columnBarTop,0,0);
    setLabelPos(columns,1,0);
    setLabelPos(columnBarBottom,2,0);


    setLabelText(columnBarTop ,   "┌───────────┬──────────────────┬──────────────────┬──────┬───────┬──────┐");
    setLabelText(columns,         "│ 차량 번호 │    입차  시간    │    출차  시간    │ 구분 │ 요 금 │ 정산 │");
    setLabelText(columnBarBottom ,"├───────────┴──────────────────┴──────────────────┴──────┴───────┴──────┤");


    addLabel(historyData,columnBarTop);
    addLabel(historyData,columns);
    addLabel(historyData,columnBarBottom);
    return historyData;
}


int renderHistoryDetailByCarNum(HISTORY_DETAIL_UI* history){
    renderWidget(history);

    char carNumber[20];
    fgets(carNumber,20,stdin);
    carNumber[strlen(carNumber)-1] = '\0';
    
    if(!strcmp("exit",carNumber)){
        return HOME;
    }
    else{
    }

    return HOME;
}

int renderHistoryDetailByNotPaid(HISTORY_DETAIL_UI* history){
    renderWidget(history);
    
    char init[20];
    fgets(init,20,stdin);
    init[strlen(init)-1] = '\0';
    
    if(!strcmp("exit",init)){
        return HOME;
    }

    return HOME;
}

int renderHistoryDetailByDate(HISTORY_DETAIL_UI* history){
    renderWidget(history);
    
    char init[20];
    fgets(init,20,stdin);
    init[strlen(init)-1] = '\0';
    
    if(!strcmp("exit",init)){
        return HOME;
    }
    else {
        Widget* historyData = createHistoryDetailSub();
        
        // 데이터 7개까지 출력 가능
        // Label* log1 = createLabel();
        // setLabelPos(log1,3,1);
        // setLabelText(log1," 123가1234   2022.02.10 13:24   2022.02.10 15:22   경차   32000    X");
        // addLabel(historyData,log1);
        

        renderWidget(historyData);
        getch();
    }

    return HOME;
}
