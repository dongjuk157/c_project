#include "history_detail.h"
#include "info.h"
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
        setLabelPos(input,10,32);
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


int renderHistoryDetail(HISTORY_DETAIL_UI* history, int type){
    renderWidget(history);
    char init[20];

    if(type == BY_CAR_NUMBER || type == BY_DATE_IN || type == BY_DATE_OUT){
        fgets(init,20,stdin);
        init[strlen(init)-1] = '\0';
    
        if(!strcmp("exit",init)){
            return HOME;
        }
    }
    
    LPARRAY datas;
    getHistoryDetail(type, init, &datas);

    for (int i = 0; i < (arraySize(datas)-1)/7 + 1; i++)
    {
        Widget* historyData = createHistoryDetailSub();
        renderEmpty(historyData);
        for (int j = 0; j < min(7,arraySize(datas) - i*7); j++)
        {
            CAR_INFO* buf;
            char str[100];
            arrayGetAt(datas, i*7 + j, (LPDATA *)&buf);
            Label *temp = createLabel();
            setLabelPos(temp,3+j,1);
            sprintf(str," %s   %16s   %16s   %4s   %5d    %c",
                buf->car_number,
                buf->in_datetime,
                buf->out_datetime,
                (buf->car_type == 'e') ? "전기" : (buf->car_type == 'l') ? "경차" : "일반",
                buf->fee,
                (buf->is_paid==True) ? 'O' : 'X'
            );
            setLabelText(temp,str);
            addLabel(historyData, temp);
        }
        renderWidget(historyData);
        getch();
        clearWidget(historyData);
        
        
        arrayDestroy(datas);
    }
    return HOME;
}


int getHistoryDetail(int type, char* data, LPARRAY* datas){
    arrayCreate(datas);
    FILE* fp = fopen("./data/History.dat","rb");
    if(fp<=0){
        return 1;
    }
    while(1){
        CAR_INFO* info = (CAR_INFO *) malloc(sizeof(CAR_INFO));
        if(fread(info,sizeof(CAR_INFO), 1,fp)==False){
            break;
        }
        
        if(type == BY_CAR_NUMBER){
            if(!strcmp(info->car_number, data)) arrayAdd(*datas, info);
        }
        else if(type == BY_NOT_PAID){
            if(info->is_paid == False) arrayAdd(*datas, info);
        }
        else if(type == BY_DATE_IN){
            if(!strncmp(info->in_datetime, data,10)) arrayAdd(*datas, info);
        }
        else if(type == BY_DATE_OUT){
            if(!strncmp(info->out_datetime, data,10)) arrayAdd(*datas, info);
        }

    }
    fclose(fp);

    return 0;
}
