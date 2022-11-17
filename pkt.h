typedef struct Clientes{
  int id;
  char nombre[50];
}Clientes;
typedef struct Productos{
  int id;
  char producto[25];
  int precio;
}Productos;
typedef struct Packet{
  int tipo;
  union{
    Clientes cliente;
    Productos producto;
  };
}Packet;