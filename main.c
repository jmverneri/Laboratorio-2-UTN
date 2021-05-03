#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

///Librerias creadas
#include "producto.h"
#include "cliente.h"
#include "pedido.h"
#include "listaProductos.h"
#include "arbolProductos.h"
#include "arregloClientes.h"

///Constantes para archivos
#define aClientes "clientes.dat"
#define aProductos "productos.dat"
#define aPedidos "pedidos.dat"

///Menus
void iniciar();
void imprimirCabecera(char cabecera[]);
void imprimirOpcionIncorrecta();
void imprimirSalida();
int ingresarOpcion();
int menuModificacionesCliente();
int login(stCelda clientes[], int validos, stCliente* cLogin);

///subprogramas para los menus
void subProgramaBajaProducto(nodoArbolstProducto** arbol, nodoListaProducto** productos);
void subProgramaModificarProducto(nodoArbolstProducto** arbol, nodoListaProducto** productos);
void subprogramaConsultaProducto(nodoArbolstProducto* arbol);
void subProgramaModificarCliente(stCelda clientes[], int validos);
void subprogramaBajaCliente(stCelda clientes[], int validos);
void subprogramaAgregarProductoAlPedido(stCelda clientes[], int validos, int idCliente, nodoArbolstProducto* arbol, nodoListaProducto* productos);
void subprogramaConsultaCliente(stCelda clientes[], int validos);
void recomendarProductosPorMarca(stCelda clientes[], int validos, int idCliente, nodoListaProducto* productos);

///ABML Productos
int bajaProducto(nodoArbolstProducto** arbolProducto, nodoListaProducto** listaProducto, int idProducto);
void altaProducto(nodoListaProducto **listaProducto, nodoArbolstProducto **arbolProducto);
int modificarProducto(nodoArbolstProducto** arbolProducto, nodoListaProducto** listaProducto, int id);
int ultimoID(nodoListaProducto *lista);

///ABML Clientes
int altaCliente(stCelda clientes[], int validos, int rolCliente);
int asignarRolCliente();
int modificarCliente(stCelda adl[], int validos, int idCliente);
int bajaCliente(stCelda clientes[], int validos, int idCliente);

///Funciones para manejo de archivos
nodoListaProducto* cargarProductosDesdeArchivo(nodoListaProducto* productos);
nodoArbolstProducto* cargarArbolBalanceadoDesdeLista(nodoArbolstProducto* arbol, nodoListaProducto* lista);
int cargarPedidosAlArregloDesdeArchivo(stCelda clientes[], int validos, nodoArbolstProducto* arbol);
int cargarClientesDesdeArchivos(stCelda clientes[], int dimension, nodoArbolstProducto* arbol);
int contarClientesActivos();
stCliente crearAdministrador();

void guardarEnArchivoProductos(stProducto p);
void guardarEnArchivoClientes(stCliente c);
void guardarEnArchivoPedidos(stPedido p);
void persistirModificacionProducto(nodoListaProducto* productos);
void persistirModificaciones(stCelda clientes[],int validos);


