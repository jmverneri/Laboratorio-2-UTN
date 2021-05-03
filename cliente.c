#include "cliente.h"


/**********************************************************************************
Funcion que permite cargar un solo cliente por el usuario.
Es una subfuncion que sera llamada por otra para cargar hasta que el usuario desee.
**********************************************************************************/
stCliente cargaUnCliente(char username[])
{
    stCliente cliente;
    strcpy(cliente.userName, username);

    printf("\n\t Completar todos los campos obligatorios");
    printf("\n\t --------------------------------------------------------");

    printf("\n\t ==> Contrase%ca: ",164);
    fflush(stdin);
    gets(cliente.password);

    printf("\n\t ==> Nombre: ");
    fflush(stdin);
    gets(cliente.nombre);

    printf("\n\t ==> Apellido: ");
    fflush(stdin);
    gets(cliente.apellido);

    printf("\n\t ==> Mail: ");
    fflush(stdin);
    gets(cliente.mail);

    printf("\n\t ==> Domicilio: ");
    fflush(stdin);
    gets(cliente.domicilio);

    do
    {
        printf("\n\t ==> Genero - m(masculino)/ f(femenino): ");
        fflush(stdin);
        scanf("%c", &cliente.genero);
        if(cliente.genero != 'm' && cliente.genero != 'f' && cliente.genero != 'M' && cliente.genero != 'F')
        {
            printf("\n\t El valor ingresado no es correcto. \n\t Vuelva a intentar.");
        }

    } while(cliente.genero != 'm' && cliente.genero != 'f' && cliente.genero != 'M' && cliente.genero != 'F');

    printf("\n\t ==> Gracias por registrarse %s\n\n", cliente.nombre);

    cliente.eliminado = 0;  /// indica 1 o 0 si el cliente fue eliminado

    return cliente;
}

/******************************************
Funcion que muestra los datos de un cliente
*******************************************/
void mostrarCliente(stCliente c)
{
    printf("\n\t Cliente Nro: %d",c.idCliente);
    printf("\n\t Nombre: %s",c.nombre);
    printf("\n\t Apellido: %s",c.apellido);
    printf("\n\t Nombre de Usuario: %s",c.userName);
    printf("\n\t Mail: %s",c.mail);
    printf("\n\t Domicilio: %s",c.domicilio);

    if(c.genero == 'm')
    {
        printf("\n\t Genero:  Masculino");
    }
    else
    {
        printf("\n\t Genero:  Femenino");
    }

    if(c.rol == 1)
    {
        printf("\n\t Rol:  Administrador");
    }
    else
    {
        printf("\n\t Rol:  Cliente");
    }
    printf("\n");
}






