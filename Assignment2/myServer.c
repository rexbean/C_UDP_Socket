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

#define MYPORT 32815

void startServer(int sock);
void parsePacket(short type, char * buf, int len, int sock);
void checkPacket(struct Requset * request, int sock);

int packetLength = 0;
struct sockaddr_in clientAddr;
socklen_t clientLen;
int prev = -1;
int order[5];

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
    readFile(number, technology, paid);
    
    for(int i = 0; i < 10; i ++){
        printf("number = %s\n",(number[i]));
        printf("technology = %d\n", technology[i]);
        printf("paid = %d\n", paid[i]);
    }
    // while(1){
    //     clientLen = sizeof(clientAddr);
    //     memset(recvbuf, 0, sizeof(recvbuf));
    //     printf("prepareing for receiving the message\n");
    //     packetLength = recvfrom(sock, recvbuf, sizeof(recvbuf), 0,
    //                 (struct sockaddr *)&clientAddr, &clientLen);
    //     if(packetLength <= 0){
    //         if(errno == EINTR){
    //             continue;
    //         }
    //         errorOutput("recvfrom error");
    //     } else {
    //         printf("message received : %s\n", recvbuf);
    //         parsePacket(recvbuf, packetLength, sock);
    //     }
    // }
    close(sock);
}

// void parsePacket(char * buf, int len, int sock){
//     struct Request request;
//
//     socklen_t clientLen = sizeof(clientAddr);
//     memset(&request, 0 , sizeof(request));
//     copyMemory(buf, (char *)&request, len);
//
//     checkPacket(&request,sock);
//
//     printf("generated\n");
//     for(int i = 0; i < sizeof(reject1); i++){
//         printf("%x ", *((char *)&reject1 + i));
//     }
//     printf("sent\n");
// }
//
// void checkPacket(struct Request * request, int sock){
//     int index = -1;
//     short status = 0;
//     for(int i = 0; i < n; i++){
//         if(strcmp(number[i], request -> number) == 0){
//             index = i;
//             break;
//         }
//     }
//     if(index != -1){
//         if(strcmp(technology[i], request -> technology) == 0){
//             status = 0xFFFF;
//         }
//         if()
//     }
//
//     generateACK(&ack, data);
//     sendto(sock, (char *)&ack, sizeof(ack), 0,
//               (struct sockaddr *)&clientAddr, clientLen);
//     } else {
//         generateReject(&reject, data, rejectCode);
//         sendto(sock, (char *)&reject, sizeof(reject), 0,
//               (struct sockaddr *)&clientAddr, clientLen);
//     }
//     order[index] = 1;
//     prev = index;
// }
