
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "conio.h"
#include "pacientes.h"
#include "ingresos_Labo.h"
#include "practicas_ingreso.h"
#include "practicas_Labo.h"
#include "empleado_laboratorio.h"

#define ARCHIVO_PACIENTES "pacientes.dat"
#define ARCHIVO_EMPLEADOS "archivo_empleados.dat"
#define ARCHIVO_PRACXINGRESO "practicaXingreso.dat"
#define ARCHIVO_INGRESOS "ingresos.dat"
#define Practicas_Laboratorio "practicas.dat"

#define BORRAR system("cls")
#define PAUSA system("pause")


#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 5
#define MAX_INTENTOS 3

empleados_laboratorio crearRegistroEmpleados()
{
    marco_menu();
    gotoxy(52,2);
    printf("ALTA DE EMPLEADO");
    empleados_laboratorio empleado;

    char ok ='n';

    while(ok == 'n' || ok == 'N')
    {
        gotoxy(20,6);
        printf("Ingrese DNI: ");///verificar int HACER FUNCION
        gotoxy(20,7);
        printf("Ingrese Apellido y Nombre: ");///verificar string HACER FUNCION
        gotoxy(20,8);
        printf("Ingrese el Usuario que desea registrar: ");
        gotoxy(20,9);
        printf("Ingrese la Clave que desea registrar: ");
        gotoxy(20,10);
        printf("Ingrese su perfil (administrador/empleado/bioquimico) : ");
        fflush(stdin);
        gotoxy(33,6);
        scanf("%d",&empleado.dni);

        fflush(stdin);
        gotoxy(47,7);
        gets(empleado.ape_nombre);

        fflush(stdin);
        gotoxy(60,8);
        gets(empleado.usuario);

        fflush(stdin);
        gotoxy(58,9);
        gets(empleado.clave);

        fflush(stdin);
        gotoxy(75,10);
        gets(empleado.perfil);

        empleado.eliminado=0;

        BORRAR;
        marco_menu();
        gotoxy(52,2);
        printf("ALTA DE EMPLEADO");
        mostrar_un_empleado(empleado,35,8);

        gotoxy(35,14);
        printf("Los Datos ingresados son correctos? s/n : ");
        fflush(stdin);
        gotoxy(58,14);
        ok=getch();

        if(ok == 'n' || ok == 'N')
        {
            gotoxy(40,16);
            printf("\nIngrese los datos nuevamente...\n\n");
            getch();
            BORRAR;
        }
    }

    return empleado;
}

void mostrar_un_empleado(empleados_laboratorio empleado, int x, int y)
{
    gotoxy(x,y++);
    printf("=====================================================");
    gotoxy(x,y++);
    printf("APELLIDO Y NOMBRE: %s [%s]", empleado.ape_nombre,empleado.perfil);
    gotoxy(x,y++);
    printf("DNI: %d", empleado.dni);
    gotoxy(x,y++);
    printf("USUARIO : [%s]", empleado.usuario);
    gotoxy(x,y++);
    printf("CLAVE :[%s]", empleado.clave);
    gotoxy(x,y++);
    printf("=====================================================");
}

