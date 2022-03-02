#include "manage_detail.h"

MANAGE_DETAIL_UI* createManageDetailUI(char io){
    MANAGE_DETAIL_UI *manage = createWidget();

    // 기본 위젯 Position 세팅
    setWidgetPos(manage, DEFAULT_POSY,DEFAULT_POSX);
    setWidgetSize(manage, 25, 70);
    setWidgetType(manage, MAIN);
    arrayCreate(&(manage->label));

    // Label 세팅
    Label *title = createLabel();
    setLabelPos(title, 3, 26);
    setLabelText(title,"주차 관리 프로그램");

    Label *subTitle = createLabel();
    setLabelPos(subTitle, 5, 30);
    if(io == IN_CAR) setLabelText(subTitle,"입차 관리");
    if(io == OUT_CAR) setLabelText(subTitle,"출차 관리");

    addLabel(manage,title);
    addLabel(manage,subTitle);

    return manage;
}
