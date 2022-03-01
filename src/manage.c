#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "manage.h"
#include "hash.h"


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
                printf("==\n");
                printf("%s\n", car_info->car_number);
                printf("%s\n", (menu=='i')?car_info->in_datetime : car_info->out_datetime);
                printf("==\n");
                 // 3. save simple log
                error_cnt = 0;
                while (error_cnt < 5) // ���� ����� �����ΰ�� 5�� �õ�
                {
                    ret = save_log(menu, car_info);
                    printf("error_num: %d", ret);
                    if (ret == OK){
                        break;
                    }
                }
                if (error_cnt >= 5) { // 5�� �õ��̻� ��������� �����ΰ�� �Լ� ����
                    return ret;
                }
                
                ret = search_user(car_info->car_number, &user); 
                printf("error_num: %d", ret);
                // 4 search user data with car_number
                // user_info �ؽ����̺� �߰�
                // �ش� �޸𸮴� main������ free
                ret = update_current(menu, car_info, user); // 5. add current list 
                printf("error_num: %d", ret);

                ret = update_history(menu, car_info, user); // 6. add history
                printf("error_num: %d", ret);
                //currentList�� �߰�
                break;
            }
            case 'o':
            {
                ret = get_values(menu, &car_info); // 2. ������ �Է� �� ����(����)
                ret = save_log(menu, car_info); // 3. save simple log
                ret = update_current(menu, car_info, user); // 5. add current list 
                ret = update_history(menu, car_info, user); // 6. add history
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

    sprintf(datetime, "%4d-%02d-%02d %02d:%02d:%02d", 
        today->tm_year+1900, today->tm_mon + 1, today->tm_mday,
        today->tm_hour, today->tm_min, today->tm_sec
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
        return FORMAT_ERROR;
    }
    
    printf("���� ��ȣ >> ");
    scanf("%s", (*car_info)->car_number); while((tmp=getchar())!='\n');

    printf("���� [e]lectric, [l]ight, [n]ormal >> ");
    scanf("%c", &(*car_info)->car_type); while((tmp=getchar())!='\n');
    switch ((*car_info)->car_type){
        case 'e': case'l': case'n':
            break;
        default:
            return FORMAT_ERROR;
    }

    printf("���� ��ġ >> ");
    scanf("%d", &(*car_info)->floor); while((tmp=getchar())!='\n');
    
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
	// �ؽ� ���̺��� Ȯ��. ã�� ���� ������ user_data�� ����

    // LPHASH, LPDATA�� ���� �� �����ؾ��� ��
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
    // user �ؽ����̺� ���� �� �ؽ� ���̺� ����
    // ó�� �����Ҷ� �ؽ�Ʈ ���� �о ���� ������ָ� ������
}
int update_current(char io, CAR_INFO *car_info, USER_INFO *user_data){
    // 1. io == i �϶� current list �� ������ �߰�
	// 2. io == o �϶� current list ���� ����
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
            // append��� fopen("history.dat", "r+");
            FILE *fp = fopen(HISTORY_DATA_FILE_PATH,"r+");
            if(!fp) 
                return FILE_ERROR;
            ////////// �̱���
            // ���ϳ��������� Ȯ��=> �ֱٿ� �߰��Ǿ����� �Ŵϱ�
            // ã���� �ش� �κп� �״�� �ٿ��ֱ�
            // fwrite(&car_info, sizeof(car_info), 1, fp);
            fclose(fp);
            break;
        }
        default:
            return FORMAT_ERROR;
    }
	// 0: �Է� ���� 1: ���� �����(����, �Է� ��) ����
    return OK;
}