//main
int main()
{
    /* Visualizacion - Inicio del programa */
    iniciar();

    /* Carga de estruturas desde archivos */
    nodoListaProducto* productos = iniciarLista();
    productos = cargarProductosDesdeArchivo(productos);

    nodoArbolstProducto* arbolProductos = inicArbol();
    arbolProductos = cargarArbolBalanceadoDesdeLista(arbolProductos, productos);

    int dimension = contarClientesActivos()+1;
    stCelda* clientes = (stCelda*) malloc(sizeof(stCelda)*dimension);
    int validos = cargarClientesDesdeArchivos(clientes, dimension, arbolProductos);

    /* Menu Principal */
    int op;
    do
    {
        imprimirCabecera("Bienvenidos");
        printf("\n\t 1. Ingresar");
        printf("\n\t 2. Registrarse");
        printf("\n\t 0. Salir");
        op = ingresarOpcion();

        stCliente cLogin;
        int flag;
        switch(op)
        {
        case 0:
            system("cls");
            imprimirSalida();
            break;
        case 1:
            //funcion para ingreso (debera devolver 1 o 0 segun exito)
            flag = login(clientes,validos,&cLogin);

            ///menu admin o clientes segun username del login
            if(flag)
            {
                if(cLogin.rol == 1)
                {
                    do
                    {
                        imprimirCabecera(" Administracion");
                        printf("\n\t 1. Clientes");
                        printf("\n\t 2. Productos");
                        printf("\n\t 3. Volver al menu anterior");
                        op = ingresarOpcion();
                        switch(op)
                        {
                        case 1:
                            ///ABLM clientes
                            do
                            {
                                imprimirCabecera(" Administracion de Clientes");
                                printf("\n\t 1. Alta");
                                printf("\n\t 2. Baja");
                                printf("\n\t 3. Modificacion");
                                printf("\n\t 4. Listado de Clientes Activos");
                                printf("\n\t 5. Consultas");
                                printf("\n\t 6. Volver al menu anterior");
                                op = ingresarOpcion();
                                switch(op)
                                {
                                case 1:
                                    ///alta cliente
                                    system("cls");
                                    imprimirCabecera("Registro del Cliente");
                                    int rol = asignarRolCliente();
                                    validos = altaCliente(clientes,validos,rol);
                                    printf("\n\n\n");
                                    system("pause");
                                    break;
                                case 2:
                                    ///baja cliente
                                    subprogramaBajaCliente(clientes,validos);
                                    break;
                                case 3:
                                    ///modificar info cliente
                                    subProgramaModificarCliente(clientes,validos);
                                    break;
                                case 4:
                                    ///mostrar listado de clientes
                                    imprimirCabecera("Listado de clientes");
                                    mostrarListadoClientes(clientes,validos);
                                    printf("\n\n\n");
                                    system("pause");
                                    break;
                                case 5:
                                    ///funcion consultas
                                    subprogramaConsultaCliente(clientes, validos);
                                    break;
                                case 6:
                                    system("cls");
                                    break;
                                default:
                                    imprimirOpcionIncorrecta();
                                }
                            }
                            while(op != 6);
                            break;
                        case 2:
                            ///ABLM productos
                            do
                            {
                                imprimirCabecera("Administracion de Productos");
                                printf("\n\t 1. Alta");
                                printf("\n\t 2. Baja");
                                printf("\n\t 3. Modificacion");
                                printf("\n\t 4. Listado de Productos");
                                printf("\n\t 5. Consultas");
                                printf("\n\t 6. Volver al menu anterior");
                                op = ingresarOpcion();
                                switch(op)
                                {
                                case 1:
                                    ///alta producto
                                    altaProducto(&productos,&arbolProductos);
                                    break;
                                case 2:
                                    ///baja producto
                                    subProgramaBajaProducto(&arbolProductos, &productos);
                                    break;
                                case 3:
                                    //modificar info productos
                                    subProgramaModificarProducto(&arbolProductos, &productos);
                                    break;
                                case 4:
                                    //subprograma mostrar listado de productos
                                    do
                                    {
                                        imprimirCabecera("Mostrar Productos");
                                        printf("\n\t 1. Preorder");
                                        printf("\n\t 2. Inorder");
                                        printf("\n\t 3. Postorder");
                                        printf("\n\t 4. Volver al menu anterior");
                                        op = ingresarOpcion();
                                        switch(op)
                                        {
                                        case 1:
                                            imprimirCabecera("Arbol de Productos");
                                            muestraPreOrden(arbolProductos);
                                            printf("\n\n\n");
                                            system("pause");
                                            break;
                                        case 2:
                                            imprimirCabecera("Arbol de Productos");
                                            muestraInOrden(arbolProductos);
                                            printf("\n\n\n");
                                            system("pause");
                                            break;
                                        case 3:
                                            imprimirCabecera("Arbol de Productos");
                                            muestraPostOrden(arbolProductos);
                                            printf("\n\n\n");
                                            system("pause");
                                            break;
                                        case 4:
                                            system("cls");
                                            break;
                                        default:
                                            imprimirOpcionIncorrecta();
                                        }
                                    }
                                    while(op != 4);
                                    break;
                                case 5:
                                    //funcion consultas
                                    subprogramaConsultaProducto(arbolProductos);
                                    break;
                                case 6:
                                    system("cls");
                                    break;
                                default:
                                    imprimirOpcionIncorrecta();
                                }
                            }
                            while(op != 6);
                            break;
                        case 3:
                            system("cls");
                            break;
                        default:
                            imprimirOpcionIncorrecta();
                        }
                    }
                    while(op != 3);
                }
                if (cLogin.rol == 0)
                {
                    do
                    {
                        imprimirCabecera("Bienvenidos");
                        printf("\n\t 1. Ver Perfil");
                        printf("\n\t 2. Mostrar Pedido");
                        printf("\n\t 3. Agregar Producto al Pedido");
                        printf("\n\t 4. Mostrar Productos recomendados");
                        printf("\n\t 5. Volver al menu anterior");
                        op = ingresarOpcion();
                        switch(op)
                        {
                        case 1:
                            imprimirCabecera("Perfil");
                            mostrarCliente(cLogin);
                            printf("\n\n\n");
                            system("pause");
                            break;
                        case 2:
                            imprimirCabecera("Pedido");
                            mostrarPedidoDeCliente(clientes, validos, cLogin);
                            printf("\n\n\n");
                            system("pause");
                            break;
                        case 3:
                            subprogramaAgregarProductoAlPedido(clientes,validos,cLogin.idCliente,arbolProductos,productos);
                            break;
                        case 4:
                            imprimirCabecera("Productos Recomendados");
                            recomendarProductosPorMarca(clientes,validos,cLogin.idCliente,productos);
                            system("pause");
                            break;
                        case 5:
                            system("cls");
                            break;
                        default:
                            imprimirOpcionIncorrecta();
                        }
                    }
                    while(op != 5);
                }
            }
            break;
        case 2:
            ///registrarse
            validos = altaCliente(clientes,validos,0);
            printf("\n\n\n");
            system("pause");
            break;
        default:
            imprimirOpcionIncorrecta();
        }
    }
    while(op != 0);

    ///Guardar cambios del programa en los archivos
    remove(aClientes);
    remove(aPedidos);
    remove(aProductos);
    persistirModificacionProducto(productos);
    persistirModificaciones(clientes,validos);

    return 0;
}
/******************************************************************
        Imprime visualizacion de inicio - simulacion de carga
******************************************************************/
void iniciar()
{
    system("color 90");

    printf("\n o88                o88                o88                                  oooo");
    Sleep(100);
    printf("\n oooo  oo oooooo    oooo    ooooooo    oooo    ooooooo   oo oooooo     ooooo888    ooooooo");
    Sleep(100);
    printf("\n  888   888   888    888  888     888   888    ooooo888   888   888  888    888  888     888");
    Sleep(100);
    printf("\n  888   888   888    888  888           888  888    888   888   888  888    888  888     888");
    Sleep(100);
    printf("\n o888o o888o o888o  o888o   88ooo888   o888o  88ooo88 8o o888o o888o   88ooo888o   88ooo88");
    for(int i = 0; i<3; i++)
    {
        Sleep(1000);
        printf("\tOoO");
    }
    Sleep(1000);
    system("cls");
    system("color 5F");
}

