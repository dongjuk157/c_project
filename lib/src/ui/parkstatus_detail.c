#include "parkstatus_detail.h"
#include "linkedlist.h"
#include "messagebox.h"
#include "info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// extern LinkedList current_list;

PARK_DETAIL_UI* createParkDetailEntryUI(){
    PARK_DETAIL_UI* park_detail = createMainWidget(DEFAULT_POSY,DEFAULT_POSX,25,70);

    labelAdd(park_detail,5,26,"주차 관리 프로그램",0);
    labelAdd(park_detail,7,24,"[주차 현황 - 전체 조회]",0);

    Widget* detailSub = createSubWidget(14,4,5,63);

    labelAdd(detailSub,0,0,"┌─────────┬───────────┬─────────────┬───────────┬─────────────┐",0);
    labelAdd(detailSub,1,0,"│ 총 공간 │ 남은 공간 │ 전기차 전용 │ 경차 전용 │ 장애인 전용 │",0);
    labelAdd(detailSub,2,0,"├─────────┴───────────┴─────────────┴───────────┴─────────────┤",0);

    addWidget(park_detail,detailSub);

    return park_detail;
}

PARK_DETAIL_UI* createParkDetailFloorUI(){
    PARK_DETAIL_UI* park_detail = createMainWidget(DEFAULT_POSY,DEFAULT_POSX,25,81);

    labelAdd(park_detail,5,32,"주차 관리 프로그램", 0);
    labelAdd(park_detail,7,30,"[주차 현황 - 층별 조회]", 0);
    
    Widget* detailSub = createSubWidget(8,5,15,70);

    labelAdd(detailSub,0,0,"┌──────┬─────────┬───────────┬─────────────┬───────────┬─────────────┐",0);
    labelAdd(detailSub,1,0,"│ 층수 │ 총 공간 │ 남은 공간 │ 전기차 전용 │ 경차 전용 │ 장애인 전용 │",0);
    labelAdd(detailSub,2,0,"├──────┴─────────┴───────────┴─────────────┴───────────┴─────────────┤",0);

    addWidget(park_detail,detailSub);

    return park_detail;
}

PARK_DETAIL_UI* createParkDetailOtherUI(){
    PARK_DETAIL_UI* park_detail = createMainWidget(DEFAULT_POSY,DEFAULT_POSX,25,70);

    labelAdd(park_detail,5,26,"주차 관리 프로그램",0);
    labelAdd(park_detail,7,21,"[주차 현황 - 타 주차장 조회]",0);

    Widget* detailSub = createSubWidget(8,4,15,63);

    labelAdd(detailSub,0,0,"┌─────────┬───────────┬─────────────┬───────────┬─────────────┐",0);
    labelAdd(detailSub,1,0,"│ 총 공간 │ 남은 공간 │ 전기차 전용 │ 경차 전용 │ 장애인 전용 │",0);
    labelAdd(detailSub,2,0,"├─────────┴───────────┴─────────────┴───────────┴─────────────┤",0);

    addWidget(park_detail,detailSub);

    return park_detail;
}


int renderDetailEntry(PARK_DETAIL_UI* park_detail){
    renderWidget(park_detail);

    PARK total;
    memset(&total,0,sizeof(PARK));
    
    Node* temp = current_list.head;
    while(temp){
        PARK* buf = (PARK *)temp->data;
        total.total += buf->total;
        total.total_car += buf->total_car;
        total.electric_charge += buf->electric_charge;
        total.handicapped += buf->handicapped;
        total.light_car += buf->light_car;
        temp = temp->next;
    }

    char buffer[100];

    sprintf(buffer,"현재 주차가능 공간 수는 %d개 입니다.", total.total - total.total_car);
    printSiglelineWidget(park_detail, 10, 10, buffer, 0);

    sprintf(buffer," %5d      %5d         %4d         %4d         %4d", 
        total.total,
        total.total - total.total_car,
        total.electric_charge,
        total.light_car,
        total.handicapped
    );
    printSiglelineWidget(park_detail, 17, 5, buffer, 0);


    return 0;
}

