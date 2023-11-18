
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
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
#define ESC 27
//para pegar en el main o posterior


void fechaActual(char fecha[])
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(fecha,128,"%d/%m/%y",tlocal);
}

int autoincrementalIngresos(char archivo[])
{
    FILE * archi = fopen(archivo, "rb");

    laboratorios registro;
    int i=0;

    if(archi)
    {
        fseek(archi, sizeof(laboratorios)*-1,SEEK_END);
        while(fread(&registro, sizeof(laboratorios), 1, archi)>0)
        {
            i=registro.Nro_de_ingreso;
        }
        fclose(archi);
    }

    return i+1;
}

laboratorios nuevoRegistroLaboratorio()
{
    laboratorios nuevo;

    char fecha[50];
    char opc=0;
    ///le asigno la fecha de hoy al string "fecha", que se usará en la carga (automática, no la requerirá al usuario)
    fechaActual(fecha);

    nuevo.Nro_de_ingreso=autoincrementalIngresos(ARCHIVO_INGRESOS);

    ///marco_menu();
    ///gotoxy(45,2);printf("MENU ALTA LABORATORIOS");
    gotoxy(20,8);printf("Ingrese DNI del Paciente: ");
    gotoxy(20,9);printf("Nro de Ingreso: [%d]", nuevo.Nro_de_ingreso);///verificar string HACER FUNCION
    gotoxy(20,10);printf("Fecha de ingreso: [%s]",strcpy(nuevo.fecha_de_ingreso, fecha));
    gotoxy(20,11);printf("Fecha de retiro: [%s]", strcpy(nuevo.fecha_de_retiro,"a confirmar"));
    gotoxy(20,12);printf("Ingrese Matricula del Medico ordenante: ");

    fflush(stdin);
    gotoxy(48,8);scanf("%d",&nuevo.dni_paciente);
    fflush(stdin);
    gotoxy(60,12);scanf("%d", &nuevo.medico_matricula);

    nuevo.vigencia=0; ///vigente

    return nuevo;
}

nodoListaIngresos * crearNodoIngreso(laboratorios nuevo)
{
    nodoListaIngresos * lista = (nodoListaIngresos*) malloc(sizeof(nodoListaIngresos));

    lista->lab = nuevo;
    lista->siguiente=NULL;

    return lista;
}

nodoListaIngresos * agregarAlFinalIngresos(nodoListaIngresos * lista, nodoListaIngresos * nuevo)
{
    nodoListaIngresos * aux = lista;

    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        while(aux->siguiente!= NULL)
        {
            aux= aux->siguiente;
        }
        aux->siguiente= nuevo;

    }

    return lista;
}

void altaDeLaboratorio()
{
    marco_menu();
    gotoxy(48,2);printf("ALTA DE LABORATORIO");

    char opc='s';
    laboratorios registrolab;
    pracXingreso prac_labo;
    practicas p;

    nodoArbol * arbol=inicArbol();
    arbol=carga_arbol();

    registrolab = nuevoRegistroLaboratorio();
    nodoArbol * busca=busca_nodopaciente_en_arbol(arbol,registrolab.dni_paciente);

    if(busca!=NULL && busca->p.eliminado==0)
    /*si existe el paciente en el arbol y esta vigente procedo a grabar el registro
    de nuevo laboratorio en el archivo y lo cargo al arbol.*/
    {
        FILE * archi = fopen(ARCHIVO_INGRESOS, "ab");

        if(archi)
        {
            ///grabo archivo
            fwrite(&registrolab, sizeof(laboratorios), 1, archi);
            fclose(archi);
            ///cargo el arbol con el ingreso
            busca->listaIngresos=agregarAlFinalIngresos(busca->listaIngresos,crearNodoIngreso(registrolab));
            gotoxy(45,14);printf("Alta de Laboratorio exitoso!");
            getch();
        }

        ///sigo con la carga de practica o practicas
        BORRAR;
        marco_menu();
        gotoxy(48,2);printf("ALTA DE LABORATORIO");

       while(opc=='s'||opc=='S')
       {
            alta_de_UNA_practXingreso(registrolab.Nro_de_ingreso);

            printf("\nDesea seguir cargando practicas? Seleccione ESC para salir o cualquier tecla para continuar");
            fflush(stdin);
            scanf("%c",&opc);
       }
}
}

