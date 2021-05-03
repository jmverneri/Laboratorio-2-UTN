#ifndef LISTAPRODUCTOS_H_INCLUDED
#define LISTAPRODUCTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "producto.h"

typedef struct _nodoListaProducto
{
    stProducto p;
    struct _nodoListaProducto * sig;
} nodoListaProducto;

///Iniciliarizar
nodoListaProducto *iniciarLista();
///Crear nodo
nodoListaProducto *creaNodo(stProducto dato);
///Agregar al principio
nodoListaProducto *agregaPrincipio(nodoListaProducto *lista, nodoListaProducto *nuevo);
///Agregar nodo al final
nodoListaProducto *agregarAlFinal(nodoListaProducto *lista, nodoListaProducto *nuevo);
///Buscar ultimo nodo
nodoListaProducto *buscaUltimoNodo(nodoListaProducto *lista);
///Agregar en orden
nodoListaProducto *agregaOrden(nodoListaProducto *lista, nodoListaProducto *nuevo);
///Mostrar nodo
void muestraNodo(nodoListaProducto *muestra);
///Recorrer y mostrar lista
void recorrerYMostrar(nodoListaProducto *lista);
///Borrar nodo
nodoListaProducto *borraNodo(nodoListaProducto *lista, int id);
///Borrar toda la lista
nodoListaProducto* borrarListaProductos(nodoListaProducto* lista);
///Buscar lista de productos
nodoListaProducto * buscarNodoListaProductos(nodoListaProducto *lista, int id);
///Calcular Costo de toda la lista
float calcularPrecioDeListaProductos(nodoListaProducto* lista);
///cambiar el valor eliminado a 1 de un producto
nodoListaProducto* eliminarProducto(nodoListaProducto *lista, int id);
///cambia los valores de un producto de la lista
nodoListaProducto* modificarProductoLista(nodoListaProducto *lista, int id, stProducto pCambio);
///buscar el nodo con mayor ID, para autoincrementar el id en el alta
int ultimoID(nodoListaProducto* lista);
nodoListaProducto* buscarMayorIdProducto(nodoListaProducto* lista);

stProducto encontrarPrimero(nodoListaProducto* lista);
void mostrarProductosPorMarca(nodoListaProducto* lista, stProducto p);

#endif // LISTAPRODUCTOS_H_INCLUDED
