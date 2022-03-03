#include "join.h"
#include "messagebox.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcat
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int loginCheck(char *id, char *password){
    // 1. ���� ���� data/user
    FILE *fp = fopen("./data/user.dat", "rb");
    if (!fp){
        return ERR_JOIN_FILE_NOT_OPEN; // file error
    }
    // 2. ���� �� ���� id �ִ��� Ȯ��
    USER *tmp = (USER*)malloc(sizeof(USER));
    while (1){
        fread(tmp, sizeof(USER), 1, fp);
        if (feof(fp))
            break;
        if (strcmp(tmp->id, id) == 0) { // search same id
            // check password
            // ��ȣȭ�� password�� ���ϰ�ʹ�...
            if (strcmp(tmp->passward, password) == 0) {
                return JOIN_EOK; // success
            } else {
                return ERR_JOIN_INVALID_PASSWORD; // login failed
            }
        }
    }    
    return ERR_JOIN_INVALID_ID; // not found
}

int join(char *id, char *password){
    // 1. ���� ���� data/user
    FILE *fp = fopen("./data/user.dat", "rb+");
    if (!fp){
        return ERR_JOIN_FILE_NOT_OPEN; // file error
    }
    // 2. ���� �� ���� id �ִ��� Ȯ��
    USER *tmp = (USER*)malloc(sizeof(USER));
    while (1){
        fread(tmp, sizeof(USER), 1, fp);
        if (feof(fp))
            break;
        if (strcmp(tmp->id, id) == 0) {
            return ERR_JOIN_SAME_ID_EXIST; // same id
        }
    }
    // 3. ���� �� ã�� ���� ������ �������� ����ü�� �߰�
    fseek(fp, 0, SEEK_END); // ���� ���������� �̵�
    strcpy(tmp->id, id); 
    strcpy(tmp->passward, password);  // password ��ȣȭ�ϰ�ʹ�...
    fwrite(tmp, sizeof(USER), 1, fp); // ���Ͽ� ��  �߰�
    fclose(fp); 
    free(tmp);
    createNewFiles(id);
    return JOIN_EOK;
}

int createNewFiles(char *id){
    // ȸ���������� ������ ���丮,  ���
    // char id[256];
    // char password[256];
    char dirname[256] = "./data";
    // ȸ������ �� �ش� id�� ���� ���� ����
    struct stat sb;
    if (stat(dirname, &sb) == 0 && S_ISDIR(sb.st_mode)){
        // printf("%s already exists\n", dirname);
    }
    else {
        // create directory "./data"
        if(mkdir(dirname, 0777) < 0 && errno != EEXIST) {
            // we check for EEXIST since maybe the directory is already there
            perror("mkdir failed");
            exit(-1); // or some other error handling code
        }
    }
    strcat(dirname, "/");
    strcat(dirname, id);
    
    if (stat(dirname, &sb) == 0 && S_ISDIR(sb.st_mode)){
        // printf("%s already exists\n", dirname);
    } else {
        // create directory "./data"
        if(mkdir(dirname, 0777) < 0 && errno != EEXIST) {
            // we check for EEXIST since maybe the directory is already there
            perror("mkdir failed");
            exit(-1); // or some other error handling code
        }
    }
    FILE *fp;
    char tmp_file_name[512];

    // initialize data/{id}/Current.dat 
    tmp_file_name[0] = '\0'; // �ʱ�ȭ
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/Current.dat");
    fp = fopen(tmp_file_name, "wb");
    fclose(fp);

    // initialize data/{id}/History.dat
    tmp_file_name[0] = '\0'; // �ʱ�ȭ
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/History.dat");
    fp = fopen(tmp_file_name, "wb"); 
    fclose(fp);

    // initialize data/{id}/ParkingLot.dat
    tmp_file_name[0] = '\0'; // �ʱ�ȭ
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/ParkingLot.dat");
    fp = fopen(tmp_file_name, "wb");
    fclose(fp);

    // initialize data/{id}/User.dat
    tmp_file_name[0] = '\0'; // �ʱ�ȭ
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/User.dat");
    fp = fopen(tmp_file_name, "wb");
    fclose(fp);

    // initialize data/{id}/history.log
    tmp_file_name[0] = '\0'; // �ʱ�ȭ
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/history.log");
    fp = fopen(tmp_file_name, "w");
    fclose(fp);


    return JOIN_EOK;
}

int createParkingLot(char *id, LinkedList* list){
    FILE *fp;
    // initialize data/{id}/ParkingLot.dat
    char tmp_file_name[512] = "./data/";
    strcat(tmp_file_name, id);
    strcat(tmp_file_name, "/ParkingLot.dat");

    fp = fopen(tmp_file_name, "wb");
    if(!fp) 
        return ERR_JOIN_FILE_NOT_OPEN;
    
    Node* cur = list->head;
    PARK *tmp;
    while (cur) {
        tmp = (PARK*)cur->data;
        fwrite(tmp, sizeof(PARK), 1, fp);
        cur = cur->next;
    }
    fclose(fp);
    free(tmp);
    return JOIN_EOK;
}

int joinErrorHandler(Widget* widget, int errCode){
    switch (errCode)
    {
    case JOIN_EOK:
        break;
    case ERR_JOIN_FILE_NOT_OPEN:
        messageBox(widget,7,9, "������ �� �� �����ϴ�.");
        break;
    case ERR_JOIN_INVALID_PASSWORD:
        messageBox(widget,7,9,"��й�ȣ�� �ٽ� �Է����ּ���.");
        break;
    case ERR_JOIN_INVALID_ID:
        messageBox(widget,7,9,"�߸��� ���̵� �Դϴ�.");
        break;
    case ERR_JOIN_SAME_ID_EXIST:
        messageBox(widget,7,9, "�ش� ���̵� �̹� �����մϴ�.");
        break;
    }
    return JOIN_EOK;
}