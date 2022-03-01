#include "info.h"
#include "manage.h"
#include <stdio.h>

void printInfo(Info info){
    
}

int readUserData(LPHASH *hash){
    FILE *fp = fopen(USER_DATA_FILE_PATH, "rb");
    if(fp==NULL){
        return -1;
    }
    USER_INFO *tmp_user;
    while (1){
        USER_INFO *tmp_user = (USER_INFO *)malloc(sizeof(USER_INFO));
        fread(tmp_user, sizeof(USER_INFO), 1, fp);
        if (feof(fp)) 
            break;
        hashSetValue(*hash, tmp_user->car_num, tmp_user);
    }
    fclose(fp);
}

int readParkingLot(LinkedList* list){
    FILE* fp = fopen(PARKINGLOT_SETTINGS_FILE_PATH, "rb");
    if(fp==NULL){
        return -1;
    }
    while (1){
        PARK *tmp_park = (PARK *)malloc(sizeof(PARK));
        fread(tmp_park, sizeof(PARK), 1, fp);
        if (feof(fp)) 
            break;
        
        list_push_back(list, tmp_park);
    }
    fclose(fp);
}

int readCurrentData(LinkedList* list){
    // 파일 current.dat 읽어서 리스트 생성
    FILE* fp = fopen(CURRENT_DATA_FILE_PATH, "rb");
    if(fp==NULL){
        return -1;
    }
    
    while (1){
        CAR_INFO *tmp_car_info = (CAR_INFO *)malloc(sizeof(CAR_INFO));
        fread(tmp_car_info, sizeof(CAR_INFO), 1, fp);
        if (feof(fp)) 
            break;
        list_push_back(&list, tmp_car_info);
    }
    fclose(fp);
}

int saveUserData(LPHASH hash){
    FILE* fp = fopen(USER_DATA_FILE_PATH, "wb");
	LPNODE lpNode, lpTemp;
    for (int i=0; i < hash->nHashSize; i++) {
		lpNode = hash->array[i];
		while (lpNode) {
			//노드 메모리를 제거한다.
            fwrite((USER_INFO *)lpNode->value, sizeof(USER_INFO), 1, fp);
            lpNode = lpNode->pNext;
		}
	}
    fclose(fp);
    return 0;
}