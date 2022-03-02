#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

// extern int ticketFee;
extern LPHASH user;

//정산하기
int renderFeeView(){

    system("clear");

    Widget *feeView = (Widget *)malloc(sizeof(Widget));

    setWidgetPos(feeView, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(feeView, 25, 70);
    setWidgetType(feeView, MAIN);
    arrayCreate(&(feeView->label));

    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 29);
    setLabelText(subTitle,"주차요금 정산");

    Label *prompt = createLabel();
    setLabelPos(prompt, 10, 10);
    setLabelText(prompt,"차량번호를 입력하세요 >> ");

    addLabel(feeView, title);
    addLabel(feeView, subTitle);
    addLabel(feeView, prompt);

//UI 프레임 그리기
    printWidget(feeView);
    
//세팅된 label 출력
    for (int i = 0; i < arraySize(feeView->label); i++)
        printLabel(feeView, (Label *)(feeView->label->lpData)[i]);
    
    return 0;
}


int printFeeDetailView(char *carNumber, int fee, int hasTicket){

    REPEAT:
    {
    //계산된 fee 출력을 위해 int->string
    char feeStr[10];
    sprintf(feeStr, "%d", fee);

    Widget *feeDetailView = (Widget *)malloc(sizeof(Widget));

    setWidgetPos(feeDetailView, DEFAULT_POSY, DEFAULT_POSX);
    setWidgetSize(feeDetailView, 25, 70);
    setWidgetType(feeDetailView, MAIN);
    arrayCreate(&(feeDetailView->label));

    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 29);
    setLabelText(subTitle, "주차요금 정산");

    Label *label1 = createLabel();
    setLabelPos(label1, 11, 5);
    setLabelText(label1, "정산할 요금은");

    Label *label2 = createLabel();
    setLabelPos(label2, 11, 19);
    setLabelText(label2, feeStr); // hasticket 여부로 *할인율 적용할지 판단

    Label *label3 = createLabel();
    setLabelPos(label3, 11, 24);
    setLabelText(label3, "원 입니다.");

    if(hasTicket){
        Label *label4 = createLabel();
        setLabelPos(label4, 11, 35);
        setLabelText(label4, "(정기권 할인 적용)");
        addLabel(feeDetailView, label4);
    }

    Label *label5 = createLabel();
    setLabelPos(label5, 14, 5);
    setLabelText(label5, "결제하시겠습니까? (Y/N)");

    addLabel(feeDetailView, title);
    addLabel(feeDetailView, subTitle);
    addLabel(feeDetailView, label1);
    addLabel(feeDetailView, label2);
    addLabel(feeDetailView, label3);
    addLabel(feeDetailView, label5);

    system("clear");
//UI 프레임 그리기
    printWidget(feeDetailView);
    
//세팅된 label 출력
    for (int i = 0; i < arraySize(feeDetailView->label); i++)
        printLabel(feeDetailView, (Label *)(feeDetailView->label->lpData)[i]);

//결제 여부 입력
    char prompt[10];
    fgets(prompt, 20, stdin);
    prompt[strlen(prompt) - 1] = '\0';

    if(!strcmp("Y", prompt)){
        
        FILE *ifp = fopen("./data/history.dat","rb");
        FILE *ofp = fopen("./data/history.dat","wb");

        if(ifp == NULL || ofp == NULL){
            return 1;
        }

        CAR_INFO *carInfo = (CAR_INFO *)malloc(sizeof(CAR_INFO));
        // memset(carInfo, 0, sizeof(CAR_INFO));
        //file을 읽어서 carnumber랑 일치하는 carinfo->fee = 0으로 처리해서 파일다시쓰기
        while(fread(carInfo, sizeof(Info), 1, ifp)){
            if(!strcmp(carNumber, carInfo->car_number) && strcmp(carInfo->out_datetime, "xxx"))
                carInfo->fee = 0;
            
            fwrite(carInfo, sizeof(CAR_INFO), 1, ofp);
        }
        free(carInfo);
        fclose(ifp);
        fclose(ofp);

        printSingleLineView("주차요금 정산", "결제가 완료되었습니다!");
    } else if(!strcmp("N", prompt)){
        printSingleLineView("주차요금 정산", "결제가 취소되었습니다!");
        return 0;
    } else{
        goto REPEAT;
    }
    }
    return 0;
}

