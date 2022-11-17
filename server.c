#include <stdio.h>
#include "winsock.h"
#include "pkt.h"
#include "structs.h"

#pragma comment(lib,"ws2_32.lib")

int main(int argc, char** argv){
    WSADATA wsa;
    SOCKET sock, clients[4];
    char buffer[1024];
    char buffer_clients[1024];

    struct Paquete paquete;

    int num_clients = 0;
    struct sockaddr_in ip;
    struct sockaddr_in ip_client;
    int ip_size = sizeof(ip);
    
    if(WSAStartup(MAKEWORD(2,2),&wsa)){
        printf("\nError: %d\n",WSAGetLastError());
        WSACleanup(); // libero de memoria todo lo que he usao
        return 1;
    };
    //* Todo OK
    sock = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    ip.sin_family = AF_INET; //Ipv4
    ip.sin_addr.s_addr = inet_addr("172.17.2.3"); // Todas las ips que tengo. Si quiero abrir un puerto solo para que el equipo local se conecte, pongo la ip de loopback
    ip.sin_port = htons(9999);

    bind(sock,(SOCKADDR*)&ip,sizeof(ip)); // Casting de Ipv4
    listen(sock,SOMAXCONN); // Somaxconn hace que el operativo decida cuantas son las conexiones maximas que podemos
    
    int nobloqueado = 1;
    while(num_clients<3){
      // Esperando a que se conecte un cliente
      //clients[num_clients] = accept(sock,(SOCKADDR*)&ip_client[num_clients],&ip_size);
      //printf("--Cliente conectado-- IP[ %s:%d ]\n",inet_ntoa(ip_client[num_clients].sin_addr),ntohs(ip_client[num_clients].sin_port)); // convertimos la ip que esta en big endian a little endian
      clients[num_clients] = accept(sock,(SOCKADDR*)&ip_client,&ip_size);
      ioctlsocket(clients[num_clients],FIONBIO,&nobloqueado); //Marcamos el socket del cliente como no bloqueante
      
      printf("--Cliente conectado-- IP[ %s:%d ]\n",inet_ntoa(ip_client.sin_addr),ntohs(ip_client.sin_port)); // convertimos la ip que esta en big endian a little endian
      num_clients++;
    }

    printf("***** Clientes conectaos *****\n");
    snprintf(buffer,1024,"Bienvenido chaval\0");
    for(int i = 0; i<num_clients; i++){
      send(clients[i],buffer,sizeof(buffer),0);
    }

    int bytes = 0;
    int total_clientes;
    int total_productos;
    while(1){
      memset(&paquete,'\0',sizeof(paquete));
      for(int i = 0; i<3; i++){
        bytes = recv(clients[i],(char*) &paquete,sizeof(paquete),0);
        if(bytes>0){

          if(paquete.id == 0){
            printf("Cliente %d manda un paquete de cliente con id-> %d\n",i,paquete.id);
            printf("Nombre-> %s\n",paquete.cliente.nombre);
          }else{
            printf("Cliente %d manda un paquete de producto con id-> %d\n",i,paquete.id);
            printf("Nombre del producto-> %s, precio-> %d\n",paquete.producto.producto, paquete.producto.precio);
          }
        }
      }
    }

    /*for (int i = 0; i <3; i++){
      memset(buffer,'\0',1024);
      recv(clients[i],buffer,sizeof(buffer),0);
      printf("Cliente %d dice-> %s\n",i,buffer);
      closesocket(clients[i]);
    }*/

    
    

    //while(1){
        //printf("Meteme la cadena: ");
        //strcat(buffer,"Bienvenido chaval");
        //gets(buffer);
        //send(clients[0],buffer,strlen(buffer),0);

        
        //memset(buffer,'\0',sizeof(buffer));
        //recv(clients[0],buffer,sizeof(buffer),0);
        //printf("\nRecibido: %s \n",buffer);
        //memset(buffer,'\0',sizeof(buffer));
    //}

    
    //recv(clients[0],buffer,sizeof(buffer),0);

    //printf("\nRecibid: %s\n",buffer);
    WSACleanup();
    return 0;
}