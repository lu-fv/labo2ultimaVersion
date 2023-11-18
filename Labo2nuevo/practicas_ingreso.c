
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
#include "estructuras.h"

#define ARCHIVO_PACIENTES "pacientes.dat"
#define ARCHIVO_EMPLEADOS "archivo_empleados.dat"
#define ARCHIVO_PRACXINGRESO "practicaXingreso.dat"
#define ARCHIVO_INGRESOS "ingresos.dat"
#define Practicas_Laboratorio "practicas.dat"

#define BORRAR system("cls")
#define PAUSA system("pause")

void alta_de_UNA_practXingreso(int numIngreso)
{
    pracXingreso p;
    int ok=0;
    p=crear_registro_practXingreso(numIngreso,&ok);

    if(ok==1)
    {
        FILE * arch=fopen(ARCHIVO_PRACXINGRESO,"ab");
        nodoArbol * arbol=inicArbol();
        arbol=carga_arbol();

        if(arch)
        {
            fwrite(&p,sizeof(pracXingreso),1,arch);
            arbol->listaIngresos->listaPracticas=agregarAlFinalListaPracticas(arbol->listaIngresos->listaPracticas,crearNodoPracticas(p));
            fclose(arch);
            gotoxy(50,15);printf("Alta de practica exitosa!");
        }
    }
}

pracXingreso crear_registro_practXingreso(int numIngreso, int * ok)
{
    BORRAR;
    char nompractica[30];
    pracXingreso prac;
    int verifica_practica;
    ok=0;

    if(verifica_existe_ingreso(numIngreso)==1)
    {
        ///listado_pract_vigentes();

        gotoxy(20,5);printf("Ingrese el nombre de la practica que desea: ");
        fflush(stdin);
        gotoxy(65,5);gets(nompractica);

        verifica_practica=busca_num_practica_vigente(nompractica);

        if(verifica_practica>=0)///Si la practica esta todo bien termina de cargar los campos.
        {
            prac.nro_de_practica=verifica_practica;
            strcpy(prac.nombre,nompractica);
            prac.vigencia=0;
            strcpy(prac.resultado,"A CONFIRMAR");
        }
        ok=1;
    }

  return ;///si retorna cero es que el ingreso no existe por ende no carga el registro
}

int verifica_existe_ingreso(int numIngreso)///verifica si existe ingreso "Y" si esta vigente
{
    FILE * arch=fopen(ARCHIVO_INGRESOS,"rb");
    laboratorios lab;
    int flag=0;

    if(arch)
    {
        while(flag==0 && fread(&lab,sizeof(laboratorios),1,arch)>0)
        {
            if(lab.Nro_de_ingreso==numIngreso && lab.vigencia==0)
            {
                flag=1;
            }
        }
        fclose(arch);
    }
    if(flag==0)
    {
        printf("\nla practica ingresada no esta disponible");
    }

    return flag;
}

void listado_pract_vigentes()
{
    FILE * arch=fopen(Practicas_Laboratorio,"rb");
    practicas p;

    gotoxy(20,5);printf("....................LISTADO DE PRACTICAS VIGENTES..........................");
    int x=35;
    int y=7;

    if(arch)
    {
        while(fread(&p,sizeof(practicas),1,arch)>0)
        {
            if(p.vigencia==0)
            {
                gotoxy(x,y);printf("[%s]",p.nombre);
                gotoxy(x,y++);printf("======================================");
                y=y+2;
            }
        }
        fclose(arch);
    }
}

int busca_num_practica_vigente(char nombrepractica[])
{
    ///verifica si existe practica "Y" si esta vigente retornando el numero de practica.
    ///Si no cumple estas condiciones retorna -1 (si la practica no existe o no esta vigente
    FILE * arch=fopen(Practicas_Laboratorio,"rb");
    practicas p;
    int flag=-1;

    if(arch)
    {
        while(flag==-1 && fread(&p,sizeof(practicas),1,arch)>0)
        {
            if(strcmpi(p.nombre,nombrepractica) && p.vigencia==0)
            {
                flag=p.nro_de_practica;
            }
        }
        fclose(arch);
    }

    if(flag==-1)
    {
        printf("\nLa practica ingresada no se encuentra vigente");
    }

    return flag;
}

nodoListaPracticas * crearNodoPracticas(pracXingreso p)
{
    nodoListaPracticas * nuevo=(nodoListaPracticas *)malloc(sizeof(nodoListaPracticas));

    nuevo->datoPractica=p;
    nuevo->siguiente=NULL;

    return nuevo;
}

nodoListaPracticas * agregarAlFinalListaPracticas(nodoListaPracticas * origen, nodoListaPracticas * nuevo)
{
    nodoListaPracticas * aux=origen;

    if(aux)
    {
        while(aux->siguiente!=NULL)
        {
            aux=aux->siguiente;
        }
        aux->siguiente=nuevo;
    }
    else
    {
        origen=nuevo;
    }

    return origen;
}




