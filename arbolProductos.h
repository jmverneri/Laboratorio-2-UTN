#ifndef ARBOLPRODUCTOS_H_INCLUDED
#define ARBOLPRODUCTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "producto.h"

typedef struct _nodoArbolstProducto
{
    stProducto p;
    struct _nodoArbolstProducto * izq;
    struct _nodoArbolstProducto * der;
    int altura;
} nodoArbolstProducto;

///Inicializar arbol
nodoArbolstProducto *inicArbol();

///Crear nodo arbol
nodoArbolstProducto *crearNodoArbol(stProducto dato);

///Insertar nodo en el arbol
nodoArbolstProducto *insertaNodoOrdenado(nodoArbolstProducto *arbol, stProducto dato);

///Muestra arbol In Order
void muestraInOrden (nodoArbolstProducto *arbol);

///Muestra arbol Post Order
void muestraPostOrden(nodoArbolstProducto *arbol);

///Muestra arbol Pre Order
void muestraPreOrden (nodoArbolstProducto *arbol);

///Muestra nodo Producto
void mostrarNodoProducto(nodoArbolstProducto *arbol);

///Buscar Producto
nodoArbolstProducto *buscarNodoProductoID(nodoArbolstProducto *arbol, int id);
nodoArbolstProducto *buscarNodoProductoNombre(nodoArbolstProducto *arbol, char nombre[]);

///modificar Producto de un arbol
nodoArbolstProducto* modificarProductoArbol(nodoArbolstProducto* arbol, int id, stProducto pCambio);


///Funciones para hacer arbol AVL
int maximo(int a, int b);
nodoArbolstProducto *rightRotate(nodoArbolstProducto *y);
nodoArbolstProducto *leftRotate(nodoArbolstProducto *x);
int getBalance(nodoArbolstProducto *arbol);
nodoArbolstProducto *insertarAVL(nodoArbolstProducto *arbol, stProducto);
int height(nodoArbolstProducto *arbol);
int esHoja(nodoArbolstProducto *arbol);

///Funciones para borrar nodo arbol
nodoArbolstProducto * borrarNodoIntArbol (nodoArbolstProducto * arbol, stProducto dato);
nodoArbolstProducto * nodoMasDerecha (nodoArbolstProducto * arbol);
nodoArbolstProducto * nodoMasIzquierda (nodoArbolstProducto * arbol);

#endif // ARBOLPRODUCTOS_H_INCLUDED
