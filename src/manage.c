#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "manage.h"
#include "hash.h"


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


int manage_in_out(void){
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
                // 2. 데이터 입력 및 생성(입차)
                do {
                    ret = get_values(menu, &car_info);
                    if (ret) {
                        printf("error_num: %d\n", ret);
                        free(car_info);
                    }
                } while (ret); // 입력 에러 인 경우엔 제대로 된 값을 넣을 때까지 계속 확인
                printf("==\n");
                printf("%s\n", car_info->car_number);
                printf("%s\n", (menu=='i')?car_info->in_datetime : car_info->out_datetime);
                printf("==\n");
                 // 3. save simple log
                error_cnt = 0;
                while (error_cnt < 5) // 파일 입출력 에러인경우 5번 시도
                {
                    ret = save_log(menu, car_info);
                    printf("error_num: %d", ret);
                    if (ret == OK){
                        break;
                    }
                }
                if (error_cnt >= 5) { // 5번 시도이상 파일입출력 에러인경우 함수 종료
                    return ret;
                }
                
                ret = search_user(car_info->car_number, &user); 
                printf("error_num: %d", ret);
                // 4 search user data with car_number
                // user_info 해시테이블에 추가
                // 해당 메모리는 main끝날때 free
                ret = update_current(menu, car_info, user); // 5. add current list 
                printf("error_num: %d", ret);

                ret = update_history(menu, car_info, user); // 6. add history
                printf("error_num: %d", ret);
                //currentList에 추가
                break;
            }
            case 'o':
            {
                ret = get_values(menu, &car_info); // 2. 데이터 입력 및 생성(출차)
                ret = save_log(menu, car_info); // 3. save simple log
                ret = update_current(menu, car_info, user); // 5. add current list 
                ret = update_history(menu, car_info, user); // 6. add history
                // currentList 데이터 free
                // car_info free
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
        system("pause");
    }
	
    return OK;
}

int get_values(char io, CAR_INFO **car_info) {
    char tmp;
    // current_list 에 저장할 데이터
    *car_info = (CAR_INFO*) malloc(sizeof(CAR_INFO));
    // 현재 시간
    char datetime[20];
    struct tm* today;
    time_t rawTime = time(NULL);
    today = localtime(&rawTime);  

    sprintf(datetime, "%4d-%02d-%02d %02d:%02d:%02d", 
        today->tm_year+1900, today->tm_mon + 1, today->tm_mday,
        today->tm_hour, today->tm_min, today->tm_sec
    );

    // 메뉴 값 확인해서 저장
    if (io == 'i'){ // io == i 일때 입력
        strcpy((*car_info)->in_datetime, datetime);
        // strcpy((*car_info)->out_datetime, NULL);
    }
    else if (io == 'o'){// io == o 일때 입력
        strcpy((*car_info)->out_datetime, datetime);
        // strcpy((*car_info)->in_datetime, NULL);
    }
    else{
        // 메뉴를 잘못받았는데 들어올 경우가 없지만
        // 혹시라도 들어온다면 메모리 해제하고 함수 종료
        return FORMAT_ERROR;
    }
    
    printf("차량 번호 >> ");
    scanf("%s", (*car_info)->car_number); while((tmp=getchar())!='\n');

    printf("차종 [e]lectric, [l]ight, [n]ormal >> ");
    scanf("%c", &(*car_info)->car_type); while((tmp=getchar())!='\n');
    switch ((*car_info)->car_type){
        case 'e': case'l': case'n':
            break;
        default:
            return FORMAT_ERROR;
    }

    printf("주차 위치 >> ");
    scanf("%d", &(*car_info)->floor); while((tmp=getchar())!='\n');
    
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
    // 파일형식 [i|o]    [car_number]   [yyyy-mm-dd hh:mm:ss]
    printf("%s\n", car_info->car_number);
    printf("%s\n", (io=='i')?car_info->in_datetime : car_info->out_datetime);
    fprintf(fp, "%c\t%s\t%s\n", 
        io, 
        car_info->car_number, 
        (io=='i')? car_info->in_datetime : car_info->out_datetime
    );

    fclose(fp);
    return OK;
}

int search_user(char *car_number, USER_INFO **user_data){
	// 해시 테이블에서 확인. 찾는 값이 있으면 user_data에 저장

    // LPHASH, LPDATA에 대한 것 설정해야할 듯
    // ret = hashGetValue(LPHASH lpHash, const char* key, LPDATA* value);
    // if(value) {
    //     user_data = (User *)malloc(sizeof(User));
    //     strcpy(user_data->name, value->name);
    //     strcpy(user_data->phone_num, value->phone_num);
    //     strcpy(user_data->car_num, value->car_num);
    //     user_data->has_ticket = value->has_ticket;
    // }
    // else {
    //     save_user(car_number, user_data);
    // }
	
    return OK;
}
int save_user(char *car_number, USER_INFO **user_data){
    // user 해시테이블에 없을 때 해시 테이블에 저장
    // 처음 시작할때 텍스트 파일 읽어서 쉽게 만들어주면 좋을듯
}
int update_current(char io, CAR_INFO *car_info, USER_INFO *user_data){
    // 1. io == i 일때 current list 에 데이터 추가
	// 2. io == o 일때 current list 에서 제거
    return OK;
}

int update_history(char io, CAR_INFO *car_info, USER_INFO *user_data){
    switch (io){
        case 'i':{
            // 입차할 때 history 마지막에 추가
            FILE *fp = fopen(HISTORY_DATA_FILE_PATH,"ab");
            if(!fp) 
                return FILE_ERROR;

            // 구조체의 내용을 파일에 저장
            fwrite(&car_info, sizeof(car_info), 1, fp);
            fclose(fp);
            break;
        }
        case 'o':{
            // 출차할 때 차 번호가 맞는 값 찾고 해당 부분 수정
            // append모드 fopen("history.dat", "r+");
            FILE *fp = fopen(HISTORY_DATA_FILE_PATH,"r+");
            if(!fp) 
                return FILE_ERROR;
            ////////// 미구현
            // 파일끝에서부터 확인=> 최근에 추가되어있을 거니까
            // 찾으면 해당 부분에 그대로 붙여넣기
            // fwrite(&car_info, sizeof(car_info), 1, fp);
            fclose(fp);
            break;
        }
        default:
            return FORMAT_ERROR;
    }
	// 0: 입력 성공 1: 파일 입출력(오픈, 입력 등) 실패
    return OK;
}