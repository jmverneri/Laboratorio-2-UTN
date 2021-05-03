#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct
{
    int idCliente;
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[30];
    char domicilio[30];
    char genero;
    int rol;          /// 1: es admin - 0: cliente
    int eliminado;   /// indica 1 o 0 si el cliente fue eliminado
}stCliente;

///Cargar un cliente
stCliente cargaUnCliente(char username[]);
///Mostrar un cliente
void mostrarCliente(stCliente c);

#endif // CLIENTE_H_INCLUDED
