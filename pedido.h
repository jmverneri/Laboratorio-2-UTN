#ifndef PEDIDO_H_INCLUDED
#define PEDIDO_H_INCLUDED

typedef struct
{
    int idPedido;
    int idCliente;
    int idProducto;
} stPedido;


void mostrarPedido(stPedido p);


#endif // PEDIDO_H_INCLUDED
