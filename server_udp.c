#include <stdio.h>
#include "winsock.h"
#include "structs.h"

#pragma comment(lib,"ws2_32.lib")

int main(int argc, char** argv){
  WSADATA wsa;
  SOCKET sock;
  
  struct sockaddr_in ip,ip_c[5];
  char buffer[1024];
  int bytes = 0;
  int ip_size = sizeof(ip);

  //printf("mamahuebaso");

  WSAStartup(MAKEWORD(2,2),&wsa);
  sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
  ip.sin_family = AF_INET;
  ip.sin_addr.s_addr = inet_addr("172.17.2.3");
  ip.sin_port = htons(9999);
  bind(sock,(SOCKADDR*)&ip,sizeof(ip));
  //printf("mamahuebo");

  struct UDP_Paquete paquete;
  int total_clientes = 0;

  while(total_clientes<4){
    printf("Esperando a que se conecten %d mas\n",4-total_clientes);
    bytes = recvfrom(sock,(char*)&paquete,sizeof(paquete),0,(SOCKADDR*)&ip_c[total_clientes],&ip_size);

    if(bytes>0){
      printf("Ha entrado uno de tipo %d\n",paquete.id);
      if(paquete.id == PKT_Conn){
        printf("El paquete es de conection\n");
        total_clientes++;
        bytes = 0;
        //printf("Enviando id %d al cliente\n",total_clientes);
      
        struct UDP_Paquete paq;
        paq.id = total_clientes;
        sendto(sock,(char*)&paq,sizeof(paq),0,(SOCKADDR*)&ip_c[total_clientes],&ip_size);
        printf("error-> %d\n",WSAGetLastError());
        
        
        //int error = sendto(sock,total_clientes,sizeof(total_clientes),0,(SOCKADDR*)&ip_c[total_clientes],&ip_size);
        //printf("Errores-> %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",WSAEINTR,WSAEINPROGRESS,WSAEFAULT,WSAENETRESET,WSAENOBUFS,WSAENOTCONN,WSAENOTSOCK,WSAEOPNOTSUPP,WSAESHUTDOWN,WSAEWOULDBLOCK,WSAEMSGSIZE,WSAEHOSTUNREACH);
        //printf("%d\n",error);
      }

    }

  }

  while(1){
    memset(buffer,'\0',sizeof(buffer));
    bytes = recvfrom(sock,(char*)&paquete,sizeof(paquete),0,(SOCKADDR*)&ip_c,&ip_size);
    printf("Despues del recive");
    if(bytes > 0){
      //Recibido algo
      printf("\nRecibido mensaje : %s",buffer);
    }
  }
    
  return 0;
}