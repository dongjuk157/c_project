#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pay_ui.h"
#include "info.h"
#include "view.h"
#include "utils.h"


// extern LPHASH user; 

PAY_UI *createPayUI(){

    PAY_UI *payUI = createMainWidget(DEFAULT_POSY,DEFAULT_POSX,25,70);

    labelAdd(payUI, 3,26, "주차 관리 프로그램",0);
    labelAdd(payUI, 5,31, "결제 기능",0);
    labelAdd(payUI, 13,10, "1. 주차요금 정산",0);
    labelAdd(payUI, 16,10, "2. 정기권 등록 및 연장",0);
    labelAdd(payUI, 20,10, "기능을 선택하세요 >> ",0);

    return payUI;
}

int renderPayUI(PAY_UI *pay, void *data){
    //UI 프레임 그리기
    renderWidget(pay);

    char selectNumber[8];
    myGetline(selectNumber, 8, stdin);
    
    if(!strcmp("exit", selectNumber)) return HOME;
    
    if(!strcmp("1", selectNumber)){
        payParkingFee();   //주차요금 정산 선택
    } else if(!strcmp("2", selectNumber)){
        buyTicket(); //정기권 등록 및 연장 선택
    } else{
        system("clear");
    }
    return OK;
}
// 정산하기
int payParkingFee(){
    //fee view load
    renderFeeView();
    //차량번호 입력받기
    char carNumber[20];
    myGetline(carNumber,20,stdin);

    calcFee(carNumber);

    return OK;
}

int calcFee(char *carNumber){
    
    FILE *fp = fopen(HISTORY_DATA_FILE_PATH,"rb");
    if(fp == NULL){
        gotoxy(10, 20);
        printf("주차된 차량번호가 아닙니다!");
        getchar();
        return FILE_ERROR;
    }

    CAR_INFO *carInfo = (CAR_INFO *)malloc(sizeof(CAR_INFO));
    
    int fee = 0;
    //History.dat file 검색하면서 입력받은 carnumber와 일치하는 구조체들 
    while(fread(carInfo, sizeof(CAR_INFO), 1, fp)){
        if(!strcmp(carNumber, carInfo->car_number) && (strcmp(carInfo->out_datetime, ""))){  
            if(!carInfo->is_paid)
                fee += carInfo->fee;
        }
    }
    free(carInfo);

    //차번호로 user.dat조회 -> 정기권 여부 판단
    int hasTicket = 0;
    USER_INFO *foundInfo = NULL;
    hashGetValue(user, carNumber, (LPDATA *)&foundInfo);
    if(foundInfo != NULL){  //차량번호 일치하는 user 찾음
        if(foundInfo->has_ticket){
            hasTicket = 1;
        }
    }
    fclose(fp);

    if(fee == 0){
        printSingleLineView("주차요금 정산", "미정산 요금이 없습니다!");
        return OK;
    } else{
        printFeeDetailView(carNumber, fee, hasTicket, carInfo);
        return OK;
    }
    return OK;
}

//정기권 등록
int buyTicket(){
    //ticket view load
    renderTicketView();

    //차량번호 입력받기
    char carNumber[20];
    myGetline(carNumber,20,stdin);

    USER_INFO *foundInfo = NULL;
    hashGetValue(user, carNumber, (LPDATA *)&foundInfo);
    if(foundInfo == NULL){  //차량번호 조회불가
        saveUser(carNumber, &foundInfo);
    }  //번호 조회함
    
    if (strcmp(foundInfo->recentTicket, "")==0){ // 이전 데이터 값에 null이 들어있는 경우
        strcpy(foundInfo->recentTicket, "0000-00-00");
    }
    checkRecentTicket(foundInfo);
    return OK;
}

//foundInfo -> recentTicket의 날짜확인
int checkRecentTicket(USER_INFO *foundInfo){

    char today[20];
    getTodayDate(today);
    if(strcmp(foundInfo->recentTicket, today) >= 0){
        extendTicket(foundInfo);
        return OK;
    } else{
        newTicket(foundInfo);
        return OK;
    }
    return OK;
}

int extendTicket(USER_INFO *foundInfo){

    gotoxy(11, 13);
    printf("현재 %s님의 정기권 만료일은 %s일 입니다.\n", foundInfo->name, foundInfo->recentTicket);
    gotoxy(11, 15);
    printf("연장하시겠습니까? (Y/N)");

    char buf[4];
    myGetline(buf, 4, stdin);

    if(!strcmp("Y", buf)){
        renderExtendTicketDetailView(foundInfo);
    } else if(!strcmp("N", buf)){
        return OK;
    } else{
        return OK;
    }
    return OK;
}

int newTicket(USER_INFO *foundInfo){
    gotoxy(11, 13);
    printf("%s님,\n", foundInfo->name);
    gotoxy(11, 15);
    printf("정기권을 등록하시겠습니까? (Y/N)");

    char buf[4];
    myGetline(buf, 4, stdin);

    if(!strcmp("Y", buf)){
        renderNewTicketDetailView(foundInfo);
    } else if(!strcmp("N", buf)){
        return OK;
    } else{
        return OK;
    }
    return OK;
}

int saveUser(char *carNumber, USER_INFO **foundInfo){
    Widget *saveView = createMainWidget(0,0,25,70);

    printSiglelineWidget(saveView, 12, 10, "해당 차량번호로 조회된 결과가 없습니다.", 0);
    
    *foundInfo = (USER_INFO *) malloc(sizeof(USER_INFO));
    // user_data에 값 저장

    printSiglelineWidget(saveView, 16, 10, "이름을 입력하세요 >> ", 0);
    scanf("%s", (*foundInfo)->name); while(getchar()!='\n');

    printSiglelineWidget(saveView, 18, 10, "휴대폰 번호를 입력하세요 >> ", 0);
    scanf("%s", (*foundInfo)->phone_num); while(getchar()!='\n');
    
    // 차량 번호 자동 저장
    strcpy((*foundInfo)->car_num, carNumber);
    // 정기권 없음
    (*foundInfo)->has_ticket = 0;

    strcpy((*foundInfo)->recentTicket, "0000-00-00");
    // 해시 테이블에 저장
    hashSetValue(user, carNumber, *foundInfo);

    system("clear");

    Widget *defaultView = createMainWidget(0,0,25,70);
    renderWidget(defaultView);

    return OK;
}
