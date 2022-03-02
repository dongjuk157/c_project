#include "join.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcat
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

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
    fp = fopen(tmp_file_name, "w");
    fclose(fp);

    // initialize data/{id}/History.dat
    tmp_file_name[0] = '\0'; // 초기화
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/History.dat");
    fp = fopen(tmp_file_name, "w"); 
    fclose(fp);

    // initialize data/{id}/ParkingLot.dat
    tmp_file_name[0] = '\0'; // 초기화
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/ParkingLot.dat");
    fp = fopen(tmp_file_name, "w");
    fclose(fp);

    // initialize data/{id}/User.dat
    tmp_file_name[0] = '\0'; // 초기화
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/User.dat");
    fp = fopen(tmp_file_name, "w");
    fclose(fp);

    // initialize data/{id}/history.log
    tmp_file_name[0] = '\0'; // 초기화
    strcat(tmp_file_name, dirname);
    strcat(tmp_file_name, "/history.log");
    fp = fopen(tmp_file_name, "w");
    fclose(fp);


    return 0;
}