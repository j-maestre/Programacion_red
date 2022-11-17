#include <stdio.h>
#include "winsock.h"
#include "structs.h"

#pragma comment(lib,"ws2_32.lib")

int main(int argc, char** argv){
  WSADATA wsa;
  SOCKET sock;
  
  struct sockaddr_in ip,ip_c;
  char buffer[1024];

  WSAStartup(MAKEWORD(2,2),&wsa);
  sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
  ip.sin_family = AF_INET;
  ip.sin_addr.s_addr = inet_addr("172.17.2.3");
  ip.sin_port = htons(9999);

  struct UDP_Paquete paquete;

  //Mensaje inicial al server
  paquete.id = PKT_Conn;
  sendto(sock,(char*)&paquete,sizeof(paquete),0,(SOCKADDR*)&ip,sizeof(ip));

  //Recibimos el id que nos ha dado el servidor
  int id;
  int id_tmp;
  int bytes = 0;
  printf("Esperando id...\n");
  while(bytes<=0){
    struct UDP_Paquete newid;
    recvfrom(sock,(char*)&newid,sizeof(newid),0,(SOCKADDR*)&ip,sizeof(ip));
    //bytes = recvfrom(sock,id_tmp,sizeof(id_tmp),0,(SOCKADDR*)&ip,sizeof(ip));
    if(bytes>0){
      id = newid.id;
      printf("Id asignado-> %d\n",id);
    }
  }

  printf("\n");
  



  while(1){
    memset(buffer,'\0',sizeof(buffer));
    printf("Id del mensaje: ");
    scanf("%d",paquete.datos.id);
    getchar();
    printf("Manda el mensaje: ");
    fgets(paquete.datos.cmd,sizeof(paquete.datos.cmd),stdin);

    //buffer[strcspn(buffer,"\n")] = '\0';
    sendto(sock,(char*)&paquete,sizeof(paquete),0,(SOCKADDR*)&ip,sizeof(ip));
  }
    
  return 0;
}