//author : Zihao Li
//Student Id: W1273148
void generateRequest(struct Request * request, char clientId, short type, char segNo,
                char length, char technology, int number){
    request -> start = 0xFFFF;
    request -> Id = clientId;
    request -> type = type;
    request -> segNo = segNo;
    request -> length = length;
    request -> technology = technology;
    request -> number = number;
    request -> end = 0xFFFF;
}

void generateFromRequest(struct Request *request, short type, struct Request * requestFrom){
    request -> start = 0xFFFF;
    request -> Id = requestFrom -> Id;
    request -> type = type;
    request -> segNo = requestFrom -> segNo;
    request -> length = requestFrom -> length;
    request -> technology = requestFrom -> technology;
    request -> number = requestFrom -> number;
    request -> end = 0xFFFF;
}

void printRequest(struct Request * request){
    printf("start = %x \n", request -> start);
    printf("ID = %x\n", request -> Id);
    printf("type = %x\n", request -> type);
    printf("segNo = %x\n", request -> segNo);
    printf("length = %x\n", request -> length);
    printf("technology = %x\n", request -> technology);
    printf("number = %x\n", request -> number);
    printf("end = %x\n", request -> end);
}
