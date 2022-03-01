#include <stdio.h>
#include "array.h"
#include "widget.h"
#include "label.h"
#include "home_ui.h"
#include "info_ui.h"
#include "info.h"
#include "history_ui.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <unistd.h>

typedef int (*FP)(Widget*);


int main(int argc, char const *argv[])
{
    void *mainPage;
    FP render;
    
    HOME_UI* home = createHomeUI();
    INFO_UI* info = createInfoUI();
    HISTORY_UI* history = createHistoryUI();
    Info buf;

    mainPage = home;
    render = renderHomeUI;

    int page = 0;
    
    while(1){
        page = render(mainPage);
        switch (page)
        {
        case HOME:
            mainPage = home;
            render = renderHomeUI;
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
            return 0;
        default:
            break;
        }
    }

  
    

    clearWidget(home);
    clearWidget(info);
    clearWidget(history);

    return 0;
}
