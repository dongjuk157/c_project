#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "manage.h"
#include "manage_ui.h"

extern LPHASH user;
extern LinkedList current_list;
extern LinkedList current_car_list;


// �����ϱ� ��� ���ý� ��Ÿ�� UI ���� -> ������ Widget ����ü�� ������ ����
MANAGE_UI* createManageUI(){

    MANAGE_UI *manage = (MANAGE_UI *)malloc(sizeof(MANAGE_UI));

    // �⺻ ���� Position ����
    setWidgetPos(manage, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(manage, 25, 70);
    setWidgetType(manage, MAIN);
    arrayCreate(&(manage->label));

    // Label ����
    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"���� ���� ���α׷�");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 31);
    setLabelText(subTitle,"������ ����");

    Label *selectOne = createLabel();
    setLabelPos(selectOne, 13, 10);
    setLabelText(selectOne,"1. ����");

    Label *selectTwo = createLabel();
    setLabelPos(selectTwo, 16, 10);
    setLabelText(selectTwo,"2. ����");

    Label *prompt = createLabel();
    setLabelPos(prompt, 20, 10);
    setLabelText(prompt,"����� �����ϼ��� >> ");

    // ������ Label Widget.label ���� �迭�� ���
    addLabel(manage, title);
    addLabel(manage, subTitle);
    addLabel(manage, selectOne);
    addLabel(manage, selectTwo);
    addLabel(manage, prompt);

    return manage;
}

int renderManageUI(MANAGE_UI *manage){
    //UI ������ �׸���
    renderWidget(manage);
    
    //���õ� label ���
    for (int i = 0; i < arraySize(manage->label); i++)
        printLabel(manage, (Label *)(manage->label->lpData)[i]);

    //prompt�� ���� ���óѹ� | exit - home | 1,2 - �� Page�� | �̿� - �ٽ��Է� |
    char selectNumber[8];

    //User���� �Է¹ް� ���๮�� ����
    fgets(selectNumber, 8, stdin);
    selectNumber[strlen(selectNumber)-1] = '\0';
    
    if(!strcmp("exit", selectNumber))
        return HOME;

    int num = atoi(selectNumber);
    if(num == 1){
        // ����
        getValuesUI('i');
        
    } else if(num == 2){
        // ����
        getValuesUI('o');
    } else{
        system("clear");
    }
    return HOME;
}

int getValuesUI(char io){

}