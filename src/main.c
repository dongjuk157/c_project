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

#include "utils.h"
#include "messagebox.h"
#include "login_ui.h"
#include "enroll_ui.h"
#include "setting_ui.h"



static char id[20] = "";

int init();
int setFilePath(char *id);
int backUpFile();
void signalHandler(int sig);

int main(int argc, char const *argv[])
{
    init();

    int quit = 0;
    int page = LOGIN;    
    
    HOME_UI* home = createHomeUI(); //HOME UI
    MANAGE_UI *iomanage = createManageUI(); // 입출차 관리 UI
    PAY_UI *pay = createPayUI(); //정산 관리 UI
    PARKSTATUS_UI *parkStatus = createParkStatusUI(); //주차장 현황 UI
    INFO_UI* info = createInfoUI(); //차량 정보 UI
    HISTORY_UI* history = createHistoryUI(); //주차 이력 UI
    LOGIN_UI* login = createLoginUI(); // 로그인 UI
    ENROLL_UI* enroll = createEnrollUI(); // 회원가입 UI
    SETTING_UI* setting = createSettingUI(); // 주차장 설정 UI
    
    while(!quit){
        switch (page)
        {
        case HOME:
            page = renderHomeUI(home, id);
            break;
        case IOMANAGE:
            page = renderManageUI(iomanage, id);
            break;
        case PAY:
            page = renderPayUI(pay, id);
            break;
        case PARKSTATUS:
            page = renderParkStatusUI(parkStatus, id);
            break;
        case CARINFO:
            page = renderInfoUI(info, id);
            break;
        case PARKHISTORY:
            page = renderHistoryUI(history, id);
            break;
        case LOGIN:
            page = renderLoginUI(login,id);
            if(page == HOME){
                setFilePath(id);
            }
            break;
        case ENROLLUSER:
            page = renderEnrollUI(enroll, id);
            break;
        case SETTING:
            page = renderSettingUI(setting, id);
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
    backUpFile();
    
    //자료구조 메모리 해제
    list_clear(&current_list);  
    list_clear(&current_car_list);
    hashDestroy(user);;

    //UI 메모리 해제
    clearWidget(home);
    clearWidget(iomanage);
    clearWidget(pay);
    clearWidget(parkStatus);
    clearWidget(info);
    clearWidget(history);
    clearWidget(login);
    clearWidget(enroll);
    clearWidget(setting);

    return 0;
}


int init(){
    signal(SIGINT, signalHandler);
    signal(SIGHUP, signalHandler);
    signal(SIGHUP, signalHandler);
    hashCreate(&user);
    if(current_list.magicCode != ERR_LIST_MAGICCODE)
        create_linked_list(&current_list);

    if(current_list.magicCode != ERR_LIST_MAGICCODE)
        create_linked_list(&current_car_list);
    return OK;
}
int setFilePath(char *id) {
    char command[100];
    sprintf(command, "cp -r ./data/%s ./data/tempData", id);
    system(command);

    // user 해시테이블 생성
    readUserData(&user);
    //  current list 생성
    readParkingLot(&current_list);
    // current_car_list 생성
    readCurrentData(&current_car_list);
    return OK;
}
int backUpFile(){
    saveCurrentCarData(current_car_list);
    saveParkingLot(current_list);
    saveUserData(user);
    char command[100];
    if(strcmp(id,"")){
            sprintf(command, "cp ./data/tempData/* ./data/%s",id);
        system(command);
        system("rm -r ./data/tempData");
    }

    return OK;
}
void signalHandler(int sig){
    backUpFile();
    tcsetattr(0, TCSAFLUSH, &savebuf);
    messageBox(NULL,7,17,"프로그램이 종료됩니다.");
    system("clear");
    exit(0);
}