//정기권 뷰
int renderTicketView(){
    system("clear");

    Widget *ticketView = (Widget *)malloc(sizeof(Widget));

    setWidgetPos(ticketView, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(ticketView, 25, 70);
    setWidgetType(ticketView, MAIN);
    arrayCreate(&(ticketView->label));

    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 26);
    setLabelText(subTitle,"정기권 등록 및 연장");

    Label *prompt = createLabel();
    setLabelPos(prompt, 10, 10);
    setLabelText(prompt,"차량번호를 입력하세요 >> ");

    addLabel(ticketView, title);
    addLabel(ticketView, subTitle);
    addLabel(ticketView, prompt);

//UI 프레임 그리기
    printWidget(ticketView);
    
//세팅된 label 출력
    for (int i = 0; i < arraySize(ticketView->label); i++)
        printLabel(ticketView, (Label *)(ticketView->label->lpData)[i]);
    
    return 0;
}


int renderExtendTicketDetailView(USER_INFO *foundInfo){

    getOneMonthAfterFromDate(foundInfo->recentTicket);

REPEAT:
    system("clear");

    Widget *extendticketDetailView = (Widget *)malloc(sizeof(Widget));

    setWidgetPos(extendticketDetailView, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(extendticketDetailView, 25, 70);
    setWidgetType(extendticketDetailView, MAIN);
    arrayCreate(&(extendticketDetailView->label));

    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 26);
    setLabelText(subTitle,"정기권 등록 및 연장");

    Label *label1 = createLabel();
    setLabelPos(label1, 10, 10);
    setLabelText(label1, foundInfo->name);

    Label *label2 = createLabel();
    setLabelPos(label2, 10, 18);
    setLabelText(label2,"님, 정기권을");


    Label *label3 = createLabel();
    setLabelPos(label3, 10, 24);
    setLabelText(label3, foundInfo->recentTicket);

    Label *label4 = createLabel();
    setLabelPos(label4, 10, 31);
    setLabelText(label4,"까지 연장합니다.");

    Label *label5 = createLabel();
    setLabelPos(label5, 13, 10);
    setLabelText(label5,"결제할 요금은");

    Label *label6 = createLabel();
    setLabelPos(label6, 13, 17);
    setLabelText(label6, "13000");  //나중에 전역변수 활용

    Label *label7 = createLabel();
    setLabelPos(label7, 13, 24);
    setLabelText(label7,"원 입니다.");

    
    Label *label8 = createLabel();
    setLabelPos(label8, 16, 10);
    setLabelText(label8,"결제하시겠습니까? (Y/N)");

    addLabel(extendticketDetailView, title);
    addLabel(extendticketDetailView, subTitle);
    addLabel(extendticketDetailView, label1);
    addLabel(extendticketDetailView, label2);
    addLabel(extendticketDetailView, label3);
    addLabel(extendticketDetailView, label4);
    addLabel(extendticketDetailView, label5);
    addLabel(extendticketDetailView, label6);
    addLabel(extendticketDetailView, label7);
    addLabel(extendticketDetailView, label8);



//UI 프레임 그리기
    printWidget(extendticketDetailView);
    
//세팅된 label 출력
    for (int i = 0; i < arraySize(extendticketDetailView->label); i++)
        printLabel(extendticketDetailView, (Label *)(extendticketDetailView->label->lpData)[i]);
    

    char prompt[10];
    fgets(prompt, 20, stdin);
    prompt[strlen(prompt) - 1] = '\0';

    if(!strcmp("Y", prompt)){
        hashSetValue(user, foundInfo->car_num, foundInfo);
        printSingleLineView("정기권 등록 및 연장", "정기권 연장이 완료되었습니다!");
    } else if(!strcmp("N", prompt)){
        printSingleLineView("정기권 등록 및 연장", "정기권 연장이 취소되었습니다!");
        return 0;
    } else{
        goto REPEAT;
    }


    return 0;
}

