#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "linkedlist.h"
#include "hash.h"
#include "manage.h"
#include "manage_ui.h"
#include "manage_detail.h"
#include "info.h"

extern LPHASH user;
extern LinkedList current_list;
extern LinkedList current_car_list;


// 결제하기 기능 선택시 나타날 UI 제작 -> 제작한 Widget 구조체의 포인터 리턴
MANAGE_UI* createManageUI(){

    MANAGE_UI *manage = createWidget();

    // 기본 위젯 Position 세팅
    setWidgetPos(manage, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(manage, 25, 70);
    setWidgetType(manage, MAIN);

    // Label 세팅
    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 30);
    setLabelText(subTitle,"입출차 관리");

    Label *selectOne = createLabel();
    setLabelPos(selectOne, 13, 10);
    setLabelText(selectOne,"1. 입차");

    Label *selectTwo = createLabel();
    setLabelPos(selectTwo, 16, 10);
    setLabelText(selectTwo,"2. 출차");

    Label *prompt = createLabel();
    setLabelPos(prompt, 20, 10);
    setLabelText(prompt,"기능을 선택하세요 >> ");

    // 세팅한 Label Widget.label 동적 배열에 담기
    addLabel(manage, title);
    addLabel(manage, subTitle);
    addLabel(manage, selectOne);
    addLabel(manage, selectTwo);
    addLabel(manage, prompt);

    return manage;
}

int renderManageUI(MANAGE_UI *manage){
    //UI 프레임 그리기
    CAR_INFO* car_info = NULL;
    USER_INFO* user_info = NULL;

    renderWidget(manage);

    //prompt로 받을 선택넘버 | exit - home | 1,2 - 각 Page로 | 이외 - 다시입력 |
    char selectNumber[8];

    //User에게 입력받고 개행문자 제거
    fgets(selectNumber, 8, stdin);
    selectNumber[strlen(selectNumber)-1] = '\0';
    
    if(!strcmp("exit", selectNumber)){
        return HOME;
    }
    else{
        int num = atoi(selectNumber);
        MANAGE_DETAIL_UI* detail;
        if(num == 1){
            // 입차
            detail = createManageDetailUI(IN_CAR);
            renderWidget(detail);
            getValuesUI(manage,IN_CAR,&car_info);
            save_log(IN_CAR, car_info);
            searchUserUI(manage, car_info->car_number, &user_info, 'i');
            update_current(IN_CAR, car_info, &current_list, &current_car_list); // 5. add current list 
            update_history(IN_CAR, car_info, user_info); // 6. add history
            

            // Node *tmp = current_list.head;
            // while(tmp){
            //     PARK* buf = (PARK*)tmp->data;
            //     if(buf->floor == car_info->floor){
            //         buf->total_car+=1;
            //         break;
            //     }
            //     tmp = tmp->next;
            // }

            gotoxy(10,20);
            printf("새로운 차량이 입차 정상적으로 입차 되었습니다.\n");
            getchar();

        } 
        else if(num == 2){
            // 출차
            detail = createManageDetailUI(OUT_CAR);
            renderWidget(detail);
            getValuesUI(manage,OUT_CAR,&car_info);
            int res;
            res = searchUserUI(manage, car_info->car_number, &user_info , 'o');
            if(res == -2){
                printSiglelineWidget(manage,18,10,"해당 차량 정보가 존재하지 않습니다...");
                getchar();
                return HOME;
            }

            save_log(OUT_CAR, car_info);
            update_current(OUT_CAR, car_info, &current_list, &current_car_list); // 5. add current list 
            update_history(OUT_CAR, car_info, user_info); // 6. add history
            
            gotoxy(10,20);
            printf("정상적으로 출차 되었습니다.\n");
            getchar();
        } 
        else{
            return IOMANAGE;
        }
    }

    
    return HOME;
}

