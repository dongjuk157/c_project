#ifndef MANAGE_H
#define MANAGE_H

#define OK            0
#define FILE_ERROR    -1
#define FORMAT_ERROR  -2

typedef struct car_informaition {
  char* car_number[20]; // 123가4567 
	char* in_datetime[20]; // 2022-02-28 21:44:42 : \0까지 해서 20자리
	char* out_datetime[20];
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

int manage_in_out(void);
int getValues(char io, CAR_INFO **car_info);
int save_log(char io, CAR_INFO *car_info);
// int save_log(char io, char* car_number);
int search_user(char *car_number, USER_INFO **user_data);
int update_current(char io, USER_INFO *user_data); 
int update_history(char io, USER_INFO *user_data);

#endif