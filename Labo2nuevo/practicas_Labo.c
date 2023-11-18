
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

practicas CrearPracticaLaboratorio ()
{
    marco_menu();
    gotoxy(48,2);printf("ALTA DE PRACTICA");

    practicas nuevaPractica;

    nuevaPractica.nro_de_practica=autoincrementalPracticas(Practicas_Laboratorio);
    gotoxy(30,6);printf("Ingrese el nombre de la practica: ");
    fflush(stdin);
    gotoxy(65,6);gets(nuevaPractica.nombre);
    nuevaPractica.vigencia=0;

    return nuevaPractica;
}

int autoincrementalPracticas(char archivo[])
{
    FILE * archi = fopen(archivo, "rb");

    practicas p;
    int i=0;

    if(archi)
    {
        fseek(archi, sizeof(practicas)*-1,SEEK_END);
        while(fread(&p, sizeof(practicas), 1, archi)>0)
        {
            i=p.nro_de_practica;
        }
        fclose(archi);
    }

    return i+1;
}

///funcion para verificar si existe la practica
int verificarSiExistePractica(char archivo[], char PracticaNueva[])
{
    int flag = 0;

    FILE * arch=fopen(archivo,"rb");
    practicas PracticaExistente;

    if(arch)
    {
        while(flag == 0 && fread(&PracticaExistente, sizeof(practicas), 1, arch)>0)
        {
            if(strcmpi(PracticaExistente.nombre, PracticaNueva)==0)
            {
                if(PracticaExistente.vigencia==0)
                {
                    flag = PracticaExistente.nro_de_practica;///retorna id practica cuando la practica existe y esta activa
                }
                else
                {
                    flag=-1;///retorna -1 cuando la practica existe pero esta dada de baja;
                }
            }
        }
        fclose(arch);
    }

    return flag;
}

///damos de alta una nueva práctica por usuario, verificando que no exista previamente en el archivo de prácticas
void AltaDePracticasNuevas()
{
    char opcion='s', modifica, reactiva;

    while(opcion == 's'||opcion=='S')
    {
        practicas NuevaPractica=CrearPracticaLaboratorio();

        if(verificarSiExistePractica(Practicas_Laboratorio, NuevaPractica.nombre)==0)
        {
            FILE * archivo = fopen(Practicas_Laboratorio, "ab");

            if(archivo)
            {
                marco_menu();
                gotoxy(52,2);
                printf("ALTA DE PRACTICA");
                fwrite(&NuevaPractica, sizeof(practicas), 1, archivo);
                fclose(archivo);

                gotoxy(30,7);printf("¿Desea seguir cargando prácticas? \"s\" o \"n\": ");
                fflush(stdin);
                gotoxy(80,7);scanf("%c",&opcion);

                BORRAR;
            }
            else
            {
                marco_menu();
                gotoxy(52,2);
                printf("ALTA DE PRACTICA");
                gotoxy(30,6);
                printf("No se pudo abrir el archivo. Llame al interno 111\n");
                opcion='n';///frena el while
            }
        }
        else
        {
            marco_menu();
            gotoxy(52,2);
            printf("ALTA DE PRACTICA");

            if(verificarSiExistePractica(Practicas_Laboratorio, NuevaPractica.nombre)>0)
            {
                gotoxy(20,6);
                printf("La practica ya existe. Desea modificar su nombre? \"s\"o\"n\": ");
                fflush(stdin);
                gotoxy(90,6);
                scanf("%c",&modifica);

                if(modifica=='s'|| modifica=='S')
                {
                    ModificacionArchivoPracticas(Practicas_Laboratorio,NuevaPractica.nombre);
                    gotoxy(48,8);printf("MODIFICACION EXITOSA!");
                    gotoxy(35,9);printf("Desea seguir cargando prácticas? S/N\n");
                    fflush(stdin);
                    gotoxy(78,9);scanf("%c",&opcion);
                    BORRAR;
                }
            }
            else
            {
                marco_menu();
                gotoxy(52,2);
                printf("ALTA DE PRACTICA");
                gotoxy(15,6);
                printf("La practica ya existe pero esta dada de baja.Desea Activarla nuevamente? s/n \n");
                fflush(stdin);
                gotoxy(94,6);
                scanf("%c",&reactiva);

                if(reactiva=='s'|| reactiva=='S')
                {
                    reactivacion_Practica(Practicas_Laboratorio,NuevaPractica.nombre);
                }
            }
        }
    }
}