int getValuesUI(MANAGE_UI* manage, char io, CAR_INFO **car_info){

    *car_info = (CAR_INFO*) malloc(sizeof(CAR_INFO));

    Label temp;
    labelCreate(&temp);
    if(io == 'i'){
        getDateTime((*car_info)->in_datetime);
        
        setLabelPos(&temp,8,10);
        setLabelText(&temp,"차량 번호(123가1234)>> ");
        printLabel(manage,&temp);
        fgets((*car_info)->car_number, 20, stdin);
        (*car_info)->car_number[strlen((*car_info)->car_number)-1] = '\0';

        setLabelPos(&temp,10,10);
        setLabelText(&temp,"차종 [e]lectric, [l]ight, [n]ormal >> ");
        printLabel(manage,&temp);
        scanf("%c", &(*car_info)->car_type); while(getchar()!='\n');

        switch ((*car_info)->car_type) {
            case 'e': case 'l':
                break;
            default:
                (*car_info)->car_type = 'n';
                break;
        }
        
        setLabelPos(&temp,12,10);
        setLabelText(&temp,"주차 위치(층수 입력) >> ");
        printLabel(manage,&temp);
        scanf("%d", &(*car_info)->floor); while(getchar()!='\n');

        int find_flag = 0;
        Node *tmp = current_list.head;
        while(tmp){
            PARK* buf = (PARK*)tmp->data;
            if(buf->floor == (*car_info)->floor){
                find_flag = 1;      // 찾으면 flag = 1

                if (buf->total_car < buf->total){ // total_car: 현재 주차된 차량 < total:주차공간 
                    buf->total_car+=1;  // 해당 층의 자동차 수 하나 증가
                }
                else {
                    return -4; // 자동차 수 초과
                }
                break; // 
            }
            tmp = tmp->next;
        }
        if (!find_flag) {  // 해당 층이 등록되지 않은 경우
            return -3; // there is not enrolled floor.
        }
    }
    else if(io == 'o'){
        setLabelPos(&temp,14,10);
        setLabelText(&temp,"차량 번호(123가1234)>> ");
        printLabel(manage,&temp);
        fgets((*car_info)->car_number, 20, stdin);
        (*car_info)->car_number[strlen((*car_info)->car_number)-1] = '\0';

    }
    else {
        return 0;
    }

    return 0;
}

int searchUserUI(MANAGE_UI* manage,  char *car_number, USER_INFO **user_data, char io){
    USER_INFO *tmp_user = NULL;
    hashGetValue(user, car_number, (LPDATA*)&tmp_user);
    *user_data = (USER_INFO *) malloc(sizeof(USER_INFO));
    if ((tmp_user) == NULL){ // hash 값이 없는 경우
        if (io == 'i'){
            saveUserUI(manage, car_number, user_data);
        }
        return -2; // NOT SEARCH USER
    }
    else {
        strcpy((*user_data)->name, tmp_user->name);
        strcpy((*user_data)->phone_num, tmp_user->phone_num);
        strcpy((*user_data)->car_num, tmp_user->car_num);
        (*user_data)->has_ticket = tmp_user->has_ticket;
        //printf("tmp_user: %s, %s\n", tmp_user->name, tmp_user->phone_num);
    }
	
    return OK;
}

int saveUserUI(MANAGE_UI* manage, char *car_number, USER_INFO **user_data){
    if(*user_data == NULL){
        *user_data = (USER_INFO *) malloc(sizeof(USER_INFO));
    }

    Label temp;
    labelCreate(&temp);

    setLabelPos(&temp,14,10);
    setLabelText(&temp,"차주 이름 >> ");
    printLabel(manage,&temp);
    // scanf("%s", (*user_data)->name); while(getchar()!='\n');
    fgets((*user_data)->name, 20, stdin);
    (*user_data)->name[strlen((*user_data)->name)-1] = '\0';

    setLabelPos(&temp,16,10);
    setLabelText(&temp,"차주 휴대폰 번호(010-1234-5678) >> ");
    printLabel(manage,&temp);
    // scanf("%s", (*user_data)->phone_num); while(getchar()!='\n');
    fgets((*user_data)->phone_num, 15, stdin);
    (*user_data)->phone_num[strlen((*user_data)->phone_num)-1] = '\0';
    
    strcpy((*user_data)->car_num, car_number);
    (*user_data)->has_ticket = 0;

    hashSetValue(user, car_number, *user_data);

    return OK;
}