void alta_empleado(char archivoEmpleado[])
{
    empleados_laboratorio empleado;

    char modifica_empleado;
    char activacion;

    FILE * arch=fopen(archivoEmpleado,"ab");

    if(arch)
    {
        empleado=crearRegistroEmpleados();
        marco_menu();
        gotoxy(52,2);
        printf("ALTA DE EMPLEADO");

        if(verificar_archivo_empleados(archivoEmpleado,empleado.dni)==0 && verificar_usuario_unico(archivoEmpleado,empleado.usuario)==0)
        {
            fwrite(&empleado,sizeof(empleados_laboratorio),1,arch);
        }
        else
        {
            if(verificar_archivo_empleados(archivoEmpleado,empleado.dni)==1)
            {
                gotoxy(20,5);
                printf("El Empleado que esta ingresando ya existe en los registros. Desea Modificarlo? s/n ");
                fflush(stdin);
                scanf("%c",&modifica_empleado);
                BORRAR;

                if(modifica_empleado=='s'||modifica_empleado=='S')
                {
                    modificacion_de_empleado(archivoEmpleado,empleado.dni);
                }
            }
            else
            {
                if(verificar_usuario_unico(archivoEmpleado,empleado.usuario)==1)
                {
                    gotoxy(20,5);
                    printf("El USUARIO que ingreso ya existe en la base de datos vuelva a ingresarlo");
                    PAUSA;
                    BORRAR;
                }

                if(verificar_archivo_empleados(archivoEmpleado,empleado.dni)==-1)
                {
                    BORRAR;
                    marco_menu();
                    gotoxy(52,2);
                    printf("ALTA DE EMPLEADO");

                    gotoxy(20,6);
                    printf("El empleado se encuentra dado de baja. Desea reactivarlo? s/n ");
                    fflush(stdin);
                    scanf("%c",&activacion);

                    if(activacion=='s'||activacion=='S')
                    {
                        reactivacion_empleado(archivoEmpleado,empleado.dni);
                    }
                }
            }
        }
        fclose(arch);
    }
    else
    {
        marco_menu();
        gotoxy(52,2);
        printf("ALTA DE EMPLEADO");
        gotoxy(30,5);
        printf("\nERROR AL ABRIR EL ARCHIVO. LLAME AL INTERNO 111\n");
    }
}


int verificar_archivo_empleados(char archivo[],int DNI)
{
    empleados_laboratorio empleado;
    int encontrado=0;

    FILE * arch=fopen(archivo,"rb");


    if(arch)
    {
        while(encontrado==0 && fread(&empleado,sizeof(empleados_laboratorio),1,arch)>0)
        {
            if(empleado.dni==DNI)
            {
                if(empleado.eliminado==0)
                {
                    encontrado=1;
                }
                else
                {
                    printf("EMPLEADO DADO DE BAJA");
                    encontrado=-1;
                }
            }
        }
        fclose(arch);

    }
    return encontrado;
}


int verificar_usuario_unico(char archivo[],char usuarioNuevo[])
{
    empleados_laboratorio empleado;

    int encontrado=0;

    FILE * arch=fopen(archivo,"rb");


    if(arch)
    {
        while(encontrado==0 && fread(&empleado,sizeof(empleados_laboratorio),1,arch)>0)
        {
            if(strcmp(empleado.usuario,usuarioNuevo)==0)
            {
                encontrado=1;
            }
        }
        fclose(arch);
    }

    return encontrado;
}

void baja_empleado(char archivoEmpleado[],int dni)
{
    marco_menu();
    gotoxy(52,2);
    printf("BAJA DE EMPLEADO");

    empleados_laboratorio empleado;
    int encontrado=0;

    if(verificar_archivo_empleados(archivoEmpleado,dni)==1)
    {
        FILE * arch=fopen(archivoEmpleado,"r+b");

        if(arch)
        {
            while(encontrado == 0 && fread(&empleado,sizeof(empleados_laboratorio),1,arch)>0)
            {
                if(empleado.dni==dni)
                {
                    encontrado=1;///el while corta en la posicion del empleado buscado
                }
            }
            gotoxy(30,6);
            printf("Usted quiere dar de baja al siguiente empleado");
            mostrar_un_empleado(empleado,25,8);
            char eliminar;
            gotoxy(25,15);
            printf("Presione \"s\" si es correcto sino presione cualquier tecla: ");
            fflush(stdin);
            gotoxy(85,15);
            scanf("%c",&eliminar);

            if(eliminar=='s'||eliminar=='S')
            {
                empleado.eliminado=1;///modifico

                fseek(arch,sizeof(empleados_laboratorio)*-1,SEEK_CUR);
                fwrite(&empleado,sizeof(empleados_laboratorio),1,arch);///grabo
                gotoxy(45,18);
                printf("Baja de Empleado Exitosa");
            }

            else
            {
                gotoxy(45,18);
                printf("Cambio NO realizado, vuelva a intentarlo");
            }

            fclose(arch);
        }

    }

}

