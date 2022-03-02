#include "join.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcat
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int loginCheck(char *id, char *password){
    // 1. 파일 열기 data/user
    FILE *fp = fopen("./data/user.dat", "rb");
    if (!fp){
        return -1; // file error
    }
    // 2. 파일 내 같은 id 있는지 확인
    USER *tmp = (USER*)malloc(sizeof(USER));
    while (1){
        fread(tmp, sizeof(USER), 1, fp);
        if (feof(fp))
            break;
        if (strcmp(tmp->id, id) == 0) { // search same id
            // check password
            // 암호화된 password로 비교하고싶다...
            if (strcmp(tmp->passward, password) == 0) {
                return 0; // success
            } else {
                return -2; // login failed
            }
        }
    }    
    return -3; // not found
}

int join(char *id, char *password){
    // 1. 파일 열기 data/user
    FILE *fp = fopen("./data/user.dat", "rb+");
    if (!fp){
        return -1; // file error
    }
    // 2. 파일 내 같은 id 있는지 확인
    USER *tmp = (USER*)malloc(sizeof(USER));
    while (1){
        fread(tmp, sizeof(USER), 1, fp);
        if (feof(fp))
            break;
        if (strcmp(tmp->id, id) == 0) {
            return -2; // same id
        }
    }
    // 3. 파일 내 찾는 값이 없으면 마지막에 구조체로 추가
    fseek(fp, 0, SEEK_END); // 파일 마지막으로 이동
    strcpy(tmp->id, id); 
    strcpy(tmp->passward, password);  // password 암호화하고싶다...
    fwrite(tmp, sizeof(USER), 1, fp); // 파일에 값  추가
    fclose(fp); 
    free(tmp);
    createNewFiles(id);
    return 0;
}

int createNewFiles(char *id){
    // 회원가입이후 데이터 디렉토리,  기능
    // char id[256];
    // char password[256];
    char dirname[256] = "./data";
    // 회원가입 후 해당 id로 폴더 구조 생성
    struct stat sb;
    if (stat(dirname, &sb) == 0 && S_ISDIR(sb.st_mode)){
        printf("%s already exists\n", dirname);
    } else {
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
        printf("%s already exists\n", dirname);
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
    tmp_file_name[0] = '\0'; // 초기화
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/Current.dat");
    fp = fopen(tmp_file_name, "wb");
    fclose(fp);

    // initialize data/{id}/History.dat
    tmp_file_name[0] = '\0'; // 초기화
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/History.dat");
    fp = fopen(tmp_file_name, "wb"); 
    fclose(fp);

    // initialize data/{id}/ParkingLot.dat
    tmp_file_name[0] = '\0'; // 초기화
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/ParkingLot.dat");
    fp = fopen(tmp_file_name, "wb");
    fclose(fp);

    // initialize data/{id}/User.dat
    tmp_file_name[0] = '\0'; // 초기화
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/User.dat");
    fp = fopen(tmp_file_name, "wb");
    fclose(fp);

    // initialize data/{id}/history.log
    tmp_file_name[0] = '\0'; // 초기화
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/history.log");
    fp = fopen(tmp_file_name, "w");
    fclose(fp);


    return 0;
}


int createParkingLot(char *id, LinkedList* list){
    FILE *fp;
    // initialize data/{id}/ParkingLot.dat
    char tmp_file_name[512] = "./data/";
    strcat(tmp_file_name, id);
    strcat(tmp_file_name, "/ParkingLot.dat");

    fp = fopen(tmp_file_name, "wb");
    if(!fp) 
        return -1;
    
    Node* cur = list->head;
    PARK *tmp;
    while (cur) {
        tmp = (PARK*)cur->data;
        fwrite(tmp, sizeof(PARK), 1, fp);
        cur = cur->next;
    }
    fclose(fp);
    free(tmp);
    return 0;
}