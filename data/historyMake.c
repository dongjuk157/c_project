#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct car_informaition {
        char car_number[20]; // 123가4567 
        char in_datetime[20]; // 2022-02-28 21:44:42 : \0까지 해서 20자리
        char out_datetime[20];
        char car_type; // [e]lectric, [l]ight, [n]ormal
        char is_paid; // when creating
        int floor; // except 0
        int fee; // when creating, 0
} CAR_INFO;

int main(){

        FILE *fp = fopen("history.dat", "wb");
        CAR_INFO *carInfo = (CAR_INFO *)malloc(sizeof(CAR_INFO));

//현재 주차되어있는 차량 111가1111
        strcpy(carInfo->car_number, "111가1111");
        strcpy(carInfo->in_datetime, "2022-02-28 00:00:00");
        strcpy(carInfo->out_datetime, "xxx");
        // strcpy(carInfo->car_type, "");
        // strcpy(carInfo->is_paid, "");
        // strcpy(carInfo->floor, 0);
        carInfo->fee = 0;


        fwrite(carInfo, sizeof(CAR_INFO), 1, fp);
//출차완료 & 정산완료 차량
        strcpy(carInfo->car_number, "222가2222");
        strcpy(carInfo->in_datetime, "2022-02-28 12:11:11");
        strcpy(carInfo->out_datetime, "2022-02-29 13:11:11");
        // strcpy(carInfo->car_type, "");
        // strcpy(carInfo->is_paid, "");
        // strcpy(carInfo->floor, 0);
        carInfo->fee = 0;

        fwrite(carInfo, sizeof(CAR_INFO), 1, fp);
//출차완료 & 아직 미정산
        strcpy(carInfo->car_number, "111가1111");
        strcpy(carInfo->in_datetime, "2022-02-28 00:00:00");
        strcpy(carInfo->out_datetime, "2022-02-29 11:11:11");
        // strcpy(carInfo->car_type, "");
        // strcpy(carInfo->is_paid, "");
        // strcpy(carInfo->floor, 0);
        carInfo->fee = 3000;

        fwrite(carInfo, sizeof(CAR_INFO), 1, fp);

        free(carInfo);
        fclose(fp);

    return 0;
}

