#include "producto.h"

/*************************************************
Función que permite cargar un solo producto
**************************************************/
stProducto cargaUnProducto(char nombre[])
{
    stProducto producto;
    printf("\n\t Completar todos los campos obligatorios");
    printf("\n\t ----------------------------------------------");

    strcpy(producto.nombre, nombre);

    printf("\n\t Costo del producto: ");
    fflush(stdin);
    scanf("%f", &producto.precio);

    printf("\n\t Marca del producto: ");
    fflush(stdin);
    gets(producto.marca);

    producto.eliminado = 0;  /// indica 1 si el producto fue eliminado o 0 si esta activo

    return producto;
}
/*************************************************
Función que muestra un producto
**************************************************/
void muestraProducto(stProducto p)
{
    printf("\n\t Numero de id del producto: %d", p.idProducto);

    printf("\n\t Nombre del producto: %s", p.nombre);

    printf("\n\t Marca del producto: %s", p.marca);

    printf("\n\t Precio %.2f", p.precio);
    printf("\n\t*****************************\n\n");
}
