#include "info_ui.h"
#include "info.h"
#include "messagebox.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// extern LPHASH user;
// extern LinkedList current_car_list;

INFO_UI* createInfoUI(){
    INFO_UI* info = createWidget();
    setWidgetPos(info, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(info, 25, 70);
    setWidgetType(info, MAIN);

    labelAdd(info,5,26,"주차 관리 프로그램",0);
    labelAdd(info,7,31,"차량 조회",0);
    labelAdd(info,10,10,"차량번호 입력(띄어쓰기 X) >> ",0);

    return info;
}


int findInfo(char* carNumber, Info *info){
    USER_INFO* user_info;
    int res;
    res = hashGetValue(user,carNumber,(LPDATA*)&user_info);
    if(res != ERR_HASH_OK){
        memset(info,0,sizeof(Info));
        return ERR_HASH_NOT_FOUND;
    }
    
    Node *tmp = current_car_list.head;
    CAR_INFO* car_info = NULL;
    while(tmp){
        CAR_INFO* buf = (CAR_INFO*)tmp->data;
        if(!strcmp(buf->car_number,carNumber)){
            car_info = buf;
            break;
        } 
        tmp = tmp->next;
    }


    char datetime[20];
    getDateTime(datetime);

    strcpy(info->carNumber,carNumber);
    if(car_info != NULL)
        strcpy(info->inDatetime,car_info->in_datetime);
    else   
        strcpy(info->inDatetime,"");
    strcpy(info->name,user_info->name);
    strcpy(info->phoneNumber,user_info->phone_num);
    if(car_info != NULL)
        info->fee = calculate_fee(info->inDatetime,datetime);
    else   
        info->fee = 0;
    
    return NFD;
}

int renderInfoUI(INFO_UI* info, void *dat){
    renderWidget(info);

    char carNumber[20];

    fgets(carNumber,20,stdin);
    carNumber[strlen(carNumber)-1] = '\0';
    
    if(!strcmp("exit",carNumber)){
        return HOME;
    }
    else if(!strcmp("",carNumber)){
        return CARINFO;
    }

    Info data;
    char buffer[50];
    if(findInfo(carNumber, &data)==ERR_HASH_NOT_FOUND){
        messageBox(info,7,17, "차량 정보가 존재하지 않습니다.");
        // printSiglelineWidget(info, 15, 10, "해당 차량 정보가 존재하지 않습니다...", 0);
        // getchar();
        return CARINFO;
    }; //data에 차량번호와 일치하는 info 객체 담음 없다면 못담음
    Widget* dataWidget = createWidget();
    setWidgetPos(dataWidget,14,10);
    setWidgetSize(dataWidget,9,52);
    setWidgetType(dataWidget, SUB);

    sprintf(buffer,"차량 번호 : %s",data.carNumber);
    labelAdd(dataWidget, 2,5, buffer, 0);

    sprintf(buffer,"차주 : %s",data.name);
    labelAdd(dataWidget, 3,5, buffer, 0);


    sprintf(buffer,"연락처 : %s",data.phoneNumber);
    labelAdd(dataWidget, 4,5, buffer, 0);


    sprintf(buffer,"입차 시간 : %s",data.inDatetime);
    labelAdd(dataWidget, 5,5, buffer, 0);


    sprintf(buffer,"주차 요금 : %d원",data.fee);
    labelAdd(dataWidget, 6,5, buffer, 0);

    renderWidget(dataWidget);

    getchar();
    
    return HOME;
}