/****************************************************************************
    imprime por pantalla un arreglo de caracteres con un recuadro
****************************************************************************/
void imprimirCabecera(char cabecera[])
{
    int i;
    system("cls");
    printf("\t%c", 201);
    for(i=0; i<50; i++)
    {
        printf("%c",205);
    }
    printf("%c\n", 187);
    printf("\t%c%32s%19c\n", 186,cabecera,186);
    printf("\t%c", 200);
    for(i=0; i<50; i++)
    {
        printf("%c",205);
    }
    printf("%c", 188);
    printf("\n\n");
}

/********************************************************************************
   Pide por pantalla que se ingrese un valor correspondiente a la opcion deseada
*********************************************************************************/
int ingresarOpcion()
{
    int opcion;
    printf("\n\t Ingrese opcion: ");
    fflush(stdin);
    scanf("%i", &opcion);
    return opcion;
}

/**********************************************************************
            Funcion que muestra mensaje de despedida
***********************************************************************/
void imprimirSalida()
{
    system("color 5F");
    printf("\n\t  _   _           _          _                             ");
    printf("\n\t | | | |         | |        | |                            ");
    printf("\n\t | |_| | __ _ ___| |_ __ _  | |    _   _  ___  __ _  ___   ");
    printf("\n\t |  _  |/ _` / __| __/ _` | | |   | | | |/ _ \\/ _` |/ _ \\  ");
    printf("\n\t | | | | (_| \\__ \\ || (_| | | |___| |_| |  __/ (_| | (_) | ");
    printf("\n\t \\_| |_/\\__,_|___/\\__\\__,_| \\_____/\\__,_|\\___|\\__, |\\___/");
    printf("\n\t                                               __/ |       ");
    printf("\n\t                                              |___/        ");
    printf("\n\n\n\n\n\n");
}
void imprimirOpcionIncorrecta()
{
    printf("\n\t--- Opcion incorrecta ---\n\n");
    system("pause");
}