void modificacion_de_empleado(char archivoEmpleados[],int dni)
{
    empleados_laboratorio empleado;
    int encontrado=0;
    if(verificar_archivo_empleados(archivoEmpleados,dni)==1)
    {
        FILE * arch=fopen(archivoEmpleados,"r+b");
        if(arch)
        {
            while(encontrado == 0 && fread(&empleado,sizeof(empleados_laboratorio),1,arch)>0)
            {
                if(empleado.dni==dni)
                {
                    encontrado=1;///el while corta en la posicion del empleado buscado
                }
            }
            gotoxy(30,8);
            printf("Usted quiere modificar el siguiente empleado");
            mostrar_un_empleado(empleado,25,9);

            char modificar;
            gotoxy(25,15);
            printf("Presione \"s\" si es correcto sino presione cualquier tecla... ");
            fflush(stdin);
            gotoxy(85,15);
            scanf("%c",&modificar);

            if(modificar=='s'||modificar=='S')
            {
                menu_modifica_campo_registro(arch,empleado);
                fclose(arch);
            }
            else
            {
                marco_borde_ancho();
                gotoxy(42,3);
                printf("Vuelva a Seleccionar una opcion o seleccione SALIR");
            }
        }

    }
    else
    {
        marco_borde_ancho();
        gotoxy(42,6);
        printf("El empleado que desea modificar NO existe en la base de datos");
    }
}

void listado_empleados_vigentes(char archivoEmpleados[])
{
    empleados_laboratorio empleado;
    gotoxy(43,2);
    printf("LISTADO DE EMPLEADOS VIGENTES");

    empleados_laboratorio arreglo[30];///arreglo para pasar de manera ordenada.
    int validos=0;

    FILE * arch=fopen(archivoEmpleados,"rb");

    if(arch)
    {
        while(fread(&empleado,sizeof(empleados_laboratorio),1,arch)>0)
        {
            if(empleado.eliminado==0)
            {
                validos=cargar_arreglo_ordenado_x_apellido(&arreglo,empleado,validos);
            }
        }
        if(validos==0)
        {
            gotoxy(45,4);
            printf("NO EXISTEN EMPLEADOS EN NOMINA");
            getch();
        }
        else
        {
            mostrar_arreglo_empleados(arreglo,validos);
        }

        fclose(arch);
    }
    else
    {
        gotoxy(40,6);
        printf("EL ARCHIVO NO PUDO ABRIRSE CORRECTAMENTE. LLAME AL 111");
        gotoxy(40,8);
        PAUSA;
    }

    getch();
}

int cargar_arreglo_ordenado_x_apellido(empleados_laboratorio * arreglo, empleados_laboratorio empleado, int validos)
{
    int stop=0;
    int pos=validos;

    while(stop ==0 && pos>0)
    {
        if(strcmpi(arreglo[pos-1].ape_nombre,empleado.ape_nombre)>0)
        {
            arreglo[pos]=arreglo[pos-1];
            pos--;
        }
        else
        {
            arreglo[pos]=empleado;
            validos++;
            stop=1;
        }
    }
    if(stop==0)
    {
        arreglo[0]=empleado;
        validos++;
    }

    return validos;
}

void mostrar_arreglo_empleados(empleados_laboratorio arreglo[],int validos)
{
    int i=0;
    int x=28,y=4;///coordenadas para imprimir

    while(i<validos)
    {
        mostrar_un_empleado(arreglo[i],x,y);
        y=y+7;
        i++;
    }
}

void listado_empleados_eliminados(char archivoEmpleados[])
{
    marco_menu();

    empleados_laboratorio empleado;
    int eliminados=0;

    FILE * arch=fopen(archivoEmpleados,"rb");

    if(arch)
    {
        gotoxy(43,2);
        printf("LISTADO DE EMPLEADOS NO VIGENTES");
        int x=28,y=6;

        while(fread(&empleado,sizeof(empleados_laboratorio),1,arch)>0)
        {
            if(empleado.eliminado==1)
            {
                mostrar_un_empleado(empleado,x,y);
                y=y+7;
                getch();
                eliminados++;
            }
        }
        if(eliminados==0)
        {
            gotoxy(45,6);
            printf("NO EXISTEN EMPLEADOS DADOS DE BAJA");
            getch();
        }
        fclose(arch);
    }
    else
    {
        gotoxy(30,6);
        printf("EL ARCHIVO NO PUDO ABRIRSE CORRECTAMENTE. LLAME AL 111");
        gotoxy(40,6);
        PAUSA;
    }
}

