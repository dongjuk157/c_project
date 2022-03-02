#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "array.h"
#include "widget.h"
#include "label.h"
#include "home_ui.h"
// #include "manage_ui.h"
#include "pay_ui.h"
#include "parkstatus_ui.h"
#include "info_ui.h"
#include "info.h"
#include "history_ui.h"
#include "linkedlist.h"
#include "hash.h"
#include "manage.h"

typedef int (*FP)(Widget*);

LPHASH user;
LinkedList current_list;
LinkedList current_car_list;

int main(int argc, char const *argv[])
{
    // user 해시테이블 생성
    // LPHASH user;
    hashCreate(&user); 
    readUserData(&user);

    //  current list 생성
    create_linked_list(&current_list);
    readParkingLot(&current_list);

    // current_car_list 생성
    create_linked_list(&current_car_list);
    readCurrentData(&current_car_list);

    void *mainPage;
    FP render;
    
    HOME_UI* home = createHomeUI();
    // MANAGE_UI *iomanage = createManageUI();
    PAY_UI *pay = createPayUI();
    PARKSTATUS_UI *parkStatus = createParkStatusUI();
    INFO_UI* info = createInfoUI();
    HISTORY_UI* history = createHistoryUI();
    Info buf;

    mainPage = home;
    render = renderHomeUI;

    int page = 0, err_no, break_sig;
    char tmp;
    
    while(1){
        page = render(mainPage);
        switch (page)
        {
        case HOME:
            mainPage = home;
            render = renderHomeUI;
            break;
        case IOMANAGE:
            // page = manage_in_out(user, &current_list, &current_car_list);
            // mainPage = iomanage;
            // render = renderManageUI;
            break;
        case PAY:
            mainPage = pay;
            render = renderPayUI;
            break;
        case PARKSTATUS:
            mainPage = parkStatus;
            render = renderParkStatusUI;
            break;
        case CARINFO:
            mainPage = info;
            render = renderInfoUI;
            break;
        case PARKHISTORY:
            mainPage = history;
            render = renderHistoryUI;
            break;
        case 6:
            printf("차량번호 >> ");
            scanf("%s",buf.carNumber);
            printf("이름 >> ");
            scanf("%s",buf.name);
            printf("연락처 >> ");
            scanf("%s",buf.phoneNumber);
            sprintf(buf.inDatetime,"2022년 02월 27일 13시 27분");
            buf.fee = 0;

            FILE* fp;
            fp = fopen("data/Current.dat","ab");
            if(fp == NULL){
                return 0;
            }
            fwrite(&buf,sizeof(Info),1,fp);
            fclose(fp);
            page = HOME;
            break;
        case EXIT:
            break_sig = 1;
            break;
            // return 0;
        default:
            break;
        }
        if (break_sig){
            break;
        }
    }

    // data 백업
    // 1. current_list -> ParkingLot.dat
    printf("Backup current_list\n");
    FILE *fp = fopen(PARKINGLOT_SETTINGS_FILE_PATH, "wb");
    Node *cur;
    cur = current_list.head;
    while (cur){
        fwrite(((PARK *)cur->data), sizeof(PARK), 1, fp);
        cur = cur->next;
    }
    fclose(fp);
    
    // 2. current_car_list -> Current.dat
    printf("Backup current_car_list\n");
    fp = fopen(CURRENT_DATA_FILE_PATH, "wb");
    cur = current_car_list.head;
    while (cur){
        fwrite(((CAR_INFO *)cur->data), sizeof(CAR_INFO), 1, fp);
        cur = cur->next;
    }
    fclose(fp);

    
    // 3. user_table -> User.dat
    saveUserData(user);


    // 메모리 해제
    list_clear(&current_list);  
    list_clear(&current_car_list);
    hashDestroy(user);


    clearWidget(home);
    clearWidget(info);
    clearWidget(history);

    return 0;
}
