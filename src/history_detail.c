#include "history_detail.h"
#include "info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manage.h"
#include "messagebox.h"
 

HISTORY_DETAIL_UI* createHistoryDetailUI(int type){

    HISTORY_DETAIL_UI* history = createWidget();
    setWidgetPos(history, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(history, 25, 81);
    setWidgetType(history, MAIN);
    arrayCreate(&(history->label));

    labelAdd(history,5,31,"주차 관리 프로그램",0);
    labelAdd(history,7,33,"주차 이력 조회",0);

    if(type == BY_CAR_NUMBER){
        labelAdd(history,10,10,"차량번호 입력(띄어쓰기 X) >> ",0 );
    }
    else if(type == BY_NOT_PAID){
        labelAdd(history,10,32,"미정산 주차 이력",0 );
    }
    else if(type == BY_DATE_IN){
        labelAdd(history,10,10,"입차 날짜 입력(2022-02-12) >> ",0 );
    }
    else if(type == BY_DATE_OUT){
        labelAdd(history,10,10,"출차 날짜 입력(2022-02-12) >> ",0 );
    }
    else{
        clearWidget(history);
    }
   

    return history;
}

Widget* createHistoryDetailSub(){
    Widget* historyData = createWidget();
    setWidgetPos(historyData,13,5);
    setWidgetSize(historyData,11, 73);
    setWidgetType(historyData,SUB);
    
    labelAdd(historyData ,0,0,"┌───────────┬──────────────────┬──────────────────┬──────┬───────┬──────┐",0);
    labelAdd(historyData, 1,0,"│ 차량 번호 │    입차  시간    │    출차  시간    │ 구분 │ 요 금 │ 정산 │",0);
    labelAdd(historyData ,2,0,"├───────────┴──────────────────┴──────────────────┴──────┴───────┴──────┤",0);

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
    int count = arraySize(datas);    
    for (int i = 0; i < (count-1)/7 + 1; i++)
    {
        Widget* historyData = createHistoryDetailSub();
        renderEmpty(historyData);

        for (int j = 0; j < min(7,count - i*7); j++)
        {
            CAR_INFO* buf;
            char str[100];
            arrayGetAt(datas, i*7 + j, (LPDATA *)&buf);
            sprintf(str," %9s   %16s   %16s   %4s   %5d    %c",
                buf->car_number,
                buf->in_datetime,
                buf->out_datetime,
                (buf->car_type == 'e') ? "전기" : (buf->car_type == 'l') ? "경차" : "일반",
                buf->fee,
                (buf->is_paid==True) ? 'O' : 'X'
            );
            labelAdd(historyData,3+j,1,str,0);
        }
        renderWidget(history);
        renderWidget(historyData);
        clearWidget(historyData);
        getchar();
        if(i == ((count-1)/7)){
            messageBox(historyData,7,17,"마지막 페이지 입니다.");
            arrayDestroy(datas);
            return HOME;
        }
        else if(messageBox(historyData,7,17,"다음페이지를 보시겠습니까?")==ID_CANCLE){
            arrayDestroy(datas);
            return HOME;
        }

    }
    arrayDestroy(datas);
    return HOME;
}


int getHistoryDetail(int type, char* data, LPARRAY* datas){
    arrayCreate(datas);
    FILE* fp = fopen(HISTORY_DATA_FILE_PATH,"rb");
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
