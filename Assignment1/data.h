#include <stdio.h>

void printtest(){
    printf("test\n");
}
void generateData(struct Data * data, char clientId, char *payload, int length, char segNo){
    data -> start = 0xFFFF;
    data -> Id = clientId;
    data -> type = 0xFFF1;
    data -> segNo = segNo;
    data -> length = length;
    strcpy(data -> payload, payload);
    data -> end = 0xFFFF;
}

void generateDataNoEnd(struct Data * data, char clientId, char *payload, int length, char segNo){
    data -> start = 0xFFFF;
    data -> Id = clientId;
    data -> type = 0xFFF1;
    data -> segNo = segNo;
    data -> length = length;
    strcpy(data -> payload, payload);
    data -> end = 0x0000;
}



void printData(struct Data * data){
    printf("start = %x\t\t\n",data -> start);
    printf("clientId = %x\t\t\n", data -> Id);
    printf("type = %x\t\t\n", data -> type);
    printf("segNo = %d\t\t\n", (data -> segNo - 48));
    printf("length = %d\t\t\n", (data -> length - 48));
    printf("payload = %s\t\t\n", data -> payload);
    printf("end = %x\t\t\n", data -> end);
}
