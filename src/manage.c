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


int manage_in_out(LPHASH user_table, LinkedList *current_park, LinkedList *current_car){
    // ������ ���� �α� ��� �� ������ �Է�
    char menu, tmp;
    int ret, error_cnt;
    CAR_INFO *car_info; 
    USER_INFO *user;

    while (1){
        // 1. �޴� �Է�(����, ����, �޴� ����)
        // char �ϳ��� ������ �� ������ ���� getchar�� ó�������� �Ƚ��϶�!
        system("clear");
        printf("���� ���(i), ���� ���(o), ���ư���(q)\nselect >> ");
        scanf("%c", &menu);  while((tmp=getchar())!='\n');
        switch (menu){
            case 'i': {
                // 2. ������ �Է� �� ����(����)
                do {
                    ret = get_values(menu, &car_info);
                    if (ret) {
                        printf("error_num: %d\n", ret);
                        free(car_info);
                    }
                } while (ret); // �Է� ���� �� ��쿣 ����� �� ���� ���� ������ ��� Ȯ��
                 // 3. save simple log
                error_cnt = 0;
                while (error_cnt < 5) // ���� ����� �����ΰ�� 5�� �õ�
                {
                    ret = save_log(menu, car_info);
                    printf("error_num: %d\n", ret);
                    if (ret == OK){
                        break;
                    }
                }
                if (error_cnt >= 5) { // 5�� �õ��̻� ��������� �����ΰ�� �Լ� ����
                    return ret;
                }
                // 4 search user data with car_number
                ret = search_user(user_table, car_info->car_number, &user); 
                ret = update_current(menu, car_info, current_park, current_car); // 5. add current list 
                ret = update_history(menu, car_info, user); // 6. add history
                //currentList�� �߰�
                break;
            }
            case 'o':
            {
                ret = get_values(menu, &car_info); // 2. ������ �Է� �� ����(����)
                ret = save_log(menu, car_info); // 3. save simple log
                ret = search_user(user_table, car_info->car_number, &user); 
                ret = update_current(menu, car_info, current_park, current_car); // 5. remove current list 
                system("pause");
                ret = update_history(menu, car_info, user); // 6. modify history
                // currentList ������ free
                // car_info free
                break;
            }
            case 'q':
                // 1-1. �޴� ����� �Լ� ����
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
    // current_list �� ������ ������
    *car_info = (CAR_INFO*) malloc(sizeof(CAR_INFO));
    // ���� �ð�
    char datetime[20];
    struct tm* today;
    time_t rawTime = time(NULL);
    today = localtime(&rawTime);  

    sprintf(datetime, "%4d-%02d-%02d %02d:%02d", 
        today->tm_year+1900, today->tm_mon + 1, today->tm_mday,
        today->tm_hour, today->tm_min, today->tm_sec
    );

    // �޴� �� Ȯ���ؼ� ����
    if (io == 'i'){ // io == i �϶� �Է�
        strcpy((*car_info)->in_datetime, datetime);
        // strcpy((*car_info)->out_datetime, NULL);
        
        printf("���� ��ȣ >> ");
        scanf("%s", (*car_info)->car_number); while((tmp=getchar())!='\n');

        printf("���� [e]lectric, [l]ight, [n]ormal >> ");
        scanf("%c", &(*car_info)->car_type); while((tmp=getchar())!='\n');
        
        printf("���� ��ġ >> ");
        scanf("%d", &(*car_info)->floor); while((tmp=getchar())!='\n');
    
        switch ((*car_info)->car_type){
            case 'e': case'l': case'n':
                break;
            default:
                return FORMAT_ERROR;
        }
    }
    else if (io == 'o'){// io == o �϶� �Է�
        strcpy((*car_info)->out_datetime, datetime);
        // strcpy((*car_info)->in_datetime, NULL);
        printf("���� ��ȣ >> ");
        scanf("%s", (*car_info)->car_number); while((tmp=getchar())!='\n');
    }
    else{
        // �޴��� �߸��޾Ҵµ� ���� ��찡 ������
        // Ȥ�ö� ���´ٸ� �޸� �����ϰ� �Լ� ����
        return FORMAT_ERROR;
    }
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
    // �������� [i|o]\t[car_number]\t[yyyy-mm-dd hh:mm:ss]
    fprintf(fp, "%c\t%s\t%s\n", 
        io, 
        car_info->car_number, 
        (io=='i')? car_info->in_datetime : car_info->out_datetime
    );

    fclose(fp);
    return OK;
}

int search_user(LPHASH user_table, char *car_number, USER_INFO **user_data){
	// �ؽ� ���̺��� Ȯ��. ã�� ���� ������ user_data�� ����
    // hash table get
    USER_INFO *tmp_user = NULL;
    hashGetValue(user_table, car_number, &tmp_user);
    *user_data = (USER_INFO *) malloc(sizeof(USER_INFO));
    if ((tmp_user) == NULL){ // hash ���� ���� ���
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
    // user_data�� �� ����
    char tmp;
    printf("���� �̸� >> ");
    scanf("%s", (*user_data)->name); while((tmp=getchar())!='\n');
    printf("���� �޴��� ��ȣ >> ");
    scanf("%s", (*user_data)->phone_num); while((tmp=getchar())!='\n');
    // ���� ��ȣ �ڵ� ����
    strcpy((*user_data)->car_num, car_number);
    // ����� ����
    (*user_data)->has_ticket = 0;
    printf("has_ticket: %d\n", (*user_data)->has_ticket);
    // �ؽ� ���̺� ����
    hashSetValue(user_table, car_number, user_data);

    return OK;
}

int update_current(char io, CAR_INFO *car_info, LinkedList *current_park, LinkedList *current_car){
    switch (io){
        case 'i': // 1. io == i �϶� current list �� ������ �߰�
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
        case 'o': // 2. io == o �϶� current list ���� ����
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
    switch (io){
        case 'i':{
            // ������ �� history �������� �߰�
            FILE *fp = fopen(HISTORY_DATA_FILE_PATH,"ab");
            if(!fp) 
                return FILE_ERROR;

            // ����ü�� ������ ���Ͽ� ����
            fwrite(&car_info, sizeof(car_info), 1, fp);
            fclose(fp);
            break;
        }
        case 'o':{
            // ������ �� �� ��ȣ�� �´� �� ã�� �ش� �κ� ����
            // ��� ������ �о �� �ٸ� �κ� ã�� �ӽ� ���Ͽ� �� �����ؼ� ����
            FILE *fp = fopen(HISTORY_DATA_FILE_PATH,"rb");
            if(!fp) 
                return FILE_ERROR;
            FILE *fp_tmp = fopen(TEMP_HISTORY_DATA_FILE_PATH,"wb");
            if (!fp_tmp)
                return FILE_ERROR;
            while (1){
                CAR_INFO* tmp_car= (CAR_INFO *)malloc(sizeof(CAR_INFO));
                fread(tmp_car, sizeof((*tmp_car)), 1, fp);
                if (feof(fp)) 
                    break;
                if (strcmp(tmp_car->car_number, car_info->car_number) == 0
                    && strcmp(tmp_car->out_datetime, NULL) == 0
                ) { // ������ȣ�� ������ out_datetime�� NULL�� ����ü
                    char datetime[20];
                    struct tm* today;
                    time_t rawTime = time(NULL);
                    today = localtime(&rawTime);  

                    sprintf(datetime, "%4d-%02d-%02d %02d:%02d", 
                        today->tm_year+1900, today->tm_mon + 1, today->tm_mday,
                        today->tm_hour, today->tm_min, today->tm_sec
                    );
                    strcpy(tmp_car->out_datetime, datetime);
                    tmp_car->fee = calculate_fee(tmp_car->in_datetime, tmp_car->out_datetime);
                    fwrite(tmp_car, sizeof(*tmp_car), 1, fp_tmp);
                } else {
                    fwrite(tmp_car, sizeof(*tmp_car), 1, fp_tmp);
                }
                
            }
            fclose(fp);
            fclose(fp_tmp);
            // �ӽ� ���Ͽ� �ִ� ���� �����
            fp = fopen(HISTORY_DATA_FILE_PATH,"wb");
            if(!fp) 
                return FILE_ERROR;
            fp_tmp = fopen(TEMP_HISTORY_DATA_FILE_PATH,"rb");
            if (!fp_tmp)
                return FILE_ERROR;            
            while (1){
                CAR_INFO* tmp_car= (CAR_INFO *)malloc(sizeof(CAR_INFO));
                fread(tmp_car, sizeof((*tmp_car)), 1, fp_tmp);
                if (feof(fp_tmp)) 
                    break;
                fwrite(tmp_car, sizeof(*tmp_car), 1, fp);
            }
            fclose(fp_tmp);
            fclose(fp);
            break;
        }
        default:
            return FORMAT_ERROR;
    }
	// 0: �Է� ���� 1: ���� �����(����, �Է� ��) ����
    return OK;
}