void bajaDePractica(char archivo[],char nombrePractica[],nodoArbol * arbol)
{
    marco_menu();
    gotoxy(52,2);
    printf("BAJA DE PRACTICA");

    practicas p;
    int encontrado=0;

    int id_prac=verificarSiExistePractica(archivo,nombrePractica);

    if(id_prac>0 && verificar_si_practica_es_utilizada(arbol,id_prac)==0)
    {
        FILE * arch=fopen(archivo,"r+b");

        if(arch)
        {
            while(encontrado == 0 && fread(&p,sizeof(practicas),1,arch)>0)
            {
                if(strcmpi(p.nombre,nombrePractica)==0)
                {
                    encontrado=1;///el while corta en la posicion del empleado buscado
                }
            }
            gotoxy(30,6);
            printf("Usted quiere dar de baja a la siguiente practica");
            gotoxy(40,8);
            printf("NOMBRE = %s [iD = %d]",p.nombre,p.nro_de_practica);
            char eliminar;
            gotoxy(25,15);
            printf("Presione \"s\" si es correcto sino presione cualquier tecla: ");
            fflush(stdin);
            gotoxy(85,15);
            scanf("%c",&eliminar);

            if(eliminar=='s'||eliminar=='S')
            {
                p.vigencia=1;///modifico

                fseek(arch,sizeof(practicas)*-1,SEEK_CUR);
                fwrite(&p,sizeof(practicas),1,arch);///grabo
                gotoxy(45,18);
                printf("Baja de Practica Exitosa");
                getch();
            }

            else
            {
                gotoxy(45,18);
                printf("Cambio NO realizado, vuelva a intentarlo");
                getch();
            }

            fclose(arch);
        }
    }
}

///Función para modificar el nombre de la práctica
void ModificacionArchivoPracticas(char nombreArchivo[],char nombrepractica[])
{
    marco_menu();
    gotoxy(52,2);
    printf("MODIFICACION DE PRACTICA");

    char opcion;

    if(verificarSiExistePractica(nombreArchivo,nombrepractica)== 1)
    {
        FILE * archi = fopen(nombreArchivo, "r+b");
        practicas Pract;

        if(archi)
        {
            Pract=buscaPoscionPractica(archi,nombrepractica);
            gotoxy(30,8);
            printf("Ingrese el nuevo nombre de la practica\n");
            fflush(stdin);
            gotoxy(46,8);
            gets(Pract.nombre);

            fseek(archi,sizeof(practicas)*-1,SEEK_CUR);
            fwrite(&Pract, sizeof(practicas), 1, archi);

            fclose(archi);
        }
        else
        {
            BORRAR;
            marco_borde_ancho();
            gotoxy(45,4);
            printf("Error al abrir el archivo\n");
            getch();
            BORRAR;
        }
    }
    else
    {
        marco_menu();
        gotoxy(52,2);
        printf("MODIFICACION DE PRACTICA");

        gotoxy(20,6);
        printf("No existe la práctica que acaba de ingresar. ¿Desea crearla? \"s\" o \"n\"" );
        gotoxy(85,6);
        opcion = getch();
        BORRAR;

        if(opcion == 'S' || opcion == 's')
        {
            AltaDePracticasNuevas(nombreArchivo);
        }
    }

}

practicas buscaPoscionPractica(FILE * arch,char nombrePractica[])
{
    practicas registro;
    fseek(arch,0,SEEK_SET);
    int flag=0;

    while(flag==0 && fread(&registro,sizeof(practicas),1,arch)>0)
    {
        if(registro.nombre==nombrePractica)
        {
            flag=1;
        }
    }

    return registro;
}

void reactivacion_Practica(char archivoPractica[], char nombrePractica[])
{
    FILE * arch=fopen(archivoPractica,"r+b");
    practicas p;
    int flag=0;

    if(arch)
    {
        while(flag==0 && fread(&p,sizeof(practicas),1,arch)>0)
        {
            if(strcmpi(p.nombre,nombrePractica)==0)
            {
                p.vigencia=0;
                fseek(arch,-1*sizeof(practicas),SEEK_CUR);
                fwrite(&p,sizeof(practicas),1,arch);
                gotoxy(45,8);
                printf("Reactivacion Exitosa!");
                flag=1;
            }
        }

        fclose(arch);
    }
}

