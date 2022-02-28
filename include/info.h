#if !defined(__INFO_H__)
#define __INFO_H__

typedef struct Info{
    char carNumber[20];
    char name[10];
    char phoneNumber[15];
    char inDatetime[30];
    int fee;
}Info;

void printInfo(Info info);

#endif // __INFO_H__
