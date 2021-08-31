#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32 // windows (-l wsock32)
#include <winsock2.h>
#include <ws2tcpip.h>
#else // Linux
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

typedef struct {
    char servername[20];
    char policy[50][50];
    char digest[256];
    unsigned int list_cnt;
    unsigned int recv_time;
} Information;

int main(int argc, char **argv){
    // set port
    int serverPort = 8080;
    if(argc == 2)
        serverPort = atoi(argv[1]);
    printf("Listening Ports : %d\n\n", serverPort);


    //Winsows啟用socket
    #ifdef _WIN32
    WSADATA wsadata;
    if(WSAStartup(MAKEWORD(2,2), &wsadata) == SOCKET_ERROR) {
        printf("WSAStartup() fail\n");
        exit(1);
    }
    #endif


    // 建立socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Fail to create a socket.\n");
        exit(1);
    }

    // socket 綁定
    struct sockaddr_in clientAddr, serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(serverPort);

    int err = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if(err == -1) {
        printf("Bind failed.\n");
        exit(1);
    }

    // 監聽連線
    listen(sockfd, 3);
    printf("Listening...\n");

    socklen_t addrlen = sizeof(clientAddr);
    char buffer[1024] = "Server have received your data.";
    char receiveMsg[1024];

    Information info;
    strcpy(info.servername, "HSCC");
    strcpy(info.policy[0], "/usr/bin/take_picture_demo /usr/bin/blur_image_demo");
    info.list_cnt = 1;

    strcpy(info.digest, "GIjWPZ");
    info.recv_time = 0;

    while(1){  // receive data
        int connfd = accept(sockfd, (struct sockaddr *) &clientAddr, &addrlen);
        if(connfd == -1) {
            printf("Accept failed.\n");
            exit(1);
        }

        char *client_ip = inet_ntoa(clientAddr.sin_addr);
        int client_port = ntohs(clientAddr.sin_port);
        printf("Connect form:%s Port:%d\n", client_ip, client_port);

        while(recv(connfd, receiveMsg, 1024, 0) > 0){
            printf("Received data: %s \n", receiveMsg);
            //send(connfd, buffer, strlen(buffer)+1, 0);
            send(connfd, (void *)&info, sizeof(info), 0);
        }

        printf("Socket closed.\n");

        // close socket
        #ifdef _WIN32
        closesocket(connfd);
        #else
        close(connfd);
        #endif
    }

    return 0;
}
