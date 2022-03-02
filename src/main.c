#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "array.h"
#include "widget.h"
#include "label.h"
#include "home_ui.h"
#include "manage_ui.h"
#include "pay_ui.h"
#include "parkstatus_ui.h"
#include "info_ui.h"
#include "info.h"
#include "history_ui.h"
#include "linkedlist.h"
#include "hash.h"
#include "manage.h"
#include "utils.h"
#include "messagebox.h"
#include "login_ui.h"
#include "enroll_ui.h"
#include "setting_ui.h"

typedef int (*FP)(Widget*);

LPHASH user;
LinkedList current_list;
LinkedList current_car_list;

void signalHandler(int sig){
	
    saveCurrentCarData(current_car_list);
    saveParkingLot(current_list);
    saveUserData(user);
    
    if(messageBox(NULL,"정말로 종료하시겠습니까?")==ID_OK){
        system("clear");
        exit(0);
    }
    
}

int main(int argc, char const *argv[])
{
    // signal(SIGSTOP, signalHandler);
    signal(SIGINT, signalHandler);
    signal(SIGHUP, signalHandler);
    signal(SIGHUP, signalHandler);
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
    
    HOME_UI* home = createHomeUI(); //HOME UI
    MANAGE_UI *iomanage = createManageUI(); // 입출차 관리 UI
    PAY_UI *pay = createPayUI(); //정산 관리 UI
    PARKSTATUS_UI *parkStatus = createParkStatusUI(); //주차장 현황 UI
    INFO_UI* info = createInfoUI(); //차량 정보 UI
    HISTORY_UI* history = createHistoryUI(); //주차 이력 UI
    LOGIN_UI* login = createLoginUI();
    ENROLL_UI* enroll = createEnrollUI();
    SETTING_UI* setting = createSettingUI();

    mainPage = home;
    render = renderHomeUI;

    int quit = 0;
    int page = LOGIN;
    
    while(!quit){
        page = render(mainPage);
        switch (page)
        {
        case HOME:
            mainPage = home;
            render = renderHomeUI;
            break;
        case IOMANAGE:
            mainPage = iomanage;
            render = renderManageUI;
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
            while (1){
                system("clear");
                int menu_no, break_flag=0;
                printf("1. user.dat 2. current.dat 3.history.dat 4.parkinglot.dat\n");
                printf("5. current_list 6. current_car_list others. back");
                scanf("%d", &menu_no); while(getchar()!='\n');
                switch (menu_no){
                    case 1:
                        printUserData();
                        getchar();
                        break;
                    case 2:
                        printCurrentData();
                        getchar();
                        break;
                    case 3:
                        printHistoryData();
                        getchar();
                        break;
                    case 4:
                        printParkingLotData();
                        getchar();
                        break;
                    case 5:
                        printCurrentParkList();
                        getchar();
                        break;
                    case 6:
                        printCurrentCarList();
                        getchar();
                        break;
                    default:
                        break_flag = 1;
                        break;
                }
                if (break_flag){
                    break;
                }
            }
            page = HOME;
            break;
        case EXIT:
            if(messageBox(NULL,"정말로 종료하시겠습니까?") == ID_OK){
                quit = True;
                system("clear");
            }   
            break;
        default:
            break;
        }
    }

    // 데이터 백업
    saveCurrentCarData(current_car_list);
    saveParkingLot(current_list);
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