int renderDetailFloor(PARK_DETAIL_UI* park_detail){
    renderWidget(park_detail);

    Node* temp = current_list.head;
    for (int i = 0; i < list_size(&current_list); i++)
    {
        PARK* buf = (PARK *)temp->data;
        char buffer[100];
        sprintf(buffer,"%2d층   %5d       %5d       %4d          %4d        %4d", 
            buf->floor,
            buf->total,
            buf->total - buf->total_car,
            buf->electric_charge,
            buf->light_car,
            buf->handicapped
        );
        printSiglelineWidget(park_detail, 11 + i*2, 7, buffer, 0);
        temp = temp->next;
    }

    return 0;
}

int renderDetailOther(PARK_DETAIL_UI* park_detail){
    // 여기서 사용할 리스트 생성
    LinkedList all_parking_lots;
    create_linked_list(&all_parking_lots);

    // 모든 파일 읽기
    FILE *fp_user = fopen("./data/user.dat","rb");
    if (!fp_user){
        return -1;
    }
    USER *tmp_user = (USER *)malloc(sizeof(USER));
    char *tmp_datapath = (char *)malloc(sizeof(char)*500);
    while (1) {
        fread(tmp_user, sizeof(USER), 1, fp_user);
        if (feof(fp_user)) 
            break;
        // id를 사용해서 폴더 구조 파악-> ./data/{tmp_user->id}/ParkingLot.dat 확인
        sprintf(tmp_datapath,"./data/%s/ParkingLot.dat", tmp_user->id);
        // parkinglot에서 파일 읽고 데이터 만들기

        FILE *fp_data = fopen(tmp_datapath, "rb");
        // total에 한 주차장의 모든 데이터를 더한 값 저장
        if(!fp_data){
            continue;
            // return -1;
        }
        PARK *total = (PARK *)malloc(sizeof(PARK)); // list에 넣을 값    
        memset(total,0,sizeof(PARK)); // 0으로 초기화

        PARK *tmp_park = (PARK *)malloc(sizeof(PARK)); 
        while (1) {
            fread(tmp_park, sizeof(PARK), 1, fp_data); // PARK 구조 읽고
            if (feof(fp_data))
                break;
            // 더하기
            ++(total->floor); // 여기서 floor는 주차장 층수 합
            total->total += tmp_park->total;
            total->total_car += tmp_park->total_car;
            total->electric_charge += tmp_park->electric_charge;
            total->handicapped += tmp_park->handicapped;
            total->light_car += tmp_park->light_car;
        }
        list_push_back(&all_parking_lots, total);
        free(tmp_park);
        fclose(fp_data);
    }
    fclose(fp_user);
    free(tmp_datapath);
    free(tmp_user);
    
    renderWidget(park_detail);

    char buffer[100];
    Node* cur = all_parking_lots.head;    
    // 모든값 보여줌
    int cnt=0;
    while (cnt < list_size(&all_parking_lots)){
        if (!cur) break; // 내부에서 break걸리거나 처음부터 null일때 break
        
        renderEmpty(park_detail);
        renderWidget(park_detail);
        for (int i = 0; i < 6; i++){ // 5개씩 한번에 보여줌
            if (!cur) break; // 5개보다 작으면 break
            PARK* tmp_data;
            tmp_data = (PARK *) cur->data;
            
            sprintf(buffer," %5d      %5d         %4d         %4d         %4d", 
                tmp_data->total,
                tmp_data->total - tmp_data->total_car,
                tmp_data->electric_charge,
                tmp_data->light_car,
                tmp_data->handicapped
            );
            printSiglelineWidget(park_detail, 11 + 2 * i, 5, buffer, 0);
            cnt++;
            cur = cur->next;
        }
        // printf(" %d %d ", cnt-1/5, ((list_size(&all_parking_lots)-1)/5));
        getchar();
        if((cnt-1)/6 == ((list_size(&all_parking_lots)-1)/6)){
            messageBox(park_detail,7,17,"마지막 페이지 입니다.");
            return HOME;
        }
        else if(messageBox(park_detail,7,17,"다음페이지를 보시겠습니까?")==ID_CANCLE){
            return HOME;
        }
    }


    list_clear(&all_parking_lots); //리스트 해제
    return HOME;
}