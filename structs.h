struct Cliente{
  int id;
  char nombre[50];
};

struct Producto{
  int id;
  char producto[50];
  int precio;
};

struct Paquete{
  int id;
  union{
    struct  Cliente cliente;
    struct Producto producto;
  };
};

enum {PKT_cliente=0,PKT_producto=1};


struct Conn{
  int id;
};

struct Datos{
  int id;
  char cmd[50];
};

struct UDP_Paquete{
  int id;
  union{
    struct Conn con;
    struct Datos datos;
  };
};

enum {PKT_Conn=0,PKT_Datos=1};
