#ifndef ARREGLOCLIENTES_H_INCLUDED
#define ARREGLOCLIENTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "cliente.h"
#include "listaProductos.h"

typedef struct
{
    stCliente cliente;
    nodoListaProducto * listaDeProductos;
    float costoTotalDelPedido;
} stCelda;


/// agrega un cliente al arreglo de listas
int agregarClienteAlArreglo(stCelda clientes[],int validos, stCliente cliente);
/// agrega un Producto al Cliente correspondiente
int agregarProductoToCliente(stCelda clientes[],int validos,int idCliente,stProducto p);

///busca un cliente por idCliente y retorna la posición que ocupa en el arreglo
int buscarCliente(stCelda clientes[],int validos,int idCliente);

///buscar un cliente por username
int buscarUsernameCliente(stCelda clientes[],int validos,char username[]);

///mostrar arreglo de clientes
void mostrarListadoClientes(stCelda clientes[],int validos);
void mostrarCeldaCliente(stCelda cliente);
void mostrarPedidoDeCliente(stCelda clientes[],int validos,stCliente cliente);


// esta función “vacía” todo el arreglo de listas, dejando la estructura preparada para volver a trabajar
void limpiarArregloDeClientes(stCelda clientes[], int validos);



#endif // ARREGLOCLIENTES_H_INCLUDED
