#ifndef __INFO_H__
#define __INFO_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "hash.h"
#include "array.h"

#define CURRENT_DATA_FILE_PATH          "./data/tempData/Current.dat"
#define SIMPLE_LOG_FILE_PATH    		"./data/tempData/history.log"
#define USER_DATA_FILE_PATH     		"./data/tempData/User.dat"
#define HISTORY_DATA_FILE_PATH     		"./data/tempData/History.dat"
#define PARKINGLOT_SETTINGS_FILE_PATH   "./data/tempData/ParkingLot.dat"  

#define INFO_EOK 0


#define ERROR_INFO_CAR_NOT_FOUND -100
#define ERROR_INFO_USER_NOT_FOUND -101

LPHASH user;
LinkedList current_list;
LinkedList current_car_list;

typedef struct User {
  char id[20];
  char passward[20];
} USER;

typedef struct Info{
    char carNumber[20];
    char name[10];
    char phoneNumber[15];
    char inDatetime[30];
    int fee;
}Info;

typedef struct car_informaition {
   char car_number[20]; // 123가4567 
   char in_datetime[20]; // 2022-02-28 21:44:42 : \0까지 해서 20자리
   char out_datetime[20];
   char car_type; // [e]lectric, [l]ight, [n]ormal
   char is_paid; // when creating
   int floor; // except 0
   int fee; // when creating, 0
} CAR_INFO;

typedef struct user_information {
  char name[20]; // 출입자 성명
  char phone_num[15]; // 출입자 폰번호
  char car_num[20]; // 출입자 차번호	
  int has_ticket;
  char recentTicket[20]; // has_ticket 삭제, ""이면 등록 안됨, "2022-02-28"
} USER_INFO;

typedef struct park { // 주차장
  int floor; // 층} 0 제외, + 지상, - 지하
  int total; // 주차장 내 주차 공간 수,
  int total_car; // 주차장 내 주차된 차 수
  int electric_charge; // 전기차 충전 공간 여부, 0이면 없음, 1이상 충전 공간 개수
  int handicapped; //장애인 주차 공간 여부
  int light_car; //  경차 전용 공간 여부
} PARK;

int readUserData(LPHASH *hash);
int readParkingLot(LinkedList* list);
int readCurrentData(LinkedList* list);

int saveUserData(LPHASH hash);
int saveParkingLot(LinkedList list);
int saveCurrentCarData(LinkedList list);

int findCarInfo(char* carNumber, CAR_INFO** carinfo);
int searchUser(char* carNumber, USER_INFO** userData);

#endif // __INFO_H__