/**********************************************************************
    Funcion que carga la lista de productos desde el archivo productos
***********************************************************************/
nodoListaProducto* cargarProductosDesdeArchivo(nodoListaProducto* productos)
{
    FILE* archivo;
    archivo = fopen(aProductos,"rb");
    if(archivo!= NULL)
    {
        stProducto aux;
        while(fread(&aux,sizeof(stProducto),1,archivo)>0)
        {
            productos = agregaPrincipio(productos, creaNodo(aux));
        }
    }
    fclose(archivo);
    return productos;
}
///funcion que cargar el arbol de busqueda, pasando primero los elementos del archivo a una lista y de la lista al arbol
nodoArbolstProducto* cargarArbolBalanceadoDesdeLista(nodoArbolstProducto* arbol, nodoListaProducto* lista)
{
    nodoListaProducto* aux = lista;
    while(aux)
    {
        arbol = insertarAVL(arbol, aux->p);
        aux = aux->sig;
    }

    return arbol;
}
/**********************************************************************
    Funciones que cargan el ADL desde el archivos clientes y pedidos
***********************************************************************/
///carga los pedidos que realizaron los clientes desde el archivo pedidos al ADL
int cargarPedidosAlArregloDesdeArchivo(stCelda clientes[], int validos, nodoArbolstProducto* arbol)
{
    FILE* archivo;
    archivo = fopen(aPedidos,"rb");
    if(archivo!= NULL)
    {
        stPedido aux;
        nodoArbolstProducto* nodoProducto;
        while(fread(&aux,sizeof(stPedido),1,archivo)>0)
        {
            nodoProducto = buscarNodoProductoID(arbol,aux.idProducto);
            validos = agregarProductoToCliente(clientes, validos, aux.idCliente,nodoProducto->p);
        }
    }
    fclose(archivo);
    return validos;
}

/*****************************************************************************
    Funcion que carga los clientes al ADL desde el archivo clientes y
    luego carga los productos desde el archivo pedidos
*****************************************************************************/
int cargarClientesDesdeArchivos(stCelda clientes[], int dimension, nodoArbolstProducto* arbol)
{
    FILE* archivo;
    archivo = fopen(aClientes,"rb");
    int i = 0;
    if(archivo!= NULL)
    {
        stCliente aux;
        while(fread(&aux,sizeof(stCliente),1,archivo)>0 && i<dimension)
        {
            i = agregarClienteAlArreglo(clientes,i,aux);
        }
    }
    else ///si el archivo esta vacio - crea un cliente administrador que carga al arreglo (para acceder al sistema)
    {
        stCliente admin = crearAdministrador();
        i = agregarClienteAlArreglo(clientes,i,admin);
    }
    fclose(archivo);

    i = cargarPedidosAlArregloDesdeArchivo(clientes, i, arbol);

    return i;
}
stCliente crearAdministrador()
{
    stCliente admin;
    admin.idCliente = 1;
    strcpy(admin.nombre,"Sistema");
    strcpy(admin.apellido,"Administrador");
    strcpy(admin.domicilio,"Fake street 123");
    admin.genero = 'f';
    strcpy(admin.mail, "admin");
    strcpy(admin.userName,"admin");
    strcpy(admin.password,"admin");
    admin.rol = 1;
    admin.eliminado = 0;

    return admin;
}

