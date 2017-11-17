#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>  // socklen_t
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include "packetFormat.h"
#include "helper.h"
#include "request.h"
//author: Zihao Li
//student Id: W1273148

#define MYPORT 32815

void startServer(int sock);
void parsePacket(char * buf, int len, int sock);
void checkPacket(struct Request * request, int sock);

int packetLength = 0;
int count = 0;
struct sockaddr_in clientAddr;
socklen_t clientLen;

char* number[10];
int technology[10];
int paid[10];


int main(void){
    int sock;
    printf("Server Starts\n");
    printf("Listening Port : %d\n", MYPORT);


    if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
        errorOutput("socket error");
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr)); // set memory to zero;
    //initialize the serverAddr
    //htons host type bytes to network type bytes 16-bits
    //htonl host type bytes to network type bytes 32-bits
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(MYPORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0){
        errorOutput("bind error");
    }

    startServer(sock);

    return 0;
}

void startServer(int sock){
    char recvbuf[1024] = {0};
    int type;
    printf("readfile in \n");
    //read file in
    count = readFile(number, technology, paid);

    for(int i = 0; i < count; i ++){
        printf("number = %s\n",(number[i]));
        printf("technology = %d\n", technology[i]);
        printf("paid = %d\n", paid[i]);
    }
    while(1){
        clientLen = sizeof(clientAddr);
        memset(recvbuf, 0, sizeof(recvbuf));
        printf("prepareing for receiving the message\n");
        packetLength = recvfrom(sock, recvbuf, sizeof(recvbuf), 0,
                    (struct sockaddr *)&clientAddr, &clientLen);
        if(packetLength <= 0){
            if(errno == EINTR){
                continue;
            }
            errorOutput("recvfrom error");
        } else {
            printf("message received : %s\n", recvbuf);
            // parse the packet
            parsePacket(recvbuf, packetLength, sock);
        }
        printf("\n\n");
    }
    close(sock);
}

void parsePacket(char * buf, int len, int sock){
    struct Request request;
    printf("parse Packet\n");
    memset(&request, 0 , sizeof(request));
    copyMemory(buf, (char *)&request, len);
    printf("checkPacket\n");
    checkPacket(&request,sock);

}

void checkPacket(struct Request * request, int sock){
    int index = -1;
    short status = 0;
    struct Request requestRe;
    char * num = (char *)malloc(sizeof(char *));
    sprintf(num,"%u", request -> number);
    printf("phone number = %s\n", num);
    // find the number
    for(int i = 0; i < count; i++){
        if(strcmp(number[i], num) == 0){
            index = i;
            break;
        }
    }
    if(index != -1){
        printf("has found the number\n");
        if(technology[index] != (request -> technology - '0')){
            printf("technology does not match\n");
            status = 0xFFFA;
        } else if(paid[index] != 1){
            printf("subscriber does not paid\n");
            status = 0xFFF9;
        } else{
            printf("subscriber is permitted to access\n");
            status = 0xFFFB;
        }
    } else {
        printf("does not exist\n");
        status = 0xFFFA;
    }
    //(struct Request *request, short type, char technology, struct Request * requestFrom){
    generateFromRequest(&requestRe, status, request);
    sendto(sock, (char *)&requestRe, sizeof(requestRe), 0,
          (struct sockaddr *)&clientAddr, clientLen);
}
