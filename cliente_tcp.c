#include <stdio.h>
#include "winsock.h"
#include "structs.h"
#pragma comment(lib,"ws2_32.lib")

int main(int argc, char** argv){
    WSADATA wsa;
    SOCKET sock;
    char buffer[1024];
    char msg_to_server[1024] = {"Ole los caracoles\n"};
    int bytes = 0;


    struct sockaddr_in ip;
    struct Paquete paquete;
    memset(&paquete,'\0',sizeof(paquete));
    
    if(WSAStartup(MAKEWORD(2,2),&wsa)){
        printf("\nError: %d\n",WSAGetLastError());
        WSACleanup(); // libero de memoria todo lo que he usao
        return 1;
    };
    //En el cliente no se bindea, solo en el servidor
    // Todo OK
    sock = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP); // SOCK STREAM-> TCP
    ip.sin_family = AF_INET; //Ipv4
    ip.sin_addr.s_addr = inet_addr("172.17.2.3"); // Todas las ips que tengo. Si quiero abrir un puerto solo para que el equipo local se conecte, pongo la ip de loopback
    ip.sin_port = htons(9999);

    connect(sock,(SOCKADDR*)&ip,sizeof(ip));

    /*bytes = recv(sock,buffer,sizeof(buffer),0);
    if(bytes>0){
      printf("%s\n",buffer);
      printf("Antes de enviar-> %s\n",msg_to_server);
      gets(msg_to_server);
      send(sock,msg_to_server,sizeof(msg_to_server),0);
      system("pause");
    }else{
      printf("Deconexion\n");
      system("pause");
    }*/

    char respuesta[2];
    while(1){
      memset(respuesta,'\0',sizeof(respuesta));
      printf("\nEnviar paquete Producto(p) o Cliente(c):");
      fgets(respuesta,sizeof(respuesta),stdin);
      printf("Has respondido->%s",respuesta);
      if(strcmp(respuesta,"c") == 0){
        // Paquete cliente
        printf("Vamos a formar el cliente mamahuevo");
        paquete.id = PKT_cliente;
        printf("\nIntroduce id:");
        scanf("%d",&paquete.cliente.id);
        getchar();
        printf("\nIntroduce nombre:");
        fgets(paquete.cliente.nombre,sizeof(paquete.cliente.nombre),stdin);
      
      }else{
        //Paquete producto
        paquete.id=PKT_producto;
        printf("\nIntroduce id de producto");
        scanf("%d",&paquete.producto.id);
        getchar();
        printf("\nIntroduce nombre del producto");
        fgets(paquete.producto.producto,sizeof(paquete.producto.producto),stdin);
        getchar();
        printf("\nPrecio");
        scanf("%d",&paquete.producto.precio);
      }


      send(sock,(char*)&paquete,sizeof(paquete),0);


    }     
    /*while(1){
        memset(buffer,'\0',sizeof(buffer));
        recv(sock,buffer,sizeof(buffer),0);
        printf("Recibido: %s \n",buffer);
        memset(buffer,'\0',sizeof(buffer));
        printf("Meteme la cadena: \n");
        gets(buffer);
        send(sock,buffer,strlen(buffer),0);
    }*/

    
    

    //printf("\nRecibid: %s\n",buffer);
    WSACleanup();
    return 0;
}