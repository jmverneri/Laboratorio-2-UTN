#include "listaProductos.h"

/************************************
Inicializar lista
************************************/
nodoListaProducto *iniciarLista()
{
    return NULL;
}
/************************************
Crear nodo
************************************/
nodoListaProducto *creaNodo(stProducto dato)
{
    nodoListaProducto *aux= (nodoListaProducto*)malloc(sizeof(nodoListaProducto));
    aux->p= dato;

    aux->sig= NULL;

    return aux;
}
/*************************************************
Agrega al principio
*************************************************/
nodoListaProducto *agregaPrincipio(nodoListaProducto *lista, nodoListaProducto *nuevo)
{
    nuevo->sig= lista;
    lista= nuevo;

    return lista;
}
/*******************************************
Agregar nodo al final
*******************************************/
nodoListaProducto *agregarAlFinal(nodoListaProducto *lista, nodoListaProducto *nuevo)
{
    if(lista== NULL)
    {
        lista= nuevo;
    }
    else
    {
        nodoListaProducto *ultimo= buscaUltimoNodo(lista);
        ultimo->sig= nuevo;
    }
    return lista;
}
/********************************************
Buscar el ultimo nodo
********************************************/
nodoListaProducto *buscaUltimoNodo(nodoListaProducto *lista)
{
    nodoListaProducto *aux= lista;

    if(aux!=NULL)
    {
        while(aux->sig!=NULL)
        {
            aux= aux->sig;
        }
    }
    return aux;
}

/**********************************************
Agregar en orden
**********************************************/
nodoListaProducto *agregaOrden(nodoListaProducto *lista, nodoListaProducto *nuevo)
{
    if(lista== NULL)
    {
        lista= nuevo;
    }
    else
    {
        if(strcmp(nuevo->p.nombre,lista->p.nombre)<0)
        {
            lista= agregaPrincipio(lista, nuevo);
        }
        else
        {
            nodoListaProducto *ante= lista;
            nodoListaProducto *seg= lista->sig;

            while((seg!=NULL) && (strcmp(nuevo->p.nombre, seg->p.nombre)>0))
            {
                ante= seg;
                seg= seg->sig;
            }
            nuevo->sig= seg;
            ante->sig= nuevo;
        }
    }
    return lista;
}
/***************************************************
Mostrar nodo
***************************************************/
void muestraNodo(nodoListaProducto *muestra)
{
    muestraProducto(muestra->p);
}
/**************************************************
Recorrer y mostrar lista
**************************************************/
void recorrerYMostrar(nodoListaProducto *lista)
{
    nodoListaProducto *aux = lista;

    while(aux!=NULL)
    {
        if(aux->p.eliminado == 0)
        {
            muestraNodo(aux);
        }
        aux = aux->sig;
        printf("\n");
    }
}
/*************************************************
Borrar nodo
*************************************************/
nodoListaProducto *borraNodo(nodoListaProducto *lista, int id)
{
    nodoListaProducto *ante;
    nodoListaProducto *seg;
    if(lista!=NULL && id==lista->p.idProducto)
    {
        nodoListaProducto *aux= lista;
        lista= lista->sig;
        free(aux);
    }
    else
    {
        seg= lista;
        while((seg!=NULL) && id!=seg->p.idProducto)
        {
            ante= seg;
            seg= seg->sig;
        }
        if(seg!=NULL)
        {
            ante->sig= seg->sig;
            free(seg);
        }
    }
    return lista;
}

nodoListaProducto* borrarListaProductos(nodoListaProducto* lista)
{
    nodoListaProducto* proximo;
    nodoListaProducto* aux = lista;
    while(aux!=NULL)
    {
        proximo = aux->sig;
        free(aux);
        aux = proximo;
    }
    return aux;
}
/*************************************************
Buscar nodo
*************************************************/
nodoListaProducto * buscarNodoListaProductos(nodoListaProducto *lista, int id)
{
    nodoListaProducto *aux;
    aux= lista;

    while((aux!=NULL) && (id != aux->p.idProducto) && (aux->p.eliminado == 0))
    {
        aux = aux->sig;
    }
    return aux;
}
/*************************************************
    calcula precio de una lista de productos
*************************************************/
float calcularPrecioDeListaProductos(nodoListaProducto* lista)
{
    float precioTotal = 0;
    nodoListaProducto* aux = lista;

    while(aux != NULL)
    {
        precioTotal = precioTotal + aux->p.precio;
        aux = aux->sig;
    }

    return precioTotal;
}
/****************************************************************
    cambia el valor de eliminado a 1  de un producto de la lista
*****************************************************************/
nodoListaProducto* eliminarProducto(nodoListaProducto *lista, int id)
{
    nodoListaProducto* aux;
    if(lista!=NULL && id==lista->p.idProducto)
    {
        lista->p.eliminado = 1;
    }
    else
    {
        aux = lista;
        while((aux!=NULL) && id!=aux->p.idProducto)
        {
            aux = aux->sig;
        }
        if(aux!=NULL)
        {
            aux->p.eliminado = 1;
        }
    }
    return lista;
}
/****************************************************************
    cambia los valores de un producto de la lista
*****************************************************************/
nodoListaProducto* modificarProductoLista(nodoListaProducto *lista, int id, stProducto pCambio)
{
    nodoListaProducto* aux;
    if(lista!=NULL && id == lista->p.idProducto)
    {
        lista->p = pCambio;
    }
    else
    {
        aux = lista;
        while((aux!=NULL) && id!=aux->p.idProducto)
        {
            aux = aux->sig;
        }
        if(aux!=NULL)
        {
            aux->p = pCambio;
        }
    }
    return lista;
}

/**************************************************
Funcion que devuelve el ultimo ID
**************************************************/
int ultimoID(nodoListaProducto* lista)
{
    int id = 0;
    if(lista)
    {
        nodoListaProducto* aux;
        aux = buscarMayorIdProducto(lista);
        id = aux->p.idProducto;
    }
    return id;
}


nodoListaProducto* buscarMayorIdProducto(nodoListaProducto* lista)
{
    nodoListaProducto* mayor;
    if(lista)
    {
        if(lista->sig == NULL)
        {
            mayor = lista;
        }
        else
        {
            mayor = buscarMayorIdProducto(lista->sig);
            if(lista->p.idProducto > mayor->p.idProducto)
            {
                mayor = lista;
            }
        }
    }
    return mayor;
}

stProducto encontrarPrimero(nodoListaProducto* lista)
{
    stProducto producto;
    if(lista)
    {
        producto = lista->p;
    }
    return producto;
}

void mostrarProductosPorMarca(nodoListaProducto* lista, stProducto p)
{
    nodoListaProducto* aux = lista;

    while(aux)
    {
        if(strcmp(aux->p.marca,p.marca)==0)
        {
            muestraProducto(aux->p);
        }
        aux = aux->sig;
    }
}



