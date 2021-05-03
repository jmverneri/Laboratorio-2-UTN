#include "arbolProductos.h"

/*************************************************************
Inicializar arbol
*************************************************************/
nodoArbolstProducto *inicArbol()
{
    return NULL;
}
/*************************************************************
Crear nodo arbol
*************************************************************/
nodoArbolstProducto *crearNodoArbol(stProducto dato)
{
    nodoArbolstProducto *nuevo = (nodoArbolstProducto*) malloc(sizeof(nodoArbolstProducto));

    nuevo->p = dato;
    nuevo->der = NULL;
    nuevo->izq = NULL;
    nuevo->altura= 1;

    return nuevo;
}
/*************************************************************
Insertar nodo en el arbol
*************************************************************/
nodoArbolstProducto *insertaNodoOrdenado(nodoArbolstProducto *arbol, stProducto dato)
{
    if(!arbol)
    {
        arbol= crearNodoArbol(dato);
    }
    else
    {
        if(dato.idProducto>arbol->p.idProducto)
        {
            arbol->der= insertaNodoOrdenado(arbol->der, dato);
        }
        else if(dato.idProducto>arbol->p.idProducto)
        {
            arbol->izq= insertaNodoOrdenado(arbol->izq, dato);
        }
    }
    return arbol;
}
/*************************************************************
Muestra arbol In Order
*************************************************************/
void muestraInOrden (nodoArbolstProducto *arbol)
{
    if(arbol)
    {
        muestraInOrden(arbol->izq);
        if(arbol->p.eliminado == 0)
        {
            mostrarNodoProducto(arbol);
        }
        muestraInOrden(arbol->der);
    }
}
/*************************************************************
Muestra arbol Post Order
*************************************************************/
void muestraPostOrden(nodoArbolstProducto *arbol)
{
    if(arbol)
    {
        muestraPostOrden(arbol->izq);
        muestraPostOrden(arbol->der);
        if(arbol->p.eliminado == 0)
        {
            mostrarNodoProducto(arbol);
        }
    }
}
/*************************************************************
Muestra arbol Pre Order
*************************************************************/
void muestraPreOrden (nodoArbolstProducto *arbol)
{
    if(arbol)
    {
        if(arbol->p.eliminado == 0)
            mostrarNodoProducto(arbol);

        muestraPreOrden(arbol->izq);
        muestraPreOrden(arbol->der);
    }
}
/*************************************************************
Muestra nodo Producto
*************************************************************/
void mostrarNodoProducto(nodoArbolstProducto *arbol)
{
    muestraProducto(arbol->p);
}
/*************************************************************
Buscar Producto por ID
*************************************************************/
nodoArbolstProducto* buscarNodoProductoID(nodoArbolstProducto* arbol, int id)
{
    nodoArbolstProducto *encontrado = inicArbol();
    if(arbol)
    {
        if(arbol->p.idProducto == id && arbol->p.eliminado == 0) /// proceso raiz
        {
            encontrado = arbol;
        }
        else
        {
            if(id> arbol->p.idProducto)
            {
                encontrado = buscarNodoProductoID(arbol->der, id);
            }
            else
            {
                encontrado = buscarNodoProductoID(arbol->izq, id);
            }
        }
    }
    return encontrado;
}
/*************************************************************
Buscar Producto por nombre
*************************************************************/
nodoArbolstProducto *buscarNodoProductoNombre(nodoArbolstProducto *arbol, char nombre[])
{
    nodoArbolstProducto *encontrado = inicArbol();
    if(arbol)
    {
        if(strcmpi(arbol->p.nombre,  nombre)==0 && arbol->p.eliminado == 0) /// proceso raiz
        {
            encontrado= arbol;
        }
        else
        {

            encontrado= buscarNodoProductoNombre(arbol->der, nombre);

            if(!encontrado)
            {
                encontrado= buscarNodoProductoNombre(arbol->izq, nombre);
            }
        }
    }
    return encontrado;
}
/*************************************************************
    modificar Producto por ID
*************************************************************/
nodoArbolstProducto* modificarProductoArbol(nodoArbolstProducto* arbol, int id, stProducto pCambio)
{
    if(arbol)
    {
        if(arbol->p.idProducto == id && arbol->p.eliminado == 0) /// proceso raiz
        {
            arbol->p = pCambio;
        }
        else
        {
            if(id > arbol->p.idProducto)
            {
                arbol->der = modificarProductoArbol(arbol->der, id, pCambio);
            }
            else
            {
                arbol->izq = modificarProductoArbol(arbol->izq, id, pCambio);
            }
        }
    }
    return arbol;
}



