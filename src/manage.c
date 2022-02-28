#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "manage.h"

#define SIMPLE_LOG_FILE_PATH "../data/history.log"

/*
manage.c
// ���� ���� ���� //
������ ���� �α� ��� �� ������ �Է�

flow 
1. �޴� �Է�(����, ����, �޴� ����)
2. getValues: ������ �Է� �� ����(����, ����) 
    data ����: �����ð�, �����ð�, ����, ��ġ, ���, ���� ����
    char* car_number;	char* in_datetime;	char* out_datetime;	
    char* car_type;	int floor;	int fee;	char is_paid;
3. save_log: �α� ����(history.log) �Է� (����, ����)
4. search_user: ������ ������ȣ�� user Ž��(user.dat)
-> ã�� user�� ������ �Է� �� ����
    4-1. ���� �̸�, ����ó (Ű���� �Է�)
    4-2. user.dat�� ����
5. current_list ������Ʈ
5-1. ������ current ����Ʈ�� �߰�
5-2. ������ current ����Ʈ�� ����
5-3. current.dat: ���� ���� �Ǿ��ִ� ���� 
      -> �ش� ���Ϸ� �޴� �����Ҷ� ����Ʈ ����
6. history.dat: ��ü ����, log���� ���� ���� ����
6-1. ������ history.dat ������ �߰�
6-2. ������ history.dat ������ ����
*/


int manage_in_out(void){
    // ������ ���� �α� ��� �� ������ �Է�
    char menu, tmp;
    int ret, error_cnt;
    CAR_INFO *car_info; 
    USER_INFO *user;

    while (1){
        // 1. �޴� �Է�(����, ����, �޴� ����)
        // char �ϳ��� ������ �� ������ ���� getchar�� ó�������� �Ƚ��϶�!
        scanf("%c", &menu);  while((tmp=getchar())!='\0');
        switch (menu){
            case 'i': 
                // 2. ������ �Է� �� ����(����)
                do {
                    ret = getValues(menu, &car_info);
                } while (!ret); // �Է� ���� �� ��쿣 ����� �� ���� ���� ������ ��� Ȯ��
                
                 // 3. save simple log
                error_cnt = 0;
                while (error_cnt < 5) // ���� ����� �����ΰ�� 5�� �õ�
                {
                    ret = save_log(menu, &car_info);
                    if (ret == OK){
                        break;
                    }
                }
                if (error_cnt >= 5) { // 5�� �õ��̻� ��������� �����ΰ�� �Լ� ����
                    return ret;
                }
                
                ret = search_user(car_info->car_number, &user); 
                // 4 search user data with car_number
                // user_info �ؽ����̺� �߰�
                // �ش� �޸𸮴� main������ free
                ret = update_current(menu, user); // 5. add current list 
                ret = update_history(menu, user); // 6. add history
                //currentList�� �߰�
                break;
            case 'o':
                ret = getValues(menu, &car_info); // 2. ������ �Է� �� ����(����)
                if (!ret) return ret;
                ret = save_log(menu, &car_info); // 3. save simple log
                if (!ret) return ret;
                ret = update_current(menu, user); // 5. add current list 
                if (!ret) return ret;
                ret = update_history(menu, user); // 6. add history
                if (!ret) return ret;
                // currentList ������ free
                // car_info free
                break;
            case 'q':
                // 1-1. �޴� ����� �Լ� ����
                return OK;
                break;
            default:
                return FORMAT_ERROR;
                break;
        }
    }
	
    return OK;
}

int getValues(char io, CAR_INFO **car_info) {
    // current_list �� ������ ������
    car_info = (CAR_INFO*) malloc(sizeof(CAR_INFO));
    // ���� �ð�
    char datetime[20];
    time_t rawTime = time(NULL);
    struct tm* time;
    time = localtime(&rawTime);  

    sprintf(datetime, "%d-%d-%d %d:%d:%d", 
        time->tm_year, time->tm_mon + 1, time->tm_mday,
        time->tm_hour, time->tm_min, time->tm_sec
    );

    // �޴� �� Ȯ���ؼ� ����
    if (io == 'i'){ // io == i �϶� �Է�
        strcpy((*car_info)->in_datetime, datetime);
        // strcpy((*car_info)->out_datetime, NULL);
    }
    else if (io == 'o'){// io == o �϶� �Է�
        strcpy((*car_info)->out_datetime, datetime);
        // strcpy((*car_info)->in_datetime, NULL);
    }
    else{
        // �޴��� �߸��޾Ҵµ� ���� ��찡 ������
        // Ȥ�ö� ���´ٸ� �޸� �����ϰ� �Լ� ����
        free(car_info);
        return FORMAT_ERROR;
    }
    
    printf("���� ��ȣ >> ");
    scanf("%s", (*car_info)->car_number);

    printf("���� [e]lectric, [l]ight, [n]ormal >> ");
    scanf("%c", &(*car_info)->car_type);

    printf("���� ��ġ >> ");
    scanf("%d", &(*car_info)->floor);
    
    // �� ���� �� 0���� ���� �����Ҷ� ���
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
    // �������� [i|o]    [car_number]   [yyyy-mm-dd hh:mm:ss]
    fprintf(fp, "%c\t%s\t%s\n", 
        io, 
        car_info->car_number, 
        (io=='i')?car_info->in_datetime : car_info->out_datetime
    );

    fclose(fp);
    return OK;
}

int search_user(char *car_number, USER_INFO **user_data){

    return OK;
}

int update_current(char io, USER_INFO *user_data){

    return OK;
}

int update_history(char io, USER_INFO *user_data){
    
    return OK;
}