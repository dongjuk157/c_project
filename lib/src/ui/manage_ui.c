#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "linkedlist.h"
#include "hash.h"

#include "manage_ui.h"
#include "manage_detail.h"
#include "info.h"
#include "messagebox.h"

// extern LPHASH user;
// extern LinkedList current_list;
// extern LinkedList current_car_list;


// 결제하기 기능 선택시 나타날 UI 제작 -> 제작한 Widget 구조체의 포인터 리턴
MANAGE_UI* createManageUI(){

    // 기본 위젯 Position 세팅
    MANAGE_UI *manage = createMainWidget(DEFAULT_POSY,DEFAULT_POSX,25,70);

    // Label 세팅
    labelAdd(manage,3,26,"주차 관리 프로그램",0);
    labelAdd(manage,5,30,"입출차 관리",0);
    labelAdd(manage,10,10,"1. 입차",0);
    labelAdd(manage,14,10,"2. 출차",0);

    labelAdd(manage, 20,10, "기능을 선택하세요 >> ",0);

    return manage;
}

int renderManageUI(MANAGE_UI *manage, void *data){
    //UI 프레임 그리기
    CAR_INFO* car_info = NULL;
    USER_INFO* user_info = NULL;

    renderWidget(manage);

    //prompt로 받을 선택넘버 | exit - home | 1,2 - 각 Page로 | 이외 - 다시입력 |
    char selectNumber[8];
    int errorCode = MANAGE_EOK; //에러코드

    //User에게 입력받고 개행문자 제거
    myGetline(selectNumber, 8, stdin);
    
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

            errorCode = getValuesUI(manage,IN_CAR,&car_info);
            if (errorCode){ // 에러생기면 함수 종료
                manageErrHandler(detail,errorCode);
                // return ret;
                return HOME;
            }
            errorCode = save_log(IN_CAR, car_info);
             if (errorCode){ // 에러생기면 함수 종료
                manageErrHandler(detail,errorCode);
                // return ret;
                return HOME;
            }
            errorCode = searchUserUI(manage, car_info->car_number, &user_info, IN_CAR);
            if (errorCode){ // 에러생기면 함수 종료
                manageErrHandler(detail,errorCode);
                // return ret;
                return HOME;
            }
            errorCode = update_current(IN_CAR, car_info, &current_list, &current_car_list); // 5. add current list 
            if (errorCode){ // 에러생기면 함수 종료
                manageErrHandler(detail,errorCode);
                // return ret;
                return HOME;
            }
            errorCode = update_history(IN_CAR, car_info, user_info); // 6. add history
            if (errorCode){ // 에러생기면 함수 종료
                manageErrHandler(detail,errorCode);
                // return ret;
                return HOME;
            }
            
            gotoxy(10,20);
            printf("새로운 차량이 정상적으로 입차 되었습니다.\n");
            getchar();

        } 
        else if(num == 2){
            // 출차
            detail = createManageDetailUI(OUT_CAR);
            renderWidget(detail);
            errorCode = getValuesUI(manage,OUT_CAR,&car_info);
            if (errorCode){ // 에러생기면 함수 종료
                manageErrHandler(detail,errorCode);
                // return ret;
                return HOME;
            }
            errorCode = searchUserUI(manage, car_info->car_number, &user_info , OUT_CAR);
            if (errorCode){ // 에러생기면 함수 종료
                manageErrHandler(detail,errorCode);
                // return ret;
                return HOME;
            }

            errorCode = save_log(OUT_CAR, car_info);
            if (errorCode){ // 에러생기면 함수 종료
                manageErrHandler(detail,errorCode);
                // return ret;
                return HOME;
            }
            errorCode = update_current(OUT_CAR, car_info, &current_list, &current_car_list); // 5. add current list 
            if (errorCode){ // 에러생기면 함수 종료
                manageErrHandler(detail,errorCode);
                // return ret;
                return HOME;
            }
            errorCode = update_history(OUT_CAR, car_info, user_info); // 6. add history
            if (errorCode){ // 에러생기면 함수 종료
                manageErrHandler(detail,errorCode);
                // return ret;
                return HOME;
            }
            
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

    if(io == 'i'){
        getDateTime((*car_info)->in_datetime);
        
        printSiglelineWidget(manage, 8,10, "차량 번호(123가1234)>> ", 0);
        myGetline((*car_info)->car_number, 20, stdin);
        CAR_INFO* car;
        if(findCarInfo((*car_info)->car_number,&car) == INFO_EOK){
            return ERR_MANAGE_SAME_CAR_IN_PAKR;
        }

        printSiglelineWidget(manage, 10,10, "차종 [e]lectric, [l]ight, [n]ormal >> ", 0);
        scanf("%c", &(*car_info)->car_type); while(getchar()!='\n');

        switch ((*car_info)->car_type) {
            case 'e': case 'l':
                break;
            default:
                (*car_info)->car_type = 'n';
                break;
        }
        
        printSiglelineWidget(manage, 12,10, "주차 위치(층수 입력) >> ", 0);
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
                    return ERR_MANAGE_TOO_MUCH_CAR; // 자동차 수 초과
                }
                break; // 
            }
            tmp = tmp->next;
        }
        if (!find_flag) {  // 해당 층이 등록되지 않은 경우
            return ERR_MANAGE_FLOOR_NOT_EXIST; // there is not enrolled floor.
        }
    }
    else if(io == 'o'){
        printSiglelineWidget(manage,14,10,"차량 번호(123가1234)>> ", 0);
        myGetline((*car_info)->car_number, 20, stdin);

        // 입차되지 않은 차량 제거
        CAR_INFO* car = NULL;
        if(findCarInfo((*car_info)->car_number, &car) == INFO_EOK){
            getDateTime(car->out_datetime);
            getDateTime((*car_info)->out_datetime);
        }
        else{
            return ERR_MANAGE_CAR_NOT_EXIST;
        }
      
    }
    else {
        return ERR_MANAGE_INVALID_INPUT; // format error
    }

    return MANAGE_EOK; // ok
}

