#include <stdio.h>
void generateReject(struct Reject *reject1, struct Data *data1, short rejectCode){
    reject1 -> start = 0xFFFF;
    reject1 -> Id = data1 -> Id;
    reject1 -> type = 0xFFF3;
    reject1 -> rejectCode = rejectCode;
    reject1 -> segNo = data1 -> segNo;
    reject1 -> end = 0xFFFF;
}

void printReject(struct Reject *reject){
    printf("start = %x\t\n", reject -> start);
    printf("Id = %x\t\n", reject -> Id);
    printf("type = %x\t\n", reject -> type);
    printf("rejectCode = %x\t\n", reject -> rejectCode);
    printf("segNo = %d\t\n", reject -> segNo - 48);
    printf("end = %x\t\n", reject -> end);
}
