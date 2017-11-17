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

    struct Request request;
    //(struct Request * request, char clientId, short type, char segNo,
                    //char length, char technology, int number)
    generateRequest(&request, clientId, 0xFFF8, '0','0','2', 4085546805);
    //printData(&data);
    printf("message send to server : %s\n", (char *)&request);
    sendto(sock, (char *)&request, sizeof(request), 0,
              (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    printf("send1 successfully\n");

    packetLength =  recvfrom(sock, recvbuf, sizeof(recvbuf), 0,
                NULL, NULL);
    if(packetLength <= 0){
        errorOutput("recvfrom error");
    } else {
        printf("message received : \n");
        parsePacket(recvbuf, packetLength, sock);
     }
    memset(recvbuf, 0, sizeof(recvbuf));
    close(sock);
}

void parsePacket(char * buf, int len, int sock){
    struct Request request;
    printf("parse Packet\n");
    //socklen_t clientLen = sizeof(clientAddr);
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
