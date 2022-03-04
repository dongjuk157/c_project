#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "info.h"
#include "utils.h"

// extern LPHASH user;

//할인율
float ticketDisc = 0.5; //
float elecDisc = 0.9;
float lightDisc = 0.7;
char ticketFee[6] = "13000";

//정산하기
int renderFeeView(){

    system("clear");

    Widget *feeView = createMainWidget(DEFAULT_POSY,DEFAULT_POSX,25,70);

    labelAdd(feeView,3,26,"주차 관리 프로그램",0);
    labelAdd(feeView,5,29,"주차요금 정산",0);
    labelAdd(feeView,10,10,"차량번호를 입력하세요 >> ",0);

//UI 프레임 그리기
    renderWidget(feeView);
    
    return OK;
}


int printFeeDetailView(char *carNumber, int fee, int hasTicket, CAR_INFO* carinfo){

    char feeStr[10];
    if(hasTicket){
        sprintf(feeStr, "%d", (int)(fee * ticketDisc));
    }
    else if(carinfo->car_type == 'e'){
        sprintf(feeStr, "%d", (int)(fee * elecDisc));
    }
    else if(carinfo->car_type == 'l'){
        sprintf(feeStr, "%d", (int)(fee * lightDisc));
    }
    else{
        sprintf(feeStr, "%d", fee);
    }

    Widget *feeDetailView = createMainWidget(DEFAULT_POSY, DEFAULT_POSX,25,70);

    labelAdd(feeDetailView,3,26,"주차 관리 프로그램",0);
    labelAdd(feeDetailView,5,29,"주차요금 정산",0);
    labelAdd(feeDetailView,11,5,"정산할 요금은",0);
    labelAdd(feeDetailView,11,19, feeStr,0);
    labelAdd(feeDetailView,11,24, "원 입니다.",0);

    if(hasTicket){ //할인율 적용
        labelAdd(feeDetailView,11,35,"(정기권 할인 적용)",0);
    }
    else if(carinfo->car_type == 'e'){ //할인율 적용
        labelAdd(feeDetailView,11,35,"(전기차 할인 적용)",0);
    }
    else if(carinfo->car_type == 'l'){ //할인율 적용
        labelAdd(feeDetailView,11,35,"(경차 할인 적용)",0);
    }

    labelAdd(feeDetailView,14,5,"결제하시겠습니까? (Y/N)",0);

    renderWidget(feeDetailView);

    char prompt[10];
    myGetline(prompt, 20, stdin);

    if(!strcmp("Y", prompt)){
        // 복사
        // cp History.dat History.tmp.dat
        char command[100];
        strcpy(command, "cp ");
        strcat(command, HISTORY_DATA_FILE_PATH);
        strcat(command, " ");
        strcat(command, HISTORY_TMP_DATA_FILE_PATH);
        system(command);

        FILE *fp_r = fopen(HISTORY_TMP_DATA_FILE_PATH,"rb");
        if(!fp_r) 
            return FILE_ERROR;

        FILE *fp_w = fopen(HISTORY_DATA_FILE_PATH,"wb");
        if(!fp_w) 
            return FILE_ERROR;

        CAR_INFO *carInfo = (CAR_INFO *)malloc(sizeof(CAR_INFO));

        //file을 읽어서 carnumber랑 일치하는 carinfo->fee = 0으로 처리해서 파일다시쓰기
        while(1){
            fread(carInfo, sizeof(CAR_INFO), 1, fp_r);
            if(feof(fp_r))
                break;
            if(!strcmp(carNumber, carInfo->car_number) && strcmp(carInfo->out_datetime, "")){
                // carInfo->fee = fee;
                carInfo->is_paid = 1;
            }
            // fseek(ifp,-sizeof(CAR_INFO),SEEK_CUR);
            fwrite(carInfo, sizeof(CAR_INFO), 1, fp_w);
        }
        free(carInfo);
        fclose(fp_w);
        fclose(fp_r);
        // 임시파일 삭제
        command[0] = '\0';
        strcpy(command, "rm ");
        strcat(command, HISTORY_TMP_DATA_FILE_PATH);
        system(command);

        printSingleLineView("주차요금 정산", "결제가 완료되었습니다!");
    } else if(!strcmp("N", prompt)){
        printSingleLineView("주차요금 정산", "결제가 취소되었습니다!");
        return OK;
    } else{
        return OK;
    }
    return OK;
}

//정기권 뷰
int renderTicketView(){
    Widget *ticketView = createMainWidget(0,0,25,70);

    labelAdd(ticketView,3,26,"주차 관리 프로그램",0);
    labelAdd(ticketView,5,26,"정기권 등록 및 연장",0);
    labelAdd(ticketView,10,10,"차량번호를 입력하세요 >> ",0);

//UI 프레임 그리기
    renderWidget(ticketView);
    
//세팅된 label 출력
    return OK;
}


