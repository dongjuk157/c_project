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
  char car_number[20]; // 123��4567 
	char in_datetime[20]; // 2022-02-28 21:44:42 : \0���� �ؼ� 20�ڸ�
	char out_datetime[20];
	char car_type; // [e]lectric, [l]ight, [n]ormal
	char is_paid; // when creating
	int floor; // except 0
	int fee; // when creating, 0
} CAR_INFO;

typedef struct user_information {
  char name[10]; // ������ ����
  char phone_num[15]; // ������ ����ȣ
  char car_num[20]; // ������ ����ȣ	
  int has_ticket; // ����� ��Ͽ���, 1�̸� ��ϵ� �����
} USER_INFO;

typedef struct park { // ������
  int floor; // ��} 0 ����, + ����, - ����
  int total; // ������ �� ���� ���� ��,
  int total_car; // ������ �� ������ �� ��
  int electric_charge; // ������ ���� ���� ����, 0�̸� ����, 1�̻� ���� ���� ����
  int handicapped; //����� ���� ���� ����
  int light_car; //  ���� ���� ���� ����
} PARK;


typedef struct Car{
	char car_number[20]; // ���� ��ȣ
  char in_datetime[20]; // 2022-02-28 21:44:42 : \0���� �ؼ� 20�ڸ�
	int car_type; // ���� ����(���� , ���� , �Ϲ� ����)
} CAR;


void printInfo(Info info);

#endif // __INFO_H__