int searchUserUI(MANAGE_UI* manage,  char *car_number, USER_INFO **user_data, char io){
    if(searchUser(car_number, user_data) == INFO_EOK){
        return MANAGE_EOK;
    }
    else {
        if (io == IN_CAR){
            saveUserUI(manage, car_number, user_data);
            return MANAGE_EOK;
        }
        return ERR_MANAGE_USER_NOT_EXIST; // NOT SEARCH USER
    }
}

int saveUserUI(MANAGE_UI* manage, char *car_number, USER_INFO **user_data){
    if(*user_data == NULL){
        *user_data = (USER_INFO *) malloc(sizeof(USER_INFO));
    }

    printSiglelineWidget(manage, 14, 10, "차주 이름 >> ", 0);
    myGetline((*user_data)->name, 20, stdin);

    printSiglelineWidget(manage, 16, 10, "차주 휴대폰 번호(010-1234-5678) >> ", 0);
    myGetline((*user_data)->phone_num, 15, stdin);
    
    strcpy((*user_data)->car_num, car_number);
    (*user_data)->has_ticket = 0;

    strcpy((*user_data)->recentTicket, "0000-00-00");
    hashSetValue(user, car_number, *user_data);

    return MANAGE_EOK;
}

int save_log(char io, CAR_INFO *car_info){
    FILE *fp;
    fp = fopen(SIMPLE_LOG_FILE_PATH, "a");
    if (!fp){
        return FILE_ERROR;
    }
    // fputs("",fp);
    // 파일형식 [i|o]\t[car_number]\t[yyyy-mm-dd hh:mm:ss]
    fprintf(fp, "%c\t%s\t%s\n", 
        io, 
        car_info->car_number, 
        (io=='i')? car_info->in_datetime : car_info->out_datetime
    );

    fclose(fp);
    return OK;
}