/*****************************************************************************
    Funcion para calcular cantidad de clientes activos del archivo clientes
                    (tamaño justo del arreglo clientes)
*****************************************************************************/
int contarClientesActivos()
{
    FILE* archivo;
    archivo = fopen(aClientes,"rb");
    int cantidad = 0;
    if(archivo!= NULL)
    {
        stCliente aux;
        while(fread(&aux,sizeof(stCliente),1,archivo)>0)
        {
            if(aux.eliminado == 0)
            {
                cantidad++;
            }
        }
    }
    else
    {
        cantidad = 1;
    }
    fclose(archivo);
    return cantidad;
}
/*****************************************************************************
    Funcion para persistir las modificaciones en la lista de productos
                    (guardar en archivo productos)
******************************************************************************/
void guardarEnArchivoProductos(stProducto p)
{
    FILE *archivo;
    archivo = fopen(aProductos,"ab");
    if(archivo != NULL)
    {
        fwrite(&p,sizeof(stProducto),1,archivo);
    }
    fclose(archivo);
}
void persistirModificacionProducto(nodoListaProducto* productos)
{
    nodoListaProducto* aux = productos;
    while(aux != NULL)
    {
        guardarEnArchivoProductos(aux->p);
        aux = aux->sig;
    }
}
/******************************************************************************
    Funcion para persistir las modificaciones del arreglo de listas clientes
                (guardar en archivos clientes y pedidos)
*******************************************************************************/
void guardarEnArchivoPedidos(stPedido p)
{
    FILE *archivo;
    archivo = fopen(aPedidos,"ab");
    if(archivo != NULL)
    {
        fwrite(&p,sizeof(stPedido),1,archivo);
    }
    fclose(archivo);
}
void guardarEnArchivoClientes(stCliente c)
{
    FILE *archivo;
    archivo = fopen(aClientes,"ab");
    if(archivo != NULL)
    {
        fwrite(&c,sizeof(stCliente),1,archivo);
    }
    fclose(archivo);
}
void persistirModificaciones(stCelda clientes[],int validos)
{
    for(int i=0; i<validos; i++)
    {
        if(clientes[i].cliente.eliminado == 0)
        {
            guardarEnArchivoClientes(clientes[i].cliente);
            nodoListaProducto* aux = clientes[i].listaDeProductos;
            stPedido pedido;
            pedido.idCliente = clientes[i].cliente.idCliente;
            pedido.idPedido = i;
            while(aux != NULL)
            {
                pedido.idProducto = aux->p.idProducto;
                guardarEnArchivoPedidos(pedido);
                aux = aux->sig;
            }
        }
    }
}
/*********************************************
    Funcion de dar de alta un producto
*********************************************/
void altaProducto(nodoListaProducto **listaProducto, nodoArbolstProducto **arbolProducto)
{
    stProducto nProducto;
    nodoArbolstProducto *buscado;

    do
    {
        system("cls");
        imprimirCabecera("Alta Producto");
        printf("\n\t Ingrese el nombre del producto: ");
        fflush(stdin);
        gets(nProducto.nombre);

        buscado = buscarNodoProductoNombre(*arbolProducto, nProducto.nombre);

        if(buscado)
        {
            printf("\n\t El producto ingresado ya existe, ingrese otro.\n\n");
            system("pause");
        }
    }
    while(buscado);

    nProducto = cargaUnProducto(nProducto.nombre);

    nProducto.idProducto = ultimoID(*listaProducto) + 1;
    *listaProducto = agregaPrincipio(*listaProducto, creaNodo(nProducto));
    *arbolProducto = insertarAVL(*arbolProducto, nProducto);
    printf("\n\t El producto fue ingresado correctamente.\n\n");
    system("pause");
}

/*********************************************
                Baja Producto
*********************************************/
///baja de producto, lo elimina de la lista, del arbol y persiste los cambios en el archivo
int bajaProducto(nodoArbolstProducto** arbolProducto, nodoListaProducto** listaProducto, int idProducto)
{
    int flag = 0;
    nodoArbolstProducto* buscado;
    buscado = buscarNodoProductoID(*arbolProducto, idProducto);

    if (buscado)
    {
        printf("\n\t El siguiente producto se eliminara: \n");
        muestraProducto(buscado->p);
        (*listaProducto) = eliminarProducto((*listaProducto),idProducto); //cambia el valor de eliminado a 1
        *arbolProducto = borrarNodoIntArbol(*arbolProducto, buscado->p); //elimina el nodo del arbol
        flag = 1;
    }

    return flag;
}

void subProgramaBajaProducto(nodoArbolstProducto** arbol, nodoListaProducto** productos)
{
    char control= 's';
    while(control=='s')
    {
        system("cls");
        imprimirCabecera("Baja Producto");
        int idProducto;
        printf("\n\t Ingrese el ID del producto que desea eliminar: ");
        scanf("%d",&idProducto);

        int rta = bajaProducto(arbol,productos,idProducto);
        if(rta == 1)
        {
            printf("\n\t El producto ha sido eliminado correctamente.\n\n");
        }
        else
        {
            printf("\n\t El ID ingresado no existe en la base de datos.\n\n");
        }
        printf("\n\t Queres continuar eliminando? [s/n]: ");
        fflush(stdin);
        scanf("%c", &control);
    }
}
/*********************************************
    Funcion de modificar un producto
*********************************************/
int modificarProducto(nodoArbolstProducto** arbolProducto, nodoListaProducto** listaProducto, int id)
{
    int opcion = 0;
    int flag = 0;

    nodoArbolstProducto* buscado;
    buscado = buscarNodoProductoID(*arbolProducto, id);

    if (buscado)
    {
        muestraProducto(buscado->p);
        printf("\n\t 1. Nombre del producto");
        printf("\n\t 2. Marca del producto");
        printf("\n\t 3. Precio del producto");
        printf("\n\t Que campo deseas modificar? ");

        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("\n\t Ingresa el nuevo nombre: ");
            fflush(stdin);
            gets(buscado->p.nombre);
            flag = 1;
            break;

        case 2:
            printf("\n\t Ingresa la nueva marca: ");
            fflush(stdin);
            gets(buscado->p.marca);
            flag = 1;
            break;

        case 3:
            printf("\n\t Ingresa el nuevo precio: ");
            scanf("%f", &buscado->p.precio);
            flag = 1;
            break;

        default:
            printf("\n\t ERROR: La opcion seleccionada no existe.\n\n");
        }
        *listaProducto = modificarProductoLista(*listaProducto,buscado->p.idProducto,buscado->p);
        *arbolProducto = modificarProductoArbol(*arbolProducto,buscado->p.idProducto,buscado->p);
    }
    return flag;
}



