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
#include "request.h"

//author : Zihao Li
//student Id: W1273148
void startClient(int sock);
void parsePacket(char * buf, int len, int sock);

#define MYPORT 32815
#define BUFFSIZE 1024
char* SERVERIP = "127.0.0.1";
char clientId = 'z';

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

    int packetLength;
    short type;
    char recvbuf[1024] = {0};

    //request
    char technology[4] = {'4','3','5','3'};
    int number[4] = {4085546805, 4086668821, 4086808831, 4086484023};

    //(struct Request * request, char clientId, short type, char segNo,
                    //char length, char technology, int number)
    for(int i = 0; i < 4; i++){
        struct Request request;
        generateRequest(&request, clientId, 0xFFF8, '0','0',technology[i], number[i]);
        //printData(&data);
        printf("message send to server : %u\n", number[i]);
        sendto(sock, (char *)&request, sizeof(request), 0,
                  (struct sockaddr *)&serverAddr, sizeof(serverAddr));
        printf("send successfully\n");

        packetLength =  recvfrom(sock, recvbuf, sizeof(recvbuf), 0,
                    NULL, NULL);
        if(packetLength <= 0){
            errorOutput("recvfrom error");
        } else {
            printf("message received : \n");
            //parse the packet
            parsePacket(recvbuf, packetLength, sock);
         }
        memset(recvbuf, 0, sizeof(recvbuf));
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
    printf("request type = %x\n", request.type);
    if(request.type == (short)0xFFFB){
        printf("subscriber is permitted to access\n");
    } else if(request.type == (short)0xFFF9){
        printf("subscriber has not paid\n");
    } else if(request.type == (short)0xFFFA){
        printf("subscirber does not exist\n");
    }

}
