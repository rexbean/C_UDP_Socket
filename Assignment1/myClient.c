#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "packetFormat.h"
#include "helper.h"
#include "data.h"

void startClient(int sock);
void parsePacket(short type, char * buf, int len, int sock);

#define MYPORT 32815
#define BUFFSIZE 1024
char* SERVERIP = "127.0.0.1";
char clientId = 'z';
struct timeval timeout = {3, 0};

int main(void){
    int sock;
    if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
        errorOutput("socket error\n");
    }
    printf("start client\n");
    startClient(sock);
    return 0;
}

void startClient(int sock){
    struct sockaddr_in serverAddr;
    struct sockaddr_in fromAddr;
    memset(&fromAddr, 0, sizeof(fromAddr));
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(MYPORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVERIP);

    int packetLength = 0;
    short type;
    char recvbuf[1024] = {0};
    int timesOfSend[5] = {0};
    char* payloadArray[5];

    payloadArray[0] = "123";
    payloadArray[1] = "456";
    payloadArray[2] = "789";
    payloadArray[3] = "101";
    payloadArray[4] = "112";
    //data
    for(int i = 0; i < 5; i++){
        struct Data data;
        int outOftime = 0;
        int isFirst = 1;
        generateData(&data, clientId, payloadArray[i], '3', (char)(i + 48));
        //printData(&data);
        //set a timeout option
        setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));

        printf("message send to server : %s\n", (char *)&data);
        sendto(sock, (char *)&data, sizeof(data), 0,
              (struct sockaddr *)&serverAddr, sizeof(serverAddr));
        printf("send1 successfully\n");

        packetLength = recvfrom(sock, recvbuf, sizeof(recvbuf), 0,
                NULL, NULL);
        while(packetLength == -1 && errno == EAGAIN){
            printf("do not receive ack %d times\n", ++timesOfSend[i]);
            if(timesOfSend[i] <= 3){
                sendto(sock, (char *)&data, sizeof(data), 0,
                      (struct sockaddr *)&serverAddr, sizeof(serverAddr));
                packetLength = recvfrom(sock, recvbuf, sizeof(recvbuf), 0,
                              NULL, NULL);
            } else {
                printf("bad connection!\n");
                outOftime = 1;
                break;
            }
        }
        if(outOftime != 1){
            printf("message received : \n");
            type =  getType(recvbuf);
            parsePacket(type, recvbuf, packetLength,sock);
        }
        memset(recvbuf, 0, sizeof(recvbuf));
    }
    close(sock);
}

void parsePacket(short type, char * buf, int len, int sock){
struct Data data1;
struct Ack ack1;
struct Reject reject1;
memset(&ack1, 0 , sizeof(ack1));
memset(&reject1, 0 , sizeof(reject1));
    switch(type){
        case 0:
            copyMemory(buf, (char *)&data1, len);
            break;
        case 1:
            copyMemory(buf, (char *)&ack1, len);
            printf("ack received for %c\n",ack1.segNo);
            break;
        case 2:
            copyMemory(buf, (char *)&reject1, len);
            printf("reject 1 's rejectCode %x\n",reject1.rejectCode);
            break;
        default : break;
    }
}