/***************************************************
Funcion para encontrar el lado mayor
***************************************************/
int maximo(int a, int b)
{
    return (a > b)? a : b;
}
/**************************************************
Funcion para encontrar la altura del arbol
**************************************************/
int height(nodoArbolstProducto *arbol)
{
    int respuesta;
    if (arbol == NULL)
    {
        respuesta= 0;
    }
    else
    {
        if(esHoja(arbol))
        {
            respuesta= 1;
        }
        else
        {
            respuesta= 1 + maximo(height(arbol->izq), height(arbol->der));
        }
    }
    return respuesta;
}
/*********************************************
Funcion que busca si es hoja
*********************************************/
int esHoja(nodoArbolstProducto *arbol)
{
    int rta=0;
    if(arbol)
    {
        if(arbol->izq== NULL && arbol->der== NULL)
        {
            rta= 1;
        }
    }
    return rta;
}
/**************************************************
Funcion para rotar el arbol a la derecha
***************************************************/
nodoArbolstProducto *rightRotate(nodoArbolstProducto *y)
{
    nodoArbolstProducto *x = y->izq;
    nodoArbolstProducto *T2 = x->der;

    /// Hace la rotacion
    x->der = y;
    y->izq = T2;

    /// Actualiza las alturas
    y->altura = maximo(height(y->izq), height(y->der))+1;
    x->altura = maximo(height(x->izq), height(x->der))+1;

    return x;
}
/*************************************************
Funcion que rota el arbol a la derecha
*************************************************/
nodoArbolstProducto *leftRotate(nodoArbolstProducto *x)
{
    nodoArbolstProducto *y = x->der;
    nodoArbolstProducto *T2 = y->izq;

    /// Realiza la rotacion
    y->izq = x;
    x->der = T2;

    ///  Actualiza las alturas
    x->altura = maximo(height(x->izq), height(x->der))+1;
    y->altura = maximo(height(y->izq), height(y->der))+1;


    return y;
}
/********************************
Funcion que balancea el nodo
********************************/
int getBalance(nodoArbolstProducto *arbol)
{
    int rta;
    if (arbol == NULL)
    {
        rta= 0;
    }
    else
    {
        rta= height(arbol->izq) - height(arbol->der);
    }
    return rta;
}
/****************************************************
Insertar un producto en orden en el arbol
**************************************************/
nodoArbolstProducto *insertInOrder(nodoArbolstProducto *arbol, stProducto producto)
{
    if(!arbol)
    {
        arbol= crearNodoArbol(producto);
    }
    else
    {
        if(producto.idProducto < arbol->p.idProducto)
        {
            arbol->izq  = insertarAVL(arbol->izq, producto);
        }
        else if(producto.idProducto > arbol->p.idProducto)
        {
            arbol->der = insertarAVL(arbol->der, producto);
        }
    }
    return arbol;
}
/**************************************
Funcion que inserta un nuevo producto en el arbol
Lo balancea
Devuelve puntero al nuevo arbol
****************************************/
nodoArbolstProducto* insertarAVL(nodoArbolstProducto *arbol, stProducto producto)
{
    ///* 1.  Inserscion en arbol binario de busqueda */
    arbol = insertInOrder(arbol, producto);

    ///* 2. Update height of this ancestor node */
    arbol->altura = 1 + maximo(height(arbol->izq),height(arbol->der));

    /*** 3. Analiza el balance del nodo antecesor para chequear si se
            desbalanceo */
    int balance = getBalance(arbol);

    ///Si se desbalanceo, hay 4 casos

    /// Caso izquierda izquierda
    nodoArbolstProducto* nodoIzq = arbol->izq;
    nodoArbolstProducto* nodoDer = arbol->der;

    if (balance > 1 && producto.idProducto < nodoIzq->p.idProducto)
        arbol = rightRotate(arbol);

    /// Caso derecho derecho
    else if (balance < -1 && producto.idProducto > nodoDer->p.idProducto)
        arbol = leftRotate(arbol);

    /// Caso izquierdo derecho
    else if (balance > 1 && producto.idProducto > nodoIzq->p.idProducto)
    {
        arbol->izq =  leftRotate(arbol->izq);
        arbol=  rightRotate(arbol);
    }

    /// Caso derecha izquierda
    else if (balance < -1 && producto.idProducto < nodoDer->p.idProducto)
    {
        arbol->der = rightRotate(arbol->der);
        arbol= leftRotate(arbol);
    }

    return arbol;
}
/**************************************************
Borrar nodo de un arbol
************************************************/
nodoArbolstProducto * borrarNodoIntArbol(nodoArbolstProducto * arbol, stProducto dato)
{
    if (arbol)
    {
        if (arbol->p.idProducto == dato.idProducto)
        {
            if (arbol->izq)
            {
                nodoArbolstProducto * masDer = nodoMasDerecha(arbol->izq);
                arbol->p.idProducto = masDer->p.idProducto;
                arbol->izq = borrarNodoIntArbol(arbol->izq, masDer->p);
            }
            else if (arbol->der)
            {
                nodoArbolstProducto * masIzq = nodoMasIzquierda(arbol->der);
                arbol->p.idProducto = masIzq->p.idProducto;
                arbol->izq = borrarNodoIntArbol(arbol->izq, masIzq->p);
            }
            else
            {
                // este es cuando el nodo es hoja
                free(arbol);
                arbol = NULL;
            }
        }
        else if (dato.idProducto > arbol->p.idProducto)
        {
            arbol->der = borrarNodoIntArbol(arbol->der, dato);
        }
        else
        {
            arbol->izq = borrarNodoIntArbol(arbol->izq, dato);
        }
    }

    return arbol;
}

nodoArbolstProducto * nodoMasDerecha (nodoArbolstProducto * arbol)
{
    if (arbol)
    {
        if (arbol->der)
            arbol = nodoMasDerecha(arbol->der);
    }
    return arbol;
}

nodoArbolstProducto * nodoMasIzquierda (nodoArbolstProducto * arbol)
{
    if(arbol->izq)
        arbol = nodoMasIzquierda(arbol->izq);
    return arbol;
}
