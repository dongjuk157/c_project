#include "parkstatus_detail.h"
#include "linkedlist.h"
#include "info.h"
#include <stdio.h>


extern LinkedList current_list;

PARK_DETAIL_UI* createParkDetailEntryUI(){
    PARK_DETAIL_UI* park_detail = createWidget();
    setWidgetPos(park_detail, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(park_detail,25,70);
    setWidgetType(park_detail,MAIN);
    arrayCreate(&(park_detail->label));

    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 24);
    setLabelText(subTitle,"[주차 현황 - 전체 조회]");

    addLabel(park_detail, title);
    addLabel(park_detail, subTitle);

    Widget* detailSub = createWidget();
    setWidgetPos(detailSub,14,4);
    setWidgetSize(detailSub,5,63);
    setWidgetType(detailSub,SUB);

    Label* columnBarTop = createLabel();
    Label* columns = createLabel();
    Label* columnBarBottom = createLabel();

    setLabelPos(columnBarTop,0,0);
    setLabelPos(columns,1,0);
    setLabelPos(columnBarBottom,2,0);


    setLabelText(columnBarTop ,   "┌─────────┬───────────┬─────────────┬───────────┬─────────────┐");
    setLabelText(columns,         "│ 총 공간 │ 남은 공간 │ 전기차 전용 │ 경차 전용 │ 장애인 전용 │");
    setLabelText(columnBarBottom ,"├─────────┴───────────┴─────────────┴───────────┴─────────────┤");


    addLabel(detailSub,columnBarTop);
    addLabel(detailSub,columns);
    addLabel(detailSub,columnBarBottom);

    addWidget(park_detail,detailSub);

    return park_detail;
}

PARK_DETAIL_UI* createParkDetailFloorUI(){
        PARK_DETAIL_UI* park_detail = createWidget();
    setWidgetPos(park_detail, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(park_detail,25,80);
    setWidgetType(park_detail,MAIN);
    arrayCreate(&(park_detail->label));

    Label *title = createLabel();
    setLabelPos(title, 3, 31);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 29);
    setLabelText(subTitle,"[주차 현황 - 층별 조회]");

    addLabel(park_detail, title);
    addLabel(park_detail, subTitle);

    Widget* detailSub = createWidget();
    setWidgetPos(detailSub,8,6);
    setWidgetSize(detailSub,16,70);
    setWidgetType(detailSub,SUB);

    Label* columnBarTop = createLabel();
    Label* columns = createLabel();
    Label* columnBarBottom = createLabel();

    setLabelPos(columnBarTop,0,0);
    setLabelPos(columns,1,0);
    setLabelPos(columnBarBottom,2,0);


    setLabelText(columnBarTop ,   "┌──────┬─────────┬───────────┬─────────────┬───────────┬─────────────┐");
    setLabelText(columns,         "│ 층수 │ 총 공간 │ 남은 공간 │ 전기차 전용 │ 경차 전용 │ 장애인 전용 │");
    setLabelText(columnBarBottom ,"├──────┴─────────┴───────────┴─────────────┴───────────┴─────────────┤");


    addLabel(detailSub,columnBarTop);
    addLabel(detailSub,columns);
    addLabel(detailSub,columnBarBottom);

    addWidget(park_detail,detailSub);

    return park_detail;
}


int renderDetailEntry(PARK_DETAIL_UI* park_detail){
    renderWidget(park_detail);

    PARK total;
    total.total = 0;
    total.total_car = 0;
    total.electric_charge = 0;
    total.handicapped = 0;
    total.light_car = 0;
    
    Node* temp = current_list.head;
    while(temp){
        PARK* buf = (PARK *)temp->data;
        total.total += buf->total;
        total.total_car += buf->total_car;
        total.electric_charge += buf->electric_charge;
        total.handicapped += buf->handicapped;
        total.light_car += buf->light_car;
        temp = temp->next;
    }

    char buffer[100];
    Label remain;
    labelCreate(&remain);
    setLabelPos(&remain,10,10);
    sprintf(buffer,"현재 주차가능 공간 수는 %d개 입니다.", total.total - total.total_car);
    setLabelText(&remain,buffer);
    printLabel(park_detail, &remain);

    Label data;
    labelCreate(&data);
    setLabelPos(&data,16,5);
    sprintf(buffer," %5d      %5d         %4d         %4d         %4d", 
        total.total,
        total.total - total.total_car,
        total.electric_charge,
        total.light_car,
        total.handicapped
    );
    setLabelText(&data,buffer);
    printLabel(park_detail,&data);

    return 0;
}
int renderDetailFloor(PARK_DETAIL_UI* park_detail){
    renderWidget(park_detail);
    int i = 0;
    Node* temp = current_list.head;
    while(temp){
        PARK* buf = (PARK *)temp->data;
        Label data;
        char buffer[100];
        labelCreate(&data);
        setLabelPos(&data,10+i++,6);
        sprintf(buffer," %4d   %5d       %5d        %4d          %4d        %4d", 
            buf->floor,
            buf->total,
            buf->total - buf->total_car,
            buf->electric_charge,
            buf->light_car,
            buf->handicapped
        );
        setLabelText(&data,buffer);
        printLabel(park_detail,&data);
        temp = temp->next;
    }
    return 0;
}