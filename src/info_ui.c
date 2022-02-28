#include "info_ui.h"
#include "info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

INFO_UI* createInfoUI(){
    INFO_UI* info = (INFO_UI*)malloc(sizeof(INFO_UI));
    setWidgetPos(info, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(info, 25, 70);
    setWidgetType(info, MAIN);
    arrayCreate(&(info->label));

    Label* title = createLabel();
    setLabelPos(title,5, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label* subTitle = createLabel();
    setLabelPos(subTitle,7,31);
    setLabelText(subTitle,"차량 조회");

    Label* input = createLabel();
    setLabelPos(input, 10, 10);
    setLabelText(input,"차량번호 입력(띄어쓰기 X) >> ");


    addLabel(info, title);
    addLabel(info, subTitle);
    addLabel(info,input);

    return info;
}


int findInfo(char* carNumber, Info *info){
    FILE* fp = fopen("data/Current.dat","rb");
    if(fp == NULL){
        return FOE;
    }
    
    while(fread(info,sizeof(Info),1,fp)){
        if(!strcmp(carNumber, info->carNumber)){
            fclose(fp);
            return EOK; 
        }
    }
    
    memset(info,0,sizeof(Info));
    fclose(fp); 
    return NFD;
}

int renderInfoUI(INFO_UI* info){
    printWidget(info);

    char carNumber[20];

    for (int i = 0; i < arraySize(info->label); i++)
    {
        printLabel(info,(Label *)(info->label->lpData)[i]);
    }

    fgets(carNumber,20,stdin);
    carNumber[strlen(carNumber)-1] = '\0';
    
    if(!strcmp("exit",carNumber)){
        return HOME;
    }

    Info data;
    char buffer[50];
    findInfo(carNumber, &data);
 
    Widget* dataWidget = createWidget();
    setWidgetPos(dataWidget,14,10);
    setWidgetSize(dataWidget,9,52);
    setWidgetType(dataWidget, SUB);


    Label* carNum = createLabel();
    setLabelPos(carNum,2,5);
    sprintf(buffer,"차량 번호 : %s",data.carNumber);
    setLabelText(carNum,buffer);

    Label* name = createLabel();
    setLabelPos(name,3,5);
    sprintf(buffer,"차주 : %s",data.name);
    setLabelText(name,buffer);

    Label* phoneNumber = createLabel();
    setLabelPos(phoneNumber,4,5);
    sprintf(buffer,"연락처 : %s",data.phoneNumber);
    setLabelText(phoneNumber,buffer);

    Label* inDatetime = createLabel();
    setLabelPos(inDatetime,5,5);
    sprintf(buffer,"입차 시간 : %s",data.inDatetime);
    setLabelText(inDatetime,buffer);

    Label* fee = createLabel();
    setLabelPos(fee,6,5);
    sprintf(buffer,"주차 요금 : %d원",data.fee);
    setLabelText(fee,buffer);

    addLabel(dataWidget,carNum);
    addLabel(dataWidget,name);
    addLabel(dataWidget,phoneNumber);
    addLabel(dataWidget,inDatetime);
    addLabel(dataWidget,fee);

    renderWidget(dataWidget);

    getch();
    
    return HOME;
}