void bajDeLabXId(int id, char archivo[], nodoArbol * arbol)
{
    FILE *archi=fopen(archivo, "r+b");
    laboratorios lab;
    int bandera=0;
    if(archi)
    {
        while(bandera == 0 && fread(&lab, sizeof(laboratorios), 1, archi)>0)
        {
            ///QUE NO TENGA PRACTICAS

            if(id==lab.Nro_de_ingreso && lab.vigencia==0) ///si encuentra el id y siempre y cuando no se encuentre dado de baja
            {
                bandera=1; /// para cortar la busqueda si encuentra y no recorra todo el archivo
                fseek(archi, (-1)*sizeof(laboratorios), SEEK_CUR); ///retrocede 1 registro
                lab.vigencia=1;
                fwrite(&lab, sizeof(laboratorios), 1, archi);
                printf("\n el Laboratorio de ID: %i  fue eliminado.\n", id);
                PAUSA;
            }

        }

        ///CONSULTAR SI PODEMOS UTILIZAR LA FUNCION DE TRAER TODOS LOS DATOS DEL ARCHIVO AL ARBOL
        /*
        ///busca el laboratorio con ese id en el arbol
        nodoListaIngresos * aux= arbol->listaIngresos;


        ///ELIMINAMOS LAS PRACTICAS REALIZADAS POR ESE LABORATORIO EN CASCADA
        if(bandera == 1)
        {
             while(aux !=NULL)
            {
                if(aux->lab.Nro_de_ingreso == id)
                {
                    while(aux->listaPracticas != NULL)
                    {
                        aux->listaPracticas->datoPractica.vigencia=1;
                        aux->listaPracticas = aux->listaPracticas->siguiente;
                        ///ACA DEBERIA GRABAR EL CAMBIO EN EL ARCHIVO DE PRACTICAS X INGRESOS
                    }
                    aux= aux->siguiente;
                }
            }

        if(bandera==0)
        {
            printf("\n La ID: %i  no fue encontrada en el archivo o se encuentra dado de baja, consultar en listado respectivo.");

                printf("\n La ID: %i  no fue encontrada en el archivo o ya se encuentra dado de baja, consultar en listado respectivo.");

        }*/

        fclose(archi);

    }

}


void modificacionDeLaboratorio(char archivo[])
{
    FILE* archi = fopen(archivo,"r+b");
    laboratorios lab;
    int id;
    int bandera=0;
    int nuevo;
    int opc;
    char fecha[20];

    if(archi)
    {
        printf("\nIngrese el numero de ingreso del laboratorio que desea modificar:\n");
        fflush(stdin);
        scanf("%d",&id);

        while((bandera==0)&&(fread(&lab,sizeof(laboratorios),1,archi)>0)) ///CORTA BUSQUEDA CON EL FLAG
        {
            if(lab.Nro_de_ingreso==id && lab.vigencia==0)///MIENTRAS SE ENCUENTER DADO DE ALTA Y SI LO ENCUENTRA
            {
                bandera=1;
            }
        }

        if(bandera==1)///SE EJECUTA TODO EL MENU SI LO ENCUENTRA, SINO VA AL ELSE FINAL
        {
            fseek(archi,-1*sizeof(laboratorios),SEEK_CUR); ///SE POSICIONA AL INICIO DEL REGISTRO ENCONTRADO
            do
            {
                system("cls");
                printf("\n Elija la Opcion que Desea Modificar:\n");
                printf("\n1 - DNI del Paciente\n");
                printf("\n2 - Fecha de retiro de resultados");
                printf("\n3 - Matricula del Medico");
                printf("\n5 - Ir al Menu Anterior\n");
                fflush(stdin);
                scanf("%d",&opc);

                switch(opc)
                {
                case 1:
                    system("cls");
                    printf("\nIngrese DNI del paciente correcto:\n");
                    fflush(stdin);
                    scanf("%d",&nuevo);
                    lab.dni_paciente=nuevo;
                    break;
                case 2:
                    system("cls");
                    printf("\nIngrese nueva fecha de retiro de resultados:\n");
                    fflush(stdin);
                    scanf("%s",&fecha);
                    strcpy(lab.fecha_de_retiro, fecha);
                    break;
                case 3:
                    system("cls");
                    printf("\nIngrese la matricula correcta:\n");
                    fflush(stdin);
                    scanf("%d",&nuevo);
                    lab.medico_matricula=nuevo;
                    break;
                case 4:
                    system("cls");
                    ///ACA AGREGAR VOLVER AL MENU ANTERIOR;
                    break;
                default:
                    system("cls");
                    printf("\nUsted a seleccionado una opcion incorrecta.Reintente nuevamente.\n");
                    break;
                }

            }
            while(opc!=6);

            fwrite(&lab,sizeof(laboratorios),1,archi);

        }
        else
        {
            BORRAR;
            printf("\nEl Laboratorio se encuentra dado de Baja\n"); ///CUANDO LA.BAJA ==1 (ELIMINADO)
            PAUSA;
        }
    }
}

 void listadoDeLaboratoriosVigentes(nodoArbol * arbol)
{
    nodoArbol * aux = arbol;

    if(aux != NULL)
    {
        listadoDeLaboratoriosVigentes(aux->izq);

        /*if(aux->listaIngresos->lab.vigencia==0)
        {
            mostrarListaIngresos(aux->listaIngresos);
        }

        listadoDeLaboratoriosVigentes(aux->der);*/

    }
}

        /*FILE* archi = fopen(archivo,"rb");
        laboratorios lab;

        if(archi)
        {
            printf("\n.........................LISTADO DE LABORATORIOS VIGENTES.............................\n");
            while(fread(&lab,sizeof(laboratorios),1,archi)>0)
            {
                if(lab.vigencia == 0) ///MIENTRAS SE ENCUENTRE VIGENTE
                {

                    printf("\n          NUMERO DE INGRESO: %d\n", lab.Nro_de_ingreso);
                    printf("\n           FECHA DE INGRESO: %s\n", lab.fecha_de_ingreso);
                    printf("\n            FECHA DE RETIRO: %s\n", lab.fecha_de_retiro);
                    printf("\n           DNI DEL PACIENTE: %d\n", lab.dni_paciente);
                    printf("\n       MATRICULA DEL MEDICO: %d\n", lab.medico_matricula);

                    puts("\n.........................................................................................\n");
                }
            }
        fclose(archi);

    }
    else
    {
        printf("\nERROR DEL ARCHIVO\n");
    }
}



void listadoDeLaboratoriosVigentes(char archivo[])
{
    FILE* archi = fopen(archivo,"rb");
    laboratorios lab;

    if(archi)
    {
        printf("\n.........................LISTADO DE LABORATORIOS VIGENTES.............................\n");
        while(fread(&lab,sizeof(laboratorios),1,archi)>0)
        {
<<<<<<< HEAD
            if(lab.vigencia == 0) ///MIENTRAS SE ENCUENTRE VIGENTE
            {

                printf("\n          NUMERO DE INGRESO: %d\n", lab.Nro_de_ingreso);
                printf("\n           FECHA DE INGRESO: %s\n", lab.fecha_de_ingreso);
                printf("\n            FECHA DE RETIRO: %s\n", lab.fecha_de_retiro);
                printf("\n           DNI DEL PACIENTE: %d\n", lab.dni_paciente);
                printf("\n       MATRICULA DEL MEDICO: %d\n", lab.medico_matricula);

                puts("\n.........................................................................................\n");
            }
        }
            printf("\nERROR DEL ARCHIVO\n");
        }
        fclose(archi);
    }
    else
    {
        printf("\nERROR DEL ARCHIVO\n");
    }

}*/



