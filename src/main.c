#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
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
#include<unistd.h>
#include<termios.h>

typedef int (*FP)(Widget*, void*);

LPHASH user;
LinkedList current_list;
LinkedList current_car_list;
struct termios buf, savebuf;
void *mainPage;
FP render;
char id[20];



char *CURRENT_DATA_FILE_PATH;
char *SIMPLE_LOG_FILE_PATH;    		
char *USER_DATA_FILE_PATH;
char *HISTORY_DATA_FILE_PATH;     		
char *PARKINGLOT_SETTINGS_FILE_PATH;

void signalHandler(int sig){

    saveCurrentCarData(current_car_list);
    saveParkingLot(current_list);
    saveUserData(user);
    tcsetattr(0, TCSAFLUSH, &savebuf);
    messageBox(NULL,7,17,"프로그램이 종료됩니다.");
    system("clear");
    exit(0);
    // if(messageBox(NULL,7,17,"정말로 종료하시겠습니까?")==ID_OK){
    //     system("clear");
    //     exit(0);
    // }
}

void setFilePath(char *id) {
    char *tmp_path = (char*)malloc(sizeof(char)*100);

    CURRENT_DATA_FILE_PATH = (char*)malloc(sizeof(char)*100);
    sprintf(tmp_path, "./data/%s/Current.dat", id);
    strcpy(CURRENT_DATA_FILE_PATH, tmp_path);

    SIMPLE_LOG_FILE_PATH = (char*)malloc(sizeof(char)*100);
    sprintf(tmp_path, "./data/%s/history.log", id);
    strcpy(SIMPLE_LOG_FILE_PATH, tmp_path);

    USER_DATA_FILE_PATH = (char*)malloc(sizeof(char)*100);
    sprintf(tmp_path, "./data/%s/User.dat", id);
    strcpy(USER_DATA_FILE_PATH, tmp_path);

    HISTORY_DATA_FILE_PATH = (char*)malloc(sizeof(char)*100);
    sprintf(tmp_path, "./data/%s/History.dat", id);
    strcpy(HISTORY_DATA_FILE_PATH, tmp_path);

    PARKINGLOT_SETTINGS_FILE_PATH = (char*)malloc(sizeof(char)*100);
    sprintf(tmp_path, "./data/%s/ParkingLot.dat", id);
    strcpy(PARKINGLOT_SETTINGS_FILE_PATH, tmp_path);

   
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

    free(tmp_path);
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, signalHandler);
    signal(SIGHUP, signalHandler);
    signal(SIGHUP, signalHandler);

    
    HOME_UI* home = createHomeUI(); //HOME UI
    MANAGE_UI *iomanage = createManageUI(); // 입출차 관리 UI
    PAY_UI *pay = createPayUI(); //정산 관리 UI
    PARKSTATUS_UI *parkStatus = createParkStatusUI(); //주차장 현황 UI
    INFO_UI* info = createInfoUI(); //차량 정보 UI
    HISTORY_UI* history = createHistoryUI(); //주차 이력 UI
    LOGIN_UI* login = createLoginUI();
    ENROLL_UI* enroll = createEnrollUI();
    SETTING_UI* setting = createSettingUI();

    mainPage = login;
    render = renderLoginUI;

    int quit = 0;
    int page = LOGIN;
    
    while(!quit){
        // page = render(mainPage);
        switch (page)
        {
        case HOME:
            mainPage = home;
            render = renderHomeUI;
            page = renderHomeUI(home, NULL);
            // mainPage = home;
            break;
        case IOMANAGE:
            mainPage = iomanage;
            render = renderManageUI;
            page = renderManageUI(iomanage, NULL);
            // mainPage = iomanage;
            break;
        case PAY:
            mainPage = pay;
            render = renderPayUI;
            page = renderPayUI(pay, NULL);
            // mainPage = pay;
            break;
        case PARKSTATUS:
            mainPage = parkStatus;
            render = renderParkStatusUI;
            page = renderParkStatusUI(parkStatus,NULL);
            break;
        case CARINFO:
            mainPage = info;
            render = renderInfoUI;
            page = renderInfoUI(info,NULL);
            break;
        case PARKHISTORY:
            mainPage = history;
            render = renderHistoryUI;
            page = renderHistoryUI(history,NULL);
            break;
        case LOGIN:
            mainPage = login;
            render = renderLoginUI;
            page = renderLoginUI(login,id);
            if(page == HOME){
                // getchar();
                setFilePath(id);
            }
            
            break;
        case ENROLLUSER:
            mainPage = enroll;
            render = renderEnrollUI;
            page = renderEnrollUI(enroll, id);
            break;
        case SETTING:
            mainPage = setting;
            render = renderSettingUI;
            page = renderSettingUI(setting, id);
            break;
        case 9:
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
            if(messageBox(NULL,7,17,"정말로 종료하시겠습니까?") == ID_OK){
                quit = True;
                system("clear");
            }   
            else{
                page = HOME;
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

    free(CURRENT_DATA_FILE_PATH);
    free(SIMPLE_LOG_FILE_PATH);
    free(USER_DATA_FILE_PATH);
    free(HISTORY_DATA_FILE_PATH);
    free(PARKINGLOT_SETTINGS_FILE_PATH);


    clearWidget(home);
    clearWidget(info);
    clearWidget(history);

    return 0;
}
