#include <stdio.h>
#include "winsock.h"
#include "pkt.h"

#pragma comment(lib,"ws2_32.lib")

int main(int argc, char** argv){
    WSADATA wsa;
    SOCKET sock, s_clientes[4];
    char buffer[1024];

    int num_clients = 0;
    struct sockaddr_in ip;
    struct sockaddr_in ip_client[4];

    int ip_size = sizeof(ip);

    if(WSAStartup(MAKEWORD(2,2),&wsa)){
      printf("Error");
      WSACleanup();
      return 1;
    }

    sock = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    ip.sin_family = AF_INET;
    ip.sin_addr.s_addr = inet_addr("172.17.2.3");
    ip.sin_port = htons(9999);

    bind(sock,(SOCKADDR*)&ip,sizeof(ip));
    listen(sock,SOMAXCONN);

    s_clientes[0] = accept(sock,(SOCKADDR*)&ip_client[0],&ip_size);
    printf("-- Cliente conectado -- IP-> %s:%d\n",inet_ntoa(ip_client[0].sin_addr),ntohs(ip_client[0].sin_port));




    WSACleanup();
    return 0;
}