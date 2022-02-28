#include <stdio.h>
#include "array.h"
#include "widget.h"
#include "label.h"
#include "home_ui.h"
#include "pay_ui.h"
#include "info_ui.h"
#include "info.h"
// #include "history_ui.h"
#include <stdlib.h>
#include <unistd.h>

typedef int (*FP)(Widget*);


int main(int argc, char const *argv[])
{
    void *currentPage;
    FP render;
    
    HOME_UI* home = createHomeUI();
    PAY_UI *pay = createPayUI();
    INFO_UI* info = createInfoUI();
    // HISTORY_UI* history = createHistoryUI();
    // Info buf;

    currentPage = home;
    render = renderHomeUI;

    int page = 0;
    
    while(1){
        system("clear");
        page = render(currentPage);
        switch (page)
        {
        case HOME:
            currentPage = home;
            render = renderHomeUI;
            break;
        case PAY:
            currentPage = pay;
            render = renderPayUI;
        case CARINFO:
            currentPage = info;
            render = renderInfoUI;
            break;
        case PARKHISTORY:
            // mainPage = history;
            // render = renderHistoryUI;
            // break;
        case 6:
            // printf("차량번호 >> ");
            // scanf("%s",buf.carNumber);
            // printf("이름 >> ");
            // scanf("%s",buf.name);
            // printf("연락처 >> ");
            // scanf("%s",buf.phoneNumber);
            // sprintf(buf.inDatetime,"2022년 02월 27일 13시 27분");
            // buf.fee = 0;

            // FILE* fp;
            // fp = fopen("data/Current.dat","ab");
            // if(fp == NULL){
            //     return 0;
            // }
            // fwrite(&buf,sizeof(Info),1,fp);
            // fclose(fp);
            // page = HOME;
            // break;
        case EXIT:
            return 0;
        default:
            break;
        }
    }

    

    free(home);
    // free(info);
    // free(history);

    return 0;
}
