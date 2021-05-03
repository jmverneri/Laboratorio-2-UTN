#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int idProducto;
    char nombre[30];
    char marca[20];
    float precio;
    int eliminado;  /// indica 1 o 0 si el producto fue eliminado
}stProducto;

///Cargar un solo producto
stProducto cargaUnProducto();

///Mostrar producto
void muestraProducto(stProducto p);

#endif // PRODUCTO_H_INCLUDED
