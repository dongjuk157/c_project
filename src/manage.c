#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "manage.h"
#include "hash.h"
#include "linkedlist.h"
#include "utils.h"

/*
manage.c
// 출입 차량 관리 //
차량의 출입 로그 기록 및 데이터 입력

flow 
1. 메뉴 입력(입차, 출차, 메뉴 종료)
2. getValues: 데이터 입력 및 생성(입차, 출차) 
    data 구조: 입차시간, 출차시간, 차종, 위치, 요금, 정산 유무
    char* car_number;	char* in_datetime;	char* out_datetime;	
    char* car_type;	int floor;	int fee;	char is_paid;
3. save_log: 로그 파일(history.log) 입력 (입차, 출차)
4. search_user: 입차시 차량번호로 user 탐색(user.dat)
-> 찾는 user가 없으면 입력 폼 생성
    4-1. 차주 이름, 연락처 (키보드 입력)
    4-2. user.dat에 저장
5. current_list 업데이트
5-1. 입차시 current 리스트에 추가
5-2. 출차시 current 리스트에 삭제
5-3. current.dat: 현재 주차 되어있는 정보 
      -> 해당 파일로 메뉴 시작할때 리스트 생성
6. history.dat: 전체 정보, log보다 상세한 정보 저장
6-1. 입차시 history.dat 데이터 추가
6-2. 출차시 history.dat 데이터 수정
*/


int manage_in_out(LPHASH user_table, LinkedList *current_park, LinkedList *current_car){
    // 차량의 출입 로그 기록 및 데이터 입력
    char menu, tmp;
    int ret, error_cnt;
    CAR_INFO *car_info; 
    USER_INFO *user;

    while (1){
        // 1. 메뉴 입력(입차, 출차, 메뉴 종료)
        // char 하나만 받으며 그 이후의 값은 getchar가 처리했으니 안심하라구!
        system("clear");
        printf("입차 등록(i), 출차 등록(o), 돌아가기(q)\nselect >> ");
        scanf("%c", &menu);  while((tmp=getchar())!='\n');
        switch (menu){
            case 'i': {
                ret = get_values(menu, &car_info);  // 2. 데이터 입력 및 생성(입차)
                ret = save_log(menu, car_info);     // 3. save simple log
                ret = search_user(user_table, car_info->car_number, &user);      // 4 search user data with car_number
                ret = update_current(menu, car_info, current_park, current_car); // 5. add current list 
                ret = update_history(menu, car_info, user); // 6. add history
                saveUserData(user_table);
                break;
            }
            case 'o':
            {
                ret = get_values(menu, &car_info); // 2. 데이터 입력 및 생성(출차)
                ret = save_log(menu, car_info); // 3. save simple log
                ret = search_user(user_table, car_info->car_number, &user); 
                ret = update_current(menu, car_info, current_park, current_car); // 5. remove current list 
                ret = update_history(menu, car_info, user); // 6. modify history
                break;
            }
            case 'q':
                // 1-1. 메뉴 종료시 함수 종료
                return OK;
                break;
            default:
                return FORMAT_ERROR;
                break;
        }
        printf("press any buttons");
        getchar();
    }
	
    return OK;
}

int get_values(char io, CAR_INFO **car_info) {
    char tmp;
    // current_list 에 저장할 데이터
    *car_info = (CAR_INFO*) malloc(sizeof(CAR_INFO));
    // 현재 시간
    char datetime[20];
    getDateTime(datetime);

    // 메뉴 값 확인해서 저장
    if (io == 'i'){ // io == i 일때 입력
        strcpy((*car_info)->in_datetime, datetime);
        // strcpy((*car_info)->out_datetime, NULL);
        
        printf("차량 번호 >> ");
        scanf("%s", (*car_info)->car_number); while((tmp=getchar())!='\n');

        printf("차종 [e]lectric, [l]ight, [n]ormal >> ");
        scanf("%c", &(*car_info)->car_type); while((tmp=getchar())!='\n');
        
        printf("주차 위치 >> ");
        scanf("%d", &(*car_info)->floor); while((tmp=getchar())!='\n');
    
        switch ((*car_info)->car_type){
            case 'e': case'l': case'n':
                break;
            default:
                return FORMAT_ERROR;
        }
    }
    else if (io == 'o'){// io == o 일때 입력
        strcpy((*car_info)->out_datetime, datetime);
        // strcpy((*car_info)->in_datetime, NULL);
        printf("차량 번호 >> ");
        scanf("%s", (*car_info)->car_number); while((tmp=getchar())!='\n');
    }
    else{
        // 메뉴를 잘못받았는데 들어올 경우가 없지만
        // 혹시라도 들어온다면 메모리 해제하고 함수 종료
        return FORMAT_ERROR;
    }
    // 그 외의 값 0으로 설정 정산할때 사용
    (*car_info)->fee = 0;
    (*car_info)->is_paid = 0;
    return OK;
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

int search_user(LPHASH user_table, char *car_number, USER_INFO **user_data){
    printf("search_user\n");
	// 해시 테이블에서 확인. 찾는 값이 있으면 user_data에 저장
    // hash table get
    USER_INFO *tmp_user = NULL;
    hashGetValue(user_table, car_number, &tmp_user);
    *user_data = (USER_INFO *) malloc(sizeof(USER_INFO));
    if ((tmp_user) == NULL){ // hash 값이 없는 경우
        save_user(user_table, car_number, user_data);
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
int save_user(LPHASH user_table, char *car_number, USER_INFO **user_data){
    // user_data에 값 저장
    char tmp;
    printf("차주 이름 >> ");
    scanf("%s", (*user_data)->name); while((tmp=getchar())!='\n');
    printf("차주 휴대폰 번호 >> ");
    scanf("%s", (*user_data)->phone_num); while((tmp=getchar())!='\n');
    // 차량 번호 자동 저장
    strcpy((*user_data)->car_num, car_number);
    // 정기권 없음
    (*user_data)->has_ticket = 0;
    // 해시 테이블에 저장
    hashSetValue(user_table, car_number, *user_data);

    return OK;
}

int update_current(char io, CAR_INFO *car_info, LinkedList *current_park, LinkedList *current_car){
    
    printf("update_current\n");
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
                    CAR_INFO* tmp2;
                    tmp2 = (CAR_INFO*) cur->data;
                    if (strcmp(tmp2->car_number, car_info->car_number) == 0) {
                        list_remove(current_car, idx);
                        break;
                    }
                    cur = cur->next;
                    idx++;
                }
            }
            break;
        default:
            break;
    }
    return OK;
}

int update_history(char io, CAR_INFO *car_info, USER_INFO *user_data){
    printf("udpate_history\n");
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

                }
            }
            fclose(fp);

            break;
        }
        default:
            return FORMAT_ERROR;
    }
	// 0: 입력 성공 1: 파일 입출력(오픈, 입력 등) 실패
    return OK;
}