int renderNewTicketDetailView(USER_INFO *foundInfo){

    getOneMonthAfterFromToday(foundInfo->recentTicket);

REPEAT:
    system("clear");

    Widget *newticketDetailView = (Widget *)malloc(sizeof(Widget));

    setWidgetPos(newticketDetailView, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(newticketDetailView, 25, 70);
    setWidgetType(newticketDetailView, MAIN);
    arrayCreate(&(newticketDetailView->label));

    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 26);
    setLabelText(subTitle,"정기권 등록 및 연장");

    Label *label1 = createLabel();
    setLabelPos(label1, 10, 8);
    setLabelText(label1, foundInfo->name);

    Label *label2 = createLabel();
    setLabelPos(label2, 10, 14);
    setLabelText(label2,"님, 정기권을");

    Label *label3 = createLabel();
    setLabelPos(label3, 10, 27);
    setLabelText(label3, foundInfo->recentTicket);

    Label *label4 = createLabel();
    setLabelPos(label4, 10, 38);
    setLabelText(label4,"까지 등록합니다");

    Label *label5 = createLabel();
    setLabelPos(label5, 13, 8);
    setLabelText(label5,"결제할 요금은");

    Label *label6 = createLabel();
    setLabelPos(label6, 13, 22);
    setLabelText(label6, "13000");  //나중에 전역변수 활용

    Label *label7 = createLabel();
    setLabelPos(label7, 13, 27);
    setLabelText(label7,"원 입니다.");

    Label *label8 = createLabel();
    setLabelPos(label8, 16, 8);
    setLabelText(label8,"결제하시겠습니까? (Y/N)");

    addLabel(newticketDetailView, title);
    addLabel(newticketDetailView, subTitle);
    addLabel(newticketDetailView, label1);
    addLabel(newticketDetailView, label2);
    addLabel(newticketDetailView, label3);
    addLabel(newticketDetailView, label4);
    addLabel(newticketDetailView, label5);
    addLabel(newticketDetailView, label6);
    addLabel(newticketDetailView, label7);
    addLabel(newticketDetailView, label8);

//UI 프레임 그리기
    printWidget(newticketDetailView);
    
//세팅된 label 출력
    for (int i = 0; i < arraySize(newticketDetailView->label); i++)
        printLabel(newticketDetailView, (Label *)(newticketDetailView->label->lpData)[i]);
    

    char prompt[10];
    fgets(prompt, 20, stdin);
    prompt[strlen(prompt) - 1] = '\0';

    if(!strcmp("Y", prompt)){
        hashSetValue(user, foundInfo->car_num, foundInfo);
        printSingleLineView("정기권 등록", "정기권 등록이 완료되었습니다!");
    } else if(!strcmp("N", prompt)){
        printSingleLineView("정기권 연장", "정기권 등록이 취소되었습니다!");
        return 0;
    } else{
        goto REPEAT;
    }


    return 0;

}


int printSingleLineView(char *currentMenu, char *defaultText){

    system("clear");

    Widget *singleLineView = (Widget *)malloc(sizeof(Widget));

    setWidgetPos(singleLineView, DEFAULT_POSY, DEFAULT_POSX);
    setWidgetSize(singleLineView, 25, 70);
    setWidgetType(singleLineView, MAIN);
    arrayCreate(&(singleLineView->label));

    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 29);
    setLabelText(subTitle, currentMenu);

    Label *label = createLabel();
    setLabelPos(label, 13, 18);
    setLabelText(label, defaultText);

    addLabel(singleLineView, title);
    addLabel(singleLineView, subTitle);
    addLabel(singleLineView, label);

    
//UI 프레임 그리기
    printWidget(singleLineView);
    
//세팅된 label 출력
    for (int i = 0; i < arraySize(singleLineView->label); i++)
        printLabel(singleLineView, (Label *)(singleLineView->label->lpData)[i]);

    char prompt[10];
    fgets(prompt,20,stdin);
    
    system("clear");
    
    return 0;
}

//정기권 뷰
int printSaveUserInfoView(){
    Widget *saveView = (Widget *)malloc(sizeof(Widget));
    setWidgetPos(saveView, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(saveView, 25, 70);
    setWidgetType(saveView, MAIN);
    arrayCreate(&(saveView->label));

    Label *text = createLabel();
    setLabelPos(text, 13, 10);
    setLabelText(text, "해당 차량번호로 조회된 결과가 없습니다.");

    Label *prompt = createLabel();
    setLabelPos(prompt, 16, 10);
    setLabelText(prompt,"이름을 입력하세요 >> ");

    Label *prompt2 = createLabel();
    setLabelPos(prompt2, 19, 10);
    setLabelText(prompt2,"휴대폰 번호를 입력하세요 >> ");

    addLabel(saveView, text);
    addLabel(saveView, prompt);
    addLabel(saveView, prompt2);

//UI 프레임 그리기
    printWidget(saveView);
    
//세팅된 label 출력
    for (int i = 0; i < arraySize(saveView->label); i++)
        printLabel(saveView, (Label *)(saveView->label->lpData)[i]);
    
    return 0;
}
