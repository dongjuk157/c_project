#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"

int main(int argc, char const *argv[])
{
    FILE *fp = fopen("./ParkingLot.dat","wb");
    if(fp == NULL){
        printf("error");
        return -1;
    }

    PARK p1 = {3,10,0,1,2,1};
    fwrite(&p1,sizeof(PARK), 1, fp);

    PARK p2 = {2,10,0,1,2,1};
    fwrite(&p2,sizeof(PARK), 1, fp);

    PARK p3 = {1,10,0,1,2,1};
    fwrite(&p3,sizeof(PARK), 1, fp);

    PARK p4 = {-1,10,0,1,2,1};
    fwrite(&p4,sizeof(PARK), 1, fp);

    PARK p5 = {-2,10,0,1,2,1};
    fwrite(&p5,sizeof(PARK), 1, fp);

    PARK p6 = {-3,10,0,1,2,1};
    fwrite(&p6,sizeof(PARK), 1, fp);

    fclose(fp);

   
    return 0;
}
