#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pay_ui.h"
#include "info.h"
#include "view.h"

extern LPHASH user;

// 결제하기 기능 선택시 나타날 UI 제작 -> 제작한 Widget 구조체의 포인터 리턴
PAY_UI *createPayUI(){

    PAY_UI *payUI = (PAY_UI *)malloc(sizeof(PAY_UI));

    // 기본 위젯 Position 세팅
    setWidgetPos(payUI, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(payUI, 25, 70);
    setWidgetType(payUI, MAIN);
    arrayCreate(&(payUI->label));

    // Label 세팅
    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 31);
    setLabelText(subTitle,"결제 기능");

    Label *selectOne = createLabel();
    setLabelPos(selectOne, 13, 10);
    setLabelText(selectOne,"1. 주차요금 정산");

    Label *selectTwo = createLabel();
    setLabelPos(selectTwo, 16, 10);
    setLabelText(selectTwo,"2. 정기권 등록 및 연장");

    Label *prompt = createLabel();
    setLabelPos(prompt, 20, 10);
    setLabelText(prompt,"기능을 선택하세요 >> ");

    // 세팅한 Label Widget.label 동적 배열에 담기
    addLabel(payUI, title);
    addLabel(payUI, subTitle);
    addLabel(payUI, selectOne);
    addLabel(payUI, selectTwo);
    addLabel(payUI, prompt);

    return payUI;
}

int renderPayUI(PAY_UI *pay){

    REPEAT:
    {
    //UI 프레임 그리기
    renderWidget(pay);
    
    //세팅된 label 출력
    for (int i = 0; i < arraySize(pay->label); i++)
        printLabel(pay, (Label *)(pay->label->lpData)[i]);

    //prompt로 받을 선택넘버 | exit - home | 1,2 - 각 Page로 | 이외 - 다시입력 |
    char selectNumber[8];

    //User에게 입력받고 개행문자 제거
    fgets(selectNumber, 8, stdin);
    selectNumber[strlen(selectNumber)-1] = '\0';
    
    if(!strcmp("exit", selectNumber))
        return HOME;

    int num = atoi(selectNumber);
    if(num == 1){
        //ParkingFee // 1번을 선택한 상황
        payParkingFee();
        
    } else if(num == 2){
        //buyTicket
        buyTicket();

    } else{
        system("clear");
        goto REPEAT;
    }
    }
    return HOME;
}


// 정산하기
int payParkingFee(){
    //fee view load
    printFeeView();

    //차량번호 입력받기
    char carNumber[20];

    fgets(carNumber,20,stdin);
    carNumber[strlen(carNumber)-1] = '\0';

    calcFee(carNumber);

    return 0;
}

int calcFee(char *carNumber){
    
    FILE *fp = fopen("./data/history.dat","rb");
    if(fp == NULL){
        return 1;
    }

    CAR_INFO *carInfo = (CAR_INFO *)malloc(sizeof(CAR_INFO));
    
    int fee = 0;
    //History.dat file 검색하면서 입력받은 carnumber와 일치하는 구조체들 
    while(fread(carInfo, sizeof(CAR_INFO), 1, fp)){
        if(!strcmp(carNumber, carInfo->car_number) && (strcmp(carInfo->out_datetime, "xxx"))){  
            fee += carInfo->fee;
        }
    }
    free(carInfo);

    //carNumber와 일치하는 user 찾기 -> hash? 이게 되면 할인권 적용 가능
    int hasTicket = 1;

    fclose(fp);

    if(fee == 0){
        printSingleLineView("주차요금 정산", "미정산 요금이 없습니다!");
    } else{
        printFeeDetailView(carNumber, fee, hasTicket);
    }

     
    return 0;
}

//정기권 등록

int buyTicket(){

//fee view load
    printTicketView();

    //차량번호 입력받기
    char carNumber[20];

    fgets(carNumber,20,stdin);
    carNumber[strlen(carNumber)-1] = '\0';

    /*
    1. user.dat 의 car_num이 존재 하지 않는다 -> 등록된 차량 정보 없습니다. 이름 , 번호, 차량종류 입력받기
    2. user.dat 의 car_num 존재 -> char *recentTicekt값 체크 "" 이면 등록하시겠습니까
    3. user.dat 의 car_num 존재 -> char *recentTicket값 체크 "2022-02-20" 시간과 현재 시간 차이 계산
                                4일 남았습니다 연장하시겠습니까? 하면 20일 기준 30일 뒤로 등록
     */
    USER_INFO *foundInfo;
    hashGetValue(user, carNumber, &foundInfo);

    if(foundInfo == NULL){  //차량번호 조회불가
        //save data
        saveUser(carNumber, &foundInfo);

    }  //번호 조회함
    if (strcmp(foundInfo->recentTicket, "")==0){ // 이전 데이터 값에 null이 들어있는 경우
        strcpy(foundInfo->recentTicket, "0000-00-00");
    }

    
        // "0000-00-00"  -> 재등록
        // "2022-03-01"  -> 재등록 
        // "2022-03-03"  -> 연장
    
    return 0;
}

//foundInfo -> recentTicket의 날짜확인
int checkRecentTicket(USER_INFO *foundInfo){    
}

int extendTicket(){
}

int newTicket(){
}


int saveUser(char *carNumber, USER_INFO **foundInfo){
    printSaveUserInfoView();
    // user_data에 값 저장
    char tmp;
    // printf("차주 이름 >> ");
    scanf("%s", (*foundInfo)->name); while((tmp=getchar())!='\n');
    // printf("차주 휴대폰 번호 >> ");
    scanf("%s", (*foundInfo)->phone_num); while((tmp=getchar())!='\n');
    // 차량 번호 자동 저장
    strcpy((*foundInfo)->car_num, carNumber);
    // 정기권 없음
    (*foundInfo)->has_ticket = 0;
    strcpy((*foundInfo)->recentTicket, "0000-00-00");
    // 해시 테이블에 저장
    hashSetValue(user, carNumber, *foundInfo);

    return 0;
}