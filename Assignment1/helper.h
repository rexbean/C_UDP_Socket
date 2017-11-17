#include <stdio.h>
#include<unistd.h>  // socklen_t
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
//author : Zihao Li
//Student Id: W1273148
short getType(char * buf){
    short type = 0;
    int i = 0;
    //printf("getType\n");
    //showMessage(buf);
    type = (*(buf + 5))<<8 | (*(buf + 4));
    printf("the type is %x\n",type);
    if(type == (short)0xfff1){
        return 0;
    } else if(type == (short)0xfff2){
        return 1;
    } else if(type == (short)0xfff3){
        return 2;
    } else {
        return -1;
    }
}


void showMessage(char * buf, int packetLength){
    for(int i = 0;i < packetLength; i++){
        printf("%x ", *(buf +i));
    }
}
void copyMemory(char * src, char * des, int len){
    for(int i = 0 ; i < len; i++){
        *(des + i) = *(src + i);
    }
}

void errorOutput(char * error){
    perror(error);
}
