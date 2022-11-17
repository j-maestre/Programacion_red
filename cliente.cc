#include <stdio.h>
#include "winsock.h"

int main(int argc, char** argv){
    WSADATA wsa;
    SOCKET sock, sock_c;
    
    struct sockaddr_in ip;
    
    if(WSAStartup(MAKEWORD(2,2),&wsa)){
        printf("\nError: %s\n",WSAGetLastError());
        WSACleanup(); // libero de memoria todo lo que he usao
        return 1;
    };
    // Todo OK
    sock = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    ip.sin_family = AF_INET; //Ipv4
    ip.sin_addr.s_addr = inet_addr("0.0.0.0"); // Todas las ips que tengo. Si quiero abrir un puerto solo para que el equipo local s econecte, pongo la ip de loopback
    ip.sin_port = htons(7000);

    bind(sock,(SOCKADDR*)&ip,sizeof(ip)); // Casting de Ipv4
    //listen(sock,SOMAXCONN); // Somaxconn hace que el operativo decida cuantas son las conexiones maximas que podemos
    if(connect(sock)){

    }


    return 0;
}