int validacion_usuarioYclave(char archivoEmpleados[], char perfil[])
{
    empleados_laboratorio empleado;
    int habilitado=0;
    int i=0;
    char usuario[20];
    char clave[20];
    char caracter;
    gotoxy(57,12);
    fflush(stdin);
    gets(usuario);
    gotoxy(59,17);

    while (caracter = getch())
    {
        if (caracter == TECLA_ENTER)
        {
            clave[i] = '\0';
            break;

        }
        else if (caracter == TECLA_BACKSPACE)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }

        }
        else
        {
            if (i < LONGITUD)
            {
                printf("*");
                clave[i] = caracter;
                i++;
            }
        }
    }
    BORRAR;

    FILE * arch=fopen(archivoEmpleados,"rb");

    if(arch)
    {
        while(fread(&empleado,sizeof(empleados_laboratorio),1,arch)>0)
        {
            if(strcmp(empleado.usuario,usuario)==0 && strcmp(empleado.clave,clave)==0 && strcmpi(empleado.perfil,perfil)==0)
            {
                habilitado=1;
            }
        }
        fclose(arch);
    }
    return habilitado;
}

void mostrar_archivo(char archivo[])
{
    pacientes empleado;

    FILE * arch=fopen(archivo,"rb");

    if(arch)
    {
        while(fread(&empleado,sizeof(pacientes),1,arch)>0)
        {
            printf("\n APELLIDO Y NOMBRE = %s", empleado.nomb_apell);
            printf("\n               DNI = %d",empleado.dni);
            /*printf("\n           USUARIO = %s",empleado.usuario);
            printf("\n             CLAVE = %s",empleado.clave);
            printf("\n            PERFIL = %s", empleado.perfil);*/
            printf("\n=================================================\n");
        }
        fclose(arch);
    }
}