int update_current(char io, CAR_INFO *car_info, LinkedList *current_park, LinkedList *current_car){
    
    // printf("update_current\n");
    switch (io){
        case 'i': // 1. io == i 일때 current list 에 데이터 추가
            {
                CAR_INFO* tmp_car_info;
                tmp_car_info = (CAR_INFO *)malloc(sizeof(CAR_INFO));
                strcpy(tmp_car_info->car_number, car_info->car_number);
                strcpy(tmp_car_info->in_datetime, car_info->in_datetime);
                strcpy(tmp_car_info->out_datetime, car_info->out_datetime);
                tmp_car_info->car_type = car_info->car_type;
                tmp_car_info->is_paid = car_info->is_paid;
                tmp_car_info->floor = car_info->floor;
                tmp_car_info->fee = car_info->floor;

                list_push_back(current_car, tmp_car_info);
            } 
            break;
        case 'o': // 2. io == o 일때 current list 에서 제거
            {
                Node* cur;
                int idx=0;
                cur = current_car->head;
                while (cur){
                    CAR_INFO* tmp2 = (CAR_INFO*) cur->data;
                    if (strcmp(tmp2->car_number, car_info->car_number) == 0) {
                        list_remove(current_car, idx);
                        break;
                    }
                    cur = cur->next; idx++;
                }
            }
            break;
        default:
            break;
    }
    return OK;
}

int update_history(char io, CAR_INFO *car_info, USER_INFO *user_data){
    // printf("udpate_history\n");
    switch (io){
        case 'i':{
            // 입차할 때 history 마지막에 추가
            FILE *fp = fopen(HISTORY_DATA_FILE_PATH,"ab");
            if(!fp) 
                return FILE_ERROR;

            // 구조체의 내용을 파일에 저장
            fwrite(car_info, sizeof(CAR_INFO), 1, fp);
            fclose(fp);
            break;
        }
        case 'o':{
            // 출차할 때 차 번호가 맞는 값 찾고 해당 부분 수정
            FILE *fp = fopen(HISTORY_DATA_FILE_PATH,"rb+");

            if(!fp) 
                return FILE_ERROR;
            
            while (1){
                
                CAR_INFO* tmp_car= (CAR_INFO *)malloc(sizeof(CAR_INFO));
                fread(tmp_car, sizeof(CAR_INFO), 1, fp);
                if (feof(fp)) 
                    break;
                if (strcmp(tmp_car->car_number, car_info->car_number) == 0
                    && strcmp(tmp_car->out_datetime, "") == 0
                ) { // 차량번호가 같은데 out_datetime이 NULL인 구조체
                    // out_datetime 설정
                    char datetime[20];
                    getDateTime(datetime);
                    
                    strcpy(tmp_car->out_datetime, datetime);
                    // 요금산정
                    tmp_car->fee = calculate_fee(tmp_car->in_datetime, tmp_car->out_datetime);

                    // read한 만큼 뒤로 
                    fseek(fp, -sizeof(CAR_INFO), SEEK_CUR);
                    // 덮어쓰기

                    fwrite(tmp_car, sizeof(CAR_INFO), 1, fp);

                    Node *tmp = current_list.head;
                    while(tmp){
                        PARK* buf = (PARK*)tmp->data;
                        if(buf->floor == tmp_car->floor){
                            buf->total_car-=1;
                            break;
                        }
                        tmp = tmp->next;
                    }

                }
            }
            fclose(fp);

            break;
        }
        default:
            return ERR_MANAGE_INVALID_INPUT;
    }
	// 0: 입력 성공 1: 파일 입출력(오픈, 입력 등) 실패
    return OK;
}

int manageErrHandler(Widget* widget, int errorCode){
    switch(errorCode){
    case ERR_MANAGE_SAME_CAR_IN_PAKR:
        messageBox(widget, 7 ,17, "해당 차량이 이미 존재합니다.");
        break;
    case ERR_MANAGE_TOO_MUCH_CAR:
        messageBox(widget, 7 ,17, "해당 층에 주차 공간이 없습니다.");
        break;
    case ERR_MANAGE_FLOOR_NOT_EXIST:
        messageBox(widget, 7 ,17, "해당 층에 주차장이 없습니다.");
        break;
    case ERR_MANAGE_CAR_NOT_EXIST:
        messageBox(widget, 7 ,17, "해당 차량이 존재하지 않습니다.");
        break;
    case ERR_MANAGE_INVALID_INPUT:
        messageBox(widget, 7 ,17, "잘못된 입력 입니다.");
        break;
    case ERR_MANAGE_USER_NOT_EXIST:
        break;
    default:
        break;
    }
    return MANAGE_EOK;
}