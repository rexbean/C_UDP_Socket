void generateACK(struct Ack *ack1, struct Data *data1){
    ack1 -> start = 0xFFFF;
    ack1 -> Id = data1 -> Id;
    ack1 -> type = 0xFFF2;
    ack1 -> segNo = data1 ->segNo;
    ack1 -> end = 0xFFFF;
}

void printAck(struct Ack *ack){
    printf("start = %x \n", ack->start);
    printf("Id = %x \n", ack -> Id);
    printf("type = %x \n", ack-> type);
    printf("segNo = %x \n", ack -> segNo);
    printf("end = %x \n", ack -> end);
}
