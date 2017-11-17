#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>  // socklen_t
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include "packetFormat.h"
#include "ack.h"
#include "reject.h"
#include "helper.h"

void startServer(int sock);
void parsePacket(short type, char * buf, int len, int sock);
void checkPacket(struct Data * data, int sock);

int packetLength = 0;
struct sockaddr_in clientAddr;
socklen_t clientLen;
int prev = -1;
int order[5];

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

    for(int i = 0; i < 5; i++){
        order[i] = 0;
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
            type = getType(recvbuf);
            parsePacket(type, recvbuf, packetLength,sock);
        }
        printf("\n\n");


    }
    close(sock);
}

void parsePacket(short type, char * buf, int len, int sock){
struct Data data1;
struct Ack ack1;
struct Reject reject1;

socklen_t clientLen = sizeof(clientAddr);
memset(&ack1, 0 , sizeof(ack1));
memset(&reject1, 0 , sizeof(reject1));
    switch(type){
        case 0:
            copyMemory(buf, (char *)&data1, len);
            printf("data 1' s length = %d\n",data1.length);
            printf("data 1's Id = %x\n", data1.Id);
            printf("data 1 's payload %s\n",data1.payload);
            printf("true or false %d\n", data1.length - 48 == strlen(data1.payload) ? 1 : 0);

            checkPacket(&data1,sock);

            break;
        case 1:
            copyMemory(buf, (char *)&ack1, len);
            printf("ack 1 's id %c\n",ack1.Id);
            break;
        case 2:
            copyMemory(buf, (char *)&reject1, len);
            printf("reject 1 's rejectCode %x\n",reject1.rejectCode);
            break;
        default : break;
    }
}

void checkPacket(struct Data * data, int sock){
    struct Ack ack;
    struct Reject reject;
    short rejectCode = 0;
    int index = data -> segNo - '0';
    printf("end = %x \n",data -> end);
    printf("index = %d, prev = %d\n",index, prev);
    if(prev != -1 && prev != index - 1 && prev != index){
        rejectCode = 0xFFF4;
    } else if(data -> length - 48 != strlen(data -> payload)){
        rejectCode = 0xFFF5;
    } else if(data -> end != -1){
        rejectCode = 0xFFF6;
    } else if(order[index] != 0){
        rejectCode = 0xFFF7;
    }
    if(rejectCode == 0){
        generateACK(&ack, data);
        sendto(sock, (char *)&ack, sizeof(ack), 0,
              (struct sockaddr *)&clientAddr, clientLen);
    } else {
        generateReject(&reject, data, rejectCode);
        sendto(sock, (char *)&reject, sizeof(reject), 0,
              (struct sockaddr *)&clientAddr, clientLen);
    }
    order[index] = 1;
    prev = index;
}