int renderExtendTicketDetailView(USER_INFO *foundInfo){

    getOneMonthAfterFromDate(foundInfo->recentTicket);

    system("clear");

    Widget *extendticketDetailView = createMainWidget(0,0,25,70);

    labelAdd(extendticketDetailView,3,26,"주차 관리 프로그램",0);
    labelAdd(extendticketDetailView,5,26,"정기권 등록 및 연장",0);
    labelAdd(extendticketDetailView,10,8,foundInfo->name,0);
    labelAdd(extendticketDetailView,10,14,"님, 정기권을",0);
    labelAdd(extendticketDetailView,10,27,foundInfo->recentTicket,0);
    labelAdd(extendticketDetailView,10,38,"까지 연장합니다.",0);
    labelAdd(extendticketDetailView,13,8,"결제할 요금은",0);
    labelAdd(extendticketDetailView,13,22,ticketFee,0);
    labelAdd(extendticketDetailView,13,27,"원 입니다.",0);
    labelAdd(extendticketDetailView,16,8,"결제하시겠습니까? (Y/N)",0);

//UI 프레임 그리기
    renderWidget(extendticketDetailView);
    
    char prompt[10];
    myGetline(prompt, 20, stdin);

    if(!strcmp("Y", prompt)){
        foundInfo->has_ticket = 1;
        hashSetValue(user, foundInfo->car_num, foundInfo);
        printSingleLineView("정기권 연장", "정기권 연장이 완료되었습니다!");
    } else if(!strcmp("N", prompt)){
        printSingleLineView("정기권 연장", "정기권 연장이 취소되었습니다!");
        return OK;
    } else{
        return OK;
    }
    return OK;
}

int renderNewTicketDetailView(USER_INFO *foundInfo){

    getOneMonthAfterFromToday(foundInfo->recentTicket);

    system("clear");

    Widget *newticketDetailView = createMainWidget(0,0,25,70);

    labelAdd(newticketDetailView,3,26,"주차 관리 프로그램",0);
    labelAdd(newticketDetailView,5,26,"정기권 등록 및 연장",0);
    labelAdd(newticketDetailView,10,8,foundInfo->name,0);
    labelAdd(newticketDetailView,10,14,"님, 정기권을",0);
    labelAdd(newticketDetailView,10,27,foundInfo->recentTicket,0);
    labelAdd(newticketDetailView,10,38,"까지 등록합니다.",0);
    labelAdd(newticketDetailView,13,8,"결제할 요금은",0);
    labelAdd(newticketDetailView,13,22,ticketFee,0);
    labelAdd(newticketDetailView,13,27,"원 입니다.",0);
    labelAdd(newticketDetailView,16,8,"결제하시겠습니까? (Y/N)",0);

//UI 프레임 그리기
    renderWidget(newticketDetailView);
    
//세팅된 label 출력
    char prompt[10];
    myGetline(prompt, 20, stdin);

    if(!strcmp("Y", prompt)){
        foundInfo->has_ticket = 1;
        hashSetValue(user, foundInfo->car_num, foundInfo);
        printSingleLineView("정기권 등록", "정기권 등록이 완료되었습니다!");
    } else if(!strcmp("N", prompt)){
        printSingleLineView("정기권 등록", "정기권 등록이 취소되었습니다!");
        return OK;
    } else{
        return OK;
    }
    return OK;
}


int printSingleLineView(char *currentMenu, char *defaultText){

    Widget *singleLineView = createMainWidget(0,0,25,70);

    labelAdd(singleLineView,3,26,"주차 관리 프로그램",0);
    labelAdd(singleLineView,5,29,currentMenu,0);
    labelAdd(singleLineView,13,18,defaultText,0);

//UI 프레임 그리기
    renderWidget(singleLineView);
    
//세팅된 label 출력
    char prompt[10];
    fgets(prompt,20,stdin);
    
    system("clear");
    
    return OK;
}

//정기권 뷰
int printSaveUserInfoView(){
    Widget *saveView = createMainWidget(0,0,25,70);

    labelAdd(saveView,13,10,"해당 차량번호로 조회된 결과가 없습니다.",0);
    labelAdd(saveView,16,10,"이름을 입력하세요 >> ",0);
    labelAdd(saveView,19,10,"휴대폰 번호를 입력하세요 >> ",0);

//UI 프레임 그리기
    renderWidget(saveView);
    
//세팅된 label 출력
    
    return OK;
}