void subProgramaModificarProducto(nodoArbolstProducto** arbol, nodoListaProducto** productos)
{
    char control= 's';
    while(control=='s')
    {
        system("cls");
        imprimirCabecera("Modificar Producto");
        int idProducto;
        printf("\n\t Ingrese el ID del producto que desea modificar: ");
        scanf("%d",&idProducto);

        int rta = modificarProducto(arbol, productos, idProducto);
        if(rta == 1)
        {
            printf("\n\t El producto ha sido modificado correcamente\n\n");
        }
        else
        {
            printf("\n\t El ID ingresado no existe en la base de datos.\n\n");
        }
        printf("\n\t Queres continuar haciendo modificaciones? [s/n]: ");
        fflush(stdin);
        scanf("%c", &control);
    }
}

/************************************
            Alta cliente
**********************************+*/
int altaCliente(stCelda clientes[], int validos, int rolCliente)
{
    stCliente auxiliar;
    int buscado;
    do
    {
        system("cls");
        imprimirCabecera("Registro del Cliente");
        printf("\n\t\tIngrese un nombre de usuario: ");
        fflush(stdin);
        gets(auxiliar.userName);

        buscado = buscarUsernameCliente(clientes, validos, auxiliar.userName);

        if(buscado != -1) //es decir, encontro un cliente con ese username
        {
            printf("\n\t El User Name ingresado ya existe, ingrese otro.\n\n");
            system("pause");
        }
    }
    while(buscado != -1); //hasta que el username sea valido

    auxiliar = cargaUnCliente(auxiliar.userName); //cambie la funcion de alta para que no vuelva a pedir el username
    auxiliar.rol = rolCliente;
    auxiliar.idCliente = clientes[validos-1].cliente.idCliente + 1; //se asigna un id al cliente, posterior al ultimo cliente
    stCelda* aux = NULL;
    aux = (stCelda*) realloc(clientes, sizeof(stCelda)*(validos+1));  //aumentamos la capacidad del arreglo dinamico
    if(aux != NULL)
    {
        validos = agregarClienteAlArreglo(aux, validos, auxiliar); //agregamos el cliente al arreglo
        clientes = aux;
        printf("\n\t El cliente fue ingresado correctamente.\n\n");
    }
    else
    {
        printf("\n\t Algo Fallo, el cliente no fue ingresado correctamente.\n\n");
    }

    return validos;
}


int asignarRolCliente()
{
    int rol;
    do
    {
        printf("\n\t ==> Rol - 1 (admin)/ 0 (cliente):  ");
        scanf("%d", &rol);

        if(rol != 0 && rol != 1)
        {
            printf("\n\t El valor ingresado no es correcto. \n\t Vuelva a intentar.");
        }

    }
    while(rol != 0 && rol != 1);
    return rol;
}

/******************************************************
    Funcion para modificar un cliente
*****************************************************/
void subProgramaModificarCliente(stCelda clientes[], int validos)
{
    char control= 's';
    while(control=='s')
    {
        system("cls");
        imprimirCabecera("Modificar Cliente");
        int idCliente;
        printf("\n\t Ingrese el ID del cliente que desea modificar: ");
        scanf("%d",&idCliente);

        int rta = modificarCliente(clientes,validos,idCliente);
        if(rta == 1)
        {
            printf("\n\t El cliente ha sido modificado correcamente.\n\n");
        }
        else
        {
            printf("\n\t El ID ingresado no existe en la base de datos.\n\n");
        }
        printf("\n\t Queres continuar haciendo modificaciones? [s/n]: ");
        fflush(stdin);
        scanf("%c", &control);
    }
}