void listado_practicas_ordenadas_alfabeticamente(char archivoP[])
{
    practicas p;
    gotoxy(43,2);
    printf("LISTADO DE PRACTICAS VIGENTES");

    practicas arreglo[30];///arreglo para pasar de manera ordenada.
    int validos=0;

    FILE * arch=fopen(archivoP,"rb");

    if(arch)
    {
        while(fread(&p,sizeof(practicas),1,arch)>0)
        {
            if(p.vigencia==0)
            {
                validos=cargar_arreglo_practicas_ordenado_x_apellido(&arreglo,p,validos);
            }
        }
        if(validos==0)
        {
            gotoxy(45,6);
            printf("NO EXISTEN EMPLEADOS EN NOMINA");
            getch();
        }
        else
        {
            mostrar_arreglo_practicas(arreglo,validos);
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

int cargar_arreglo_practicas_ordenado_x_apellido(practicas * arreglo, practicas p, int validos)
{
    int stop=0;
    int pos=validos;

    while(stop ==0 && pos>0)
    {
        if(strcmpi(arreglo[pos-1].nombre,p.nombre)>0)
        {
            arreglo[pos]=arreglo[pos-1];
            pos--;
        }
        else
        {
            arreglo[pos]=p;
            validos++;
            stop=1;
        }
    }
    if(stop==0)
    {
        arreglo[0]=p;
        validos++;
    }

    return validos;
}

void mostrar_arreglo_practicas(practicas arreglo[],int validos)
{
    BORRAR;
    int i=0;
    int x=28,y=4;///coordenadas para imprimir

    gotoxy(20,2);
    printf("=================LISTADO DE PRACTICAS VIGENTES==================");

    while(i<validos)
    {
        mostrar_una_practica(arreglo[i],x,y);
        y=y+3;
        i++;
    }
}

void mostrar_una_practica(practicas p, int x, int y)
{
    gotoxy(x,y++);
    printf("NOMBRE: %s [iD = %d]", p.nombre,p.nro_de_practica);
    gotoxy(x,y++);
    printf("=====================================================");
}

void busca_practica_y_muestra(char archivoPrac[], char nomPrac[])///pasa por parametro los caracteres que ingrese el usuario y muestra las practicas que comiencen de esa forma
{
    int caracteres=strlen(nomPrac);

    FILE * arch=fopen(archivoPrac,"rb");
    practicas p;
    int i=0;
    int distinto=0;

    if(arch)
    {
        while(fread(&p,sizeof(practicas),1,arch)>0)
        {
            while(distinto=0 && i<caracteres )
            {
                if(p.nombre[i]!=nomPrac[i])
                {
                    distinto=1;
                }
                i++;
            }
            if(distinto==0)
            {
                ///mostrar_una_practica(p,)
            }
            distinto=0;///reinicia para leer otro registro
        }
        fclose(arch);
    }
}

int verificar_si_practica_es_utilizada(nodoArbol * arbol, int idPractica)
{
    int utilizada=0;///inicio considerando que la practica no esta siendo utilizada

    if(utilizada==0 && arbol)
    {
        while(utilizada==0 && arbol->listaIngresos!=NULL)///si hay lista ingresos! recorro lista ingresos
        {
            if(arbol->listaIngresos->lab.vigencia==0)///si el ingreso no esta dado de baja recorro las practicas
            {
                while(utilizada==0 && arbol->listaIngresos->listaPracticas!=NULL)///si hay lista practicas la recorro
                {
                    if(arbol->listaIngresos->listaPracticas->datoPractica.nro_de_practica==idPractica)
                    {
                        utilizada=1;
                    }
                    arbol->listaIngresos->listaPracticas=arbol->listaIngresos->listaPracticas->siguiente;
                }
            }
            arbol->listaIngresos=arbol->listaIngresos->siguiente;
        }

        if(utilizada==0)///como no cambio el flag en el primer paciente recorro por derecha;
        {
            utilizada=verificar_si_practica_es_utilizada(arbol->der,idPractica);

            if(utilizada==0)///como no cambio el flag por derecha recorro por izquierda;
            {
                 utilizada=verificar_si_practica_es_utilizada(arbol->izq,idPractica);
            }
        }

    }


    return utilizada;
}
