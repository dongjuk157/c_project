#ifndef __INFO_H__
#define __INFO_H__

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
  char name[10]; // 출입자 성명
  char phone_num[15]; // 출입자 폰번호
  char car_num[20]; // 출입자 차번호	
  int has_ticket; // 정기권 등록여부, 1이면 등록된 사용자
} USER_INFO;

typedef struct park { // 주차장
  int floor; // 층} 0 제외, + 지상, - 지하
  int total; // 주차장 내 주차 공간 수,
  int total_car; // 주차장 내 주차된 차 수
  int electric_charge; // 전기차 충전 공간 여부, 0이면 없음, 1이상 충전 공간 개수
  int handicapped; //장애인 주차 공간 여부
  int light_car; //  경차 전용 공간 여부
} PARK;


typedef struct Car{
	char car_number[20]; // 차량 번호
  char in_datetime[20]; // 2022-02-28 21:44:42 : \0까지 해서 20자리
	int car_type; // 차량 구분(경차 , 전기 , 일반 차량)
} CAR;


void printInfo(Info info);

#endif // __INFO_H__

