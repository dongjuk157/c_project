#include "history_ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HISTORY_UI* createHistoryUI(){

    HISTORY_UI* history = (HISTORY_UI*)malloc(sizeof(HISTORY_UI));
    setWidgetPos(history, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(history, 25, 70);
    setWidgetType(history, MAIN);
    arrayCreate(&(history->label));

    Label* title = createLabel();
    setLabelPos(title,5, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label* subTitle = createLabel();
    setLabelPos(subTitle,7,28);
    setLabelText(subTitle,"주차 이력 조회");

    Label* carNumber = createLabel();
    setLabelPos(carNumber,12,10);
    setLabelText(carNumber,"1. 차량 번호로 조회");

    Label* notPaid = createLabel();
    setLabelPos(notPaid,12, 40);
    setLabelText(notPaid,"2. 미정산 이력 조회");

    Label* inDate = createLabel();
    setLabelPos(inDate,16,10);
    setLabelText(inDate,"3. 날짜별 조회(입차)");

    Label* outDate = createLabel();
    setLabelPos(outDate,16,40);
    setLabelText(outDate,"4. 날짜별 조회(출차)");

    Label* input = createLabel();
    setLabelPos(input, 20, 10);
    setLabelText(input,"조회 방식 입력 >> ");


    addLabel(history, title);
    addLabel(history, subTitle);
    addLabel(history, carNumber);
    addLabel(history, notPaid);
    addLabel(history, inDate);
    addLabel(history, outDate);
    addLabel(history,input);

    return history;
}

// int checkinit(char *init){
//     if(!strcmp("exit", init)) return EXIT;
//     else{
//         int num = atoi(init);
//         return num;
//     }
// }

int renderHistoryUI(HISTORY_UI* history){
    printWidget(history);
    char init[20];
    for (int i = 0; i < arraySize(history->label); i++)
    {
        printLabel(history,(Label *)(history->label->lpData)[i]);
    }

    fgets(init,20,stdin);
    init[strlen(init)-1] = '\0';

    // int sel = checkinit(init);
    // Label* input = createLabel();

    // switch (sel)
    // {
    // case EXIT:
    //     return HOME;
    //     break;
    // case 1:
    //     setLabelPos(input, 10, 10);
    //     setLabelText(input,"차량번호 입력(띄어쓰기 X) >> ");
    //     printLabel(history, input);
    //     break;
    // case 2:
    //     break;
    // case 3:
    //     break;
    // case 4:
    //     break;
    // default:
    //     break;
    // }
    
    return HOME;
}