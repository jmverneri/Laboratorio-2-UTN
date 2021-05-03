#include "arregloClientes.h"

/**********************************************************************
Funcion que permite agregar un cliente en el arreglo de clientes
***********************************************************************/
int agregarClienteAlArreglo(stCelda clientes[],int validos, stCliente cliente)
{
    clientes[validos].cliente = cliente;
    clientes[validos].listaDeProductos = iniciarLista();
    clientes[validos].costoTotalDelPedido = 0;
    validos ++;
    return validos;
}

/************************************************************************
Funcion que agrega un producto a la lista de productos de un cliente,
si el cliente no existe lo crea y lo agrega al final del arreglo
************************************************************************/
int agregarProductoToCliente(stCelda clientes[],int validos,int idCliente,stProducto p)
{
    nodoListaProducto* nuevoProducto = creaNodo(p);
    int pos = buscarCliente(clientes,validos,idCliente);
    if (pos == -1)
    {
        validos = altaCliente(clientes,validos);
        pos = validos - 1;
    }
    stCelda cliente = clientes[pos]; //extraigo el cliente del arreglo
    nodoListaProducto* listaDeProductos = cliente.listaDeProductos; //extraigo la lista
    listaDeProductos = agregaPrincipio(listaDeProductos,nuevoProducto); //agrego el nodo
    cliente.listaDeProductos = listaDeProductos; //asigno la lista al cliente, con el producto agregado
    cliente.costoTotalDelPedido = calcularPrecioDeListaProductos(listaDeProductos);
    clientes[pos] = cliente; //actualizamos el cliente

    return validos;
}
/***********************************************************************
Funcion que buscar un cliente por idCliente, si lo encuentra devuelve
la posicion, sino devuelve -1
************************************************************************/
int buscarCliente(stCelda clientes[],int validos,int idCliente)
{
    int pos = -1;
    int i = 0;
    while ((i<validos)&&(pos==-1))
    {
        if (clientes[i].cliente.idCliente == idCliente && clientes[i].cliente.eliminado == 0)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}
/***********************************************************************
Funcion que buscar un cliente por username, si lo encuentra devuelve
la posicion en el arreglo, sino devuelve -1
************************************************************************/
int buscarUsernameCliente(stCelda clientes[],int validos,char username[])
{
    int pos = -1;
    int i = 0;
    while ((i<validos)&&(pos == -1))
    {
        if (strcmp(clientes[i].cliente.userName,username)==0 && clientes[i].cliente.eliminado == 0)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}

/****************************************************
Funcion que muestra el listado de clientes
Reutilizable: se le pasa 0 o 1 a variable eliminado,
para mostrar clientes eliminados o activos
****************************************************/
void mostrarListadoClientes(stCelda clientes[],int validos)
{
    printf("\n\t **** Clientes ****\n");
    for (int i=0; i<validos; i++)
    {
        if(clientes[i].cliente.eliminado == 0)
        {
            mostrarCeldaCliente(clientes[i]);
        }
    }
    printf("\n\t **** ******** ****\n");
}

void mostrarCeldaCliente(stCelda c)
{
    mostrarCliente(c.cliente);
    printf("\n\t **** lista de Productos ****\n");
    recorrerYMostrar(c.listaDeProductos);
    printf("\n\n\t ~ Costo del Pedido: $ %.2f ~\n",c.costoTotalDelPedido);

}
void mostrarPedidoDeCliente(stCelda clientes[],int validos,stCliente cliente)
{
    int pos = buscarCliente(clientes,validos,cliente.idCliente);
    mostrarCeldaCliente(clientes[pos]);
}
//libera la memoria del arreglo cargado
void limpiarArregloDeClientes(stCelda clientes[], int validos)
{
    for(int i=validos-1;i>=0;i--)
    {
        clientes[i].listaDeProductos = borrarListaProductos(clientes[i].listaDeProductos);
    }
    free(clientes);

}