int  modificarCliente(stCelda adl[], int validos, int idCliente)
{
    int flag = 0;
    int pos = buscarCliente(adl, validos, idCliente);
    if (pos != -1)
    {
        mostrarCliente(adl[pos].cliente);
        int opcion = menuModificacionesCliente();
        flag = 1;
        char genero;
        int rol;
        switch(opcion)
        {
        case 1:
            printf("\n\t Ingrese el nuevo Nombre: ");
            fflush(stdin);
            gets(adl[pos].cliente.nombre);
            break;

        case 2:
            printf("\n\t Ingrese el nuevo Apellido: ");
            fflush(stdin);
            gets(adl[pos].cliente.apellido);
            break;

        case 3:
            do
            {
                char userName[20];
                printf("\n\t Ingrese el nuevo UserName: ");
                fflush(stdin);
                gets(userName);
                int  pos = buscarUsernameCliente(adl, validos, userName);
                if(pos != -1)
                {
                    printf("\n\t El usuario ya se encuentra registrado.\n\t Vuelva a ingresar los datos.\n\n");
                }
                else
                {
                    strcpy(adl[pos].cliente.userName, userName);
                }
            }
            while(pos != -1);
            break;
        case 4:
            printf("\n\t Ingrese la nueva contraseña: ");
            fflush(stdin);
            gets(adl[pos].cliente.password);

            break;
        case 5:
            printf("\n\t Ingrese nuevo mail: ");
            fflush(stdin);
            gets(adl[pos].cliente.mail);
            break;

        case 6:
            printf("\n\t Ingrese el nuevo Domicilio: ");
            fflush(stdin);
            gets(adl[pos].cliente.domicilio);
            break;

        case 7:
            do
            {
                printf("\n\t Ingrese el nuevo genero m / f : ");
                fflush(stdin);
                scanf("%c", &genero);
                if(genero != 'm' && genero != 'f' && genero != 'M' && genero != 'F')
                {
                    printf("\n\t El valor ingresado no es correcto. \n\t Vuelva a intentar.");
                }
                else
                {
                    adl[pos].cliente.genero = genero;
                }
            }
            while(genero != 'm' && genero != 'f' && genero != 'M' && genero != 'F');
            break;

        case 8:
            do
            {
                printf("\n\t ==> Rol - 1 (admin)/ 0 (cliente):  ");
                scanf("%d", &rol);

                if(rol != 0 && rol != 1)
                {
                    printf("\n\t El valor ingresado no es correcto. \n\t Vuelva a intentar.");
                }
                else
                {
                    adl[pos].cliente.rol = rol;
                }
            }
            while(rol != 0 && rol != 1);
            break;
        default:
            printf("\n\t ERROR: La opcion seleccionada no existe.\n\n");
        }
    }
    return flag;
}

/************************************************************
                Menu de modificaciones
***********************************************************/
int menuModificacionesCliente()
{
    int eleccion = 0;
    printf("\n\n\n\t1. Nombre");
    printf("\n\t2. Apellido ");
    printf("\n\t3. Nombre de Usuario ");
    printf("\n\t4. Password ");
    printf("\n\t5. Mail ");
    printf("\n\t6. Domicilio ");
    printf("\n\t7. Genero ");
    printf("\n\t8. Rol ");
    printf("\n\tElija que desea modificar: ");
    scanf("%d", &eleccion);

    return eleccion;
}
/*********************************************
    Funcion de dar de baja un cliente
*********************************************/
void subprogramaBajaCliente(stCelda clientes[], int validos)
{
    char control= 's';
    while(control=='s')
    {
        system("cls");
        imprimirCabecera("Baja Cliente");
        int idCliente;
        printf("\n\t Ingrese el ID del cliente que desea dar de baja: ");
        scanf("%d",&idCliente);

        int rta = bajaCliente(clientes,validos,idCliente);
        if(rta == 1)
        {
            printf("\n\t El cliente ha sido eliminado correctamente\n\n");
        }
        else
        {
            printf("\n\t El ID ingresado no existe en la base de datos. \n\n");
        }
        printf("\n\t Queres continuar realizando bajas? [s/n]: ");
        fflush(stdin);
        scanf("%c", &control);
    }
}
int bajaCliente(stCelda clientes[], int validos, int idCliente)
{
    int flag = 0;
    int pos = buscarCliente(clientes, validos, idCliente);
    if(pos != -1)
    {
        mostrarCliente(clientes[pos].cliente);
        clientes[pos].cliente.eliminado = 1;
        flag = 1;
    }
    return flag;
}

