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

void printInfo(Info info);

#endif // __INFO_H__