void mostrarListaIngresos(nodoListaIngresos * lista)
{
    nodoListaIngresos * ingreso = lista;

    while(ingreso != NULL)
    {
        printf("\n          NUMERO DE INGRESO: %d\n", ingreso->lab.Nro_de_ingreso);
        printf("\n           FECHA DE INGRESO: %s\n", ingreso->lab.fecha_de_ingreso);
        printf("\n            FECHA DE RETIRO: %s\n", ingreso->lab.fecha_de_retiro);
        printf("\n           DNI DEL PACIENTE: %d\n", ingreso->lab.dni_paciente);
        printf("\n       MATRICULA DEL MEDICO: %d\n", ingreso->lab.medico_matricula);

        puts("\n.........................................................................................\n");

        ingreso=ingreso->siguiente;
    }

}

/*void listadoDeLaboratoriosEliminados(nodoArbol * arbol)
{
    nodoArbol * aux = arbol;

    if(aux != NULL)
    {
        /// los muestra en orden
        printf("\n.........................LISTADO DE INGRESO DE LABORATORIO VIGENTES.............................\n");

        listadoDeLaboratoriosEliminados(aux->izq);

        /*if(aux->listaIngresos->lab.vigencia==1)
        {
            mostrarListaiIngresos(aux->listaIngresos);
        }

        listadoDeLaboratoriosEliminados(aux->der);
    }
}




    FILE* archi = fopen(archivo,"rb");
    laboratorios lab;

    if(archi)
    {
        printf("\n.........................LISTADO DE LABORATORIOS ELIMINADOS.............................\n");
        while(fread(&lab,sizeof(laboratorios),1,archi)>0)
        {
            if(lab.vigencia == 1) ///MIENTRAS NO SE ENCUENTREN VIGENTE
            {

                printf("\n          NUMERO DE INGRESO: %d\n", lab.Nro_de_ingreso);
                printf("\n           FECHA DE INGRESO: %s\n", lab.fecha_de_ingreso);
                printf("\n            FECHA DE RETIRO: %s\n", lab.fecha_de_retiro);
                printf("\n           DNI DEL PACIENTE: %d\n", lab.dni_paciente);
                printf("\n       MATRICULA DEL MEDICO: %d\n", lab.medico_matricula);

                puts("\n.........................................................................................\n");
            }
        }

        fclose(archi);
    }
    else
    {
        printf("\nERROR DEL ARCHIVO\n");
    }

}


}*/
