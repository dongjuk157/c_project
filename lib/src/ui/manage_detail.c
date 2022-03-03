#include "manage_detail.h"
#include "manage_ui.h"
MANAGE_DETAIL_UI* createManageDetailUI(char io){
    // 기본 위젯 Position 세팅
    MANAGE_DETAIL_UI *manage = createMainWidget(DEFAULT_POSY,DEFAULT_POSX,25,75);

    // Label 세팅
    labelAdd(manage, 3, 26, "주차 관리 프로그램", 0);

    if(io == IN_CAR) labelAdd(manage,5,30,"입차 관리",0);
    if(io == OUT_CAR) labelAdd(manage,5,30,"출차 관리",0);

    return manage;
}