/*********************************************
            Funcion de Login
*********************************************/
///retorna 1 y copia en cLogin los datos del cliente que se esta loggeando, sino devuelve 0
int login(stCelda clientes[], int validos, stCliente* cLogin)
{
    int flag = 0;
    char username[30];
    char password[20];
    int pos;
    char control= 's';
    do
    {
        system("cls");
        imprimirCabecera("Login");
        printf("\n\t Ingrese el nombre de usuario: ");
        fflush(stdin);
        scanf("%s",username);

        pos = buscarUsernameCliente(clientes, validos, username);
        if(pos == -1) //es decir, no se encontro un cliente con ese username
        {
            printf("\n\t El usuario no se encuentra registrado.\n\t Vuelva a ingresar los datos.\n\n");
            printf("\n Presione 's' para continuar intentando, o presione 'n' para volver al menu principal: ");
            fflush(stdin);
            scanf("%c", &control);

        }
        else
        {
            do
            {
                printf("\n\t Ingrese la contrase%ca de usuario: ", 164);
                fflush(stdin);
                scanf("%s",password);

                if(strcmp(clientes[pos].cliente.password, password)!= 0)
                {
                    printf("\n\t La contrase%ca no es correcta.\n\t Vuelva a ingresarla.\n\n", 164);
                    printf("\n Presione 's' para continuar intentando, o presione 'n' para volver al menu principal: ");
                    fflush(stdin);
                    scanf("%c", &control);
                }
                else
                {
                    flag = 1;
                    (*cLogin) = clientes[pos].cliente;
                    printf("\n\t presione 'c' para continuar: ");
                    fflush(stdin);
                    scanf("%c", &control);
                }
            }
            while (control == 's');
        }
    }
    while(control == 's'); //hasta que el usuario quiera

    return flag;
}
/*****************************************************
    Funcion agregar productos en pedido de cliente
*****************************************************/
///pide seleccionar un producto y lo agrega al pedido de un cliente
void subprogramaAgregarProductoAlPedido(stCelda clientes[], int validos, int idCliente, nodoArbolstProducto* arbol, nodoListaProducto* productos)
{
    char control= 's';
    int idProducto;
    nodoArbolstProducto* aux;
    while(control=='s')
    {
        system("cls");
        imprimirCabecera("Agregar Producto");
        recorrerYMostrar(productos);

        printf("\n\t Ingrese el ID del producto que desea agregar: ");
        scanf("%d",&idProducto);

        aux = buscarNodoProductoID(arbol, idProducto);
        if(aux)
        {
            validos = agregarProductoToCliente(clientes, validos, idCliente, aux->p);
            clientes = (stCelda*) realloc(clientes, sizeof(stCelda)*validos);
            printf("\n\t El producto ha sido agregado correcamente.\n\n");
        }
        else
        {
            printf("\n\t El ID ingresado no existe en la base de datos.\n\n");
        }
        printf("\n\t Queres continuar agregando productos? [s/n]: ");
        fflush(stdin);
        scanf("%c", &control);
    }
}

/*****************************************************
            Funcion consulta de clientes
*****************************************************/
void subprogramaConsultaProducto(nodoArbolstProducto* arbol)
{
    char control= 's';
    int idProducto;
    nodoArbolstProducto* aux;
    while(control=='s')
    {
        system("cls");
        imprimirCabecera("Consulta Producto");
        printf("\n\t Ingrese el ID del producto que desea consultar: ");
        scanf("%d",&idProducto);
        aux = buscarNodoProductoID(arbol, idProducto);
        if(aux)
        {
            muestraProducto(aux->p);
            printf("\n\n");
        }
        else
        {
            printf("\n\t El ID ingresado no existe en la base de datos.\n\n");
        }
        printf("\n\t Queres continuar consultando productos? [s/n]: ");
        fflush(stdin);
        scanf("%c", &control);
    }
}
///pide ingresar un id producto y muestra al cliente
void subprogramaConsultaCliente(stCelda clientes[], int validos)
{
    char control= 's';
    int idCliente;
    int pos;
    while(control=='s')
    {
        system("cls");
        imprimirCabecera("Consulta Cliente");
        printf("\n\t Ingrese el ID del cliente que desea consultar: ");
        scanf("%d",&idCliente);
        pos = buscarCliente(clientes, validos, idCliente);
        if(pos != -1)
        {
            mostrarCliente(clientes[pos].cliente);
            printf("\n\n");
        }
        else
        {
            printf("\n\t El ID ingresado no existe en la base de datos.\n\n");
        }
        printf("\n\t Queres continuar consultando clientes? [s/n]: ");
        fflush(stdin);
        scanf("%c", &control);
    }
}

void recomendarProductosPorMarca(stCelda clientes[], int validos, int idCliente, nodoListaProducto* productos)
{
    stProducto producto;
    int pos = buscarCliente(clientes, validos, idCliente);
    //mostrarCliente(clientes[pos].cliente);
    if(clientes[pos].listaDeProductos)
    {
        producto = encontrarPrimero(clientes[pos].listaDeProductos);
    }
    else
    {
        producto = encontrarPrimero(productos);
    }
    mostrarProductosPorMarca(productos,producto);
}