void menu_modifica_campo_registro(FILE * archivo, empleados_laboratorio empleado)
{
menu:
    BORRAR;
    system("COLOR E");
    marco_menu();

    int opc;
    char rta;

    gotoxy(48,2);
    printf("MODIFICA EMPLEADO");
    gotoxy(35,7);
    printf("Seleccione el campo que desea modificar");

    gotoxy(43,9);
    printf("1) NOMBRE Y APELLIDO");
    gotoxy(43,10);
    printf("2) DNI");
    gotoxy(43,11);
    printf("3) USUARIO");
    gotoxy(43,12);
    printf("4) CLAVE");
    gotoxy(43,13);
    printf("5) PERFIL");
    gotoxy(43,14);
    printf("6) SALIR...");
    gotoxy(45,15);
    printf("OPCION SELECCIONADA...");
    gotoxy(70,15);
    scanf("%d",&opc);

    do
    {
        switch(opc)
        {
        case 1:
            BORRAR;
            marco_menu();
            gotoxy(48,2);
            printf("MODIFICA APELLIDO Y NOMBRE");
            gotoxy(30,5);
            printf("Ingrese el nuevo Apellido y Nombre : ");
            fflush(stdin);
            gets(empleado.ape_nombre);///validar string
            mostrar_un_empleado(empleado,30,7);
            gotoxy(30,13);
            printf("Los datos son correctos? s/n : ");
            fflush(stdin);
            gotoxy(63,13);
            scanf("%c",&rta);
            if(rta=='s'|| rta=='S')
            {
                fseek(archivo,sizeof(empleados_laboratorio)*-1,SEEK_CUR);
                fwrite(&empleado,sizeof(empleados_laboratorio),1,archivo);
                gotoxy(30,15);
                printf("MODIFICACION EXITOSA");///no me modifica el archivo.
                getch();
            }
            else
            {
                gotoxy(20,15);
                printf("VUELVA A SELECCIONAR LA OPCION A MODIFICAR O PRESIONE SALIR");
                getch();
            }
            goto menu;

        case 2:
            BORRAR;
            marco_menu();
            gotoxy(48,2);
            printf("MODIFICA DNI");
            gotoxy(30,5);
            printf("Ingrese el nuevo Dni : ");
            fflush(stdin);
            gets(empleado.dni);///validar string
            mostrar_un_empleado(empleado,30,7);
            gotoxy(30,13);
            printf("Los datos son correctos? s/n : ");
            fflush(stdin);
            scanf("%c",&rta);
            if(rta=='s'|| rta=='S')
            {
                fseek(archivo,sizeof(empleados_laboratorio)*-1,SEEK_CUR);
                fwrite(&empleado,sizeof(empleados_laboratorio),1,archivo);
                gotoxy(30,15);
                printf("MODIFICACION EXITOSA");
            }
            else
            {
                gotoxy(20,15);
                printf("VUELVA A SELECCIONAR LA OPCION A MODIFICAR O PRESIONE SALIR");
            }
            goto menu;

        case 3:
            BORRAR;
            marco_menu();
            gotoxy(48,2);
            printf("MODIFICA USUARIO");
            gotoxy(30,5);
            printf("Ingrese el nuevo Usuario: ");
            fflush(stdin);
            gets(empleado.usuario);///validar string
            mostrar_un_empleado(empleado,30,7);
            gotoxy(30,13);
            printf("Los datos son correctos? s/n : ");
            fflush(stdin);
            scanf("%c",&rta);
            if(rta=='s'|| rta=='S')
            {
                fseek(archivo,sizeof(empleados_laboratorio)*-1,SEEK_CUR);
                fwrite(&empleado,sizeof(empleados_laboratorio),1,archivo);
                gotoxy(30,15);
                printf("MODIFICACION EXITOSA");
            }
            else
            {
                gotoxy(20,15);
                printf("VUELVA A SELECCIONAR LA OPCION A MODIFICAR O PRESIONE SALIR");
            }
            goto menu;

        case 4:
            BORRAR;
            marco_menu();
            gotoxy(48,2);
            printf("MODIFICA CLAVE");
            gotoxy(30,5);
            printf("Ingrese la nueva Clave : ");
            fflush(stdin);
            gets(empleado.clave);///validar string
            mostrar_un_empleado(empleado,30,7);
            gotoxy(30,13);
            printf("Los datos son correctos? s/n : ");
            fflush(stdin);
            scanf("%c",&rta);
            if(rta=='s'|| rta=='S')
            {
                fseek(archivo,sizeof(empleados_laboratorio)*-1,SEEK_CUR);
                fwrite(&empleado,sizeof(empleados_laboratorio),1,archivo);
                gotoxy(30,15);
                printf("MODIFICACION EXITOSA");
            }
            else
            {
                gotoxy(20,15);
                printf("VUELVA A SELECCIONAR LA OPCION A MODIFICAR O PRESIONE SALIR");
            }
            goto menu;

        case 5:
            BORRAR;
            marco_menu();
            gotoxy(48,2);
            printf("MODIFICA PERFIL EMPLEADO");
            gotoxy(30,5);
            printf("Ingrese el nuevo Perfil : ");
            fflush(stdin);
            gets(empleado.perfil);///validar string
            mostrar_un_empleado(empleado,30,7);
            gotoxy(30,13);
            printf("Los datos son correctos? s/n : ");
            fflush(stdin);
            scanf("%c",&rta);
            if(rta=='s'|| rta=='S')
            {
                fseek(archivo,sizeof(empleados_laboratorio)*-1,SEEK_CUR);
                fwrite(&empleado,sizeof(empleados_laboratorio),1,archivo);
                gotoxy(30,15);
                printf("MODIFICACION EXITOSA");
            }
            else
            {
                gotoxy(20,15);
                printf("VUELVA A SELECCIONAR LA OPCION A MODIFICAR O PRESIONE SALIR");
            }
            goto menu;

        case 6:
            BORRAR;
            break;
        }
    }
    while(opc!=6);
}

void reactivacion_empleado(char archivoEmpleado[], int dni)
{
    FILE * arch=fopen(archivoEmpleado,"r+b");
    empleados_laboratorio empleado;
    int flag=0;

    if(arch)
    {
        while(flag==0 && fread(&empleado,sizeof(empleados_laboratorio),1,arch)>0)
        {
            if(empleado.dni==dni)
            {
                empleado.eliminado=0;
                fseek(arch,-1*sizeof(empleados_laboratorio),SEEK_CUR);
                fwrite(&empleado,sizeof(empleados_laboratorio),1,arch);
                gotoxy(45,8);
                printf("Reactivacion Exitosa!");
                flag=1;
            }
        }

        fclose(arch);
    }
}
