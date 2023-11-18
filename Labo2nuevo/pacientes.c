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


void imprimirUnPaciente( pacientes p, int x,int y)
{
    gotoxy(x,y);printf("     >>>>> DATOS PACIENTE: <<<<<< ");
    y++;
    gotoxy(x,y);printf("EDAD: [%d]",p.edad);
    y++;
    gotoxy(x,y);printf("NOMBRE Y APELLIDO: %s", p.nomb_apell);
    y++;
    gotoxy(x,y);printf("\DIRECCION: %s", p.direccion);
    y++;
    gotoxy(x,y);printf("DNI: %d", p.dni);
    y++;
    gotoxy(x,y);printf("Nro.CEL: %s\n\n", p.telefono);
    y++;

    if(p.eliminado==0)
    {
        gotoxy(x,y);printf(" >>>>EL PACIENTE ESTA ACTIVO<<<<");
    }
    else
    {
        gotoxy(x,y);printf(" >>>>EL PACIENTE ESTA INACTIVO<<<<");
    }

}

nodoArbol * inicArbol()
{
    return NULL;
}

nodoArbol * crearNodoPacientes (pacientes p)
{
    nodoArbol* nuevoNodo = (nodoArbol*)malloc (sizeof (nodoArbol));

    nuevoNodo->p = p;
    nuevoNodo->der =NULL;
    nuevoNodo ->izq = NULL;
    nuevoNodo->listaIngresos = NULL;

    return nuevoNodo;

}

nodoArbol * insertarPacientes (nodoArbol * miArbol, pacientes p)
{

    if(miArbol==NULL)
    {
        miArbol = crearNodoPacientes(p);
    }
    else
    {
        if ( p.dni > miArbol->p.dni)
        {
            miArbol->der = insertarPacientes(miArbol->der, p);
        }
        else
        {

            miArbol->izq = insertarPacientes(miArbol->izq, p);
        }
    }

    return miArbol;
}

int posicionPaciente (FILE * arc, int dni)
{
    int flag =0;
    pacientes p;

    while((flag ==0)&& fread(&p, sizeof(pacientes), 1, arc)>0)
    {
        if(p.dni==dni) //si encuentra dni
        {
            if(p.eliminado==0) // esta activo
            {
                flag=1;
            }
            else // esta pero dado de baja
            {
                flag=-1;
            }
        }

    }
    return flag;
}

void altaPacientes()
{
    pacientes p;
    nodoArbol * arbol=inicArbol();
    arbol=carga_arbol();

    int dni;
    char reactiva;

    FILE * arc = fopen (ARCHIVO_PACIENTES, "ab");

    if (arc)
    {
        marco_menu();
        gotoxy(45,2);printf("ALTA DE PACIENTES");
        gotoxy(40,6);printf("DNI Paciente nuevo: ");
        fflush (stdin);
        gotoxy(60,6);scanf ("%d",&dni);

        if (buscarPaciente(arbol,dni)==0)
        {
            p= cargaPacientes(dni);
            fwrite(&p,sizeof(pacientes),1,arc);///graba en el archivo
            arbol=insertarPacientes(arbol,p);
            gotoxy(50,14);printf("Alta Exitosa!");
        }
        else
        {
            if(buscarPaciente(arbol,dni)==1)
            {
                gotoxy(32,7);printf("El paciente ya se encuentra en la base de datos");
            }
            else
            {
                gotoxy(30,7);printf("DESEA REACTIVAR EL PACIENTE? S/N : ");
                fflush(stdin);
                gotoxy(63,7);scanf("%c",&reactiva);

                if(reactiva=='s' || reactiva=='S')
                {
                    reactivaPaciente(dni);
                }
            }
        }
        fclose (arc);
    }
}
int buscarPaciente (nodoArbol * arbol, int dni)
{
    int flag=0;

    if(arbol)
    {
        if(arbol->p.dni==dni) //si encuentra dni FALTABA PONER ARBOL FLECHITA
        {
            if(arbol->p.eliminado==0) // esta activo
            {
                flag=1;
            }
            // esta pero dado de baja
            else
            {
                flag=-1;
            }
        }
        else
        {
            if (arbol->p.dni > dni)
            {
                flag =buscarPaciente(arbol->izq, dni);
            }
            else
            {
                flag = buscarPaciente(arbol->der, dni);
            }
        }
    }
    return flag;
}
pacientes cargaPacientes(int dni)
{
    pacientes p;

    gotoxy(36,7);printf(">>>>> INGRESO NUEVO PACIENTE <<<<<<");
    p.dni=dni;
    gotoxy(40,9);printf ("NOMBRE Y APELLIDO: ");
    gotoxy(40,10);printf ("DIRECCION: ");
    gotoxy(40,11);printf ("EDAD: ");
    gotoxy(40,12);printf ("Nro. CELULAR: ");

    fflush (stdin);
    gotoxy(60,9);gets(p.nomb_apell);

    fflush (stdin);
    gotoxy(51,10);gets(p.direccion);

    fflush (stdin);
    gotoxy(47,11);scanf("%d", &p.edad);

    fflush (stdin);
    gotoxy(53,12);gets(p.telefono);

    p.eliminado =0;

    return p;
}
void reactivaPaciente (int dni)
{
    FILE * arch=fopen(ARCHIVO_PACIENTES,"r+b");
    pacientes p;
    int flag=0;

    if(arch)
    {
        while(flag==0 && fread(&p,sizeof(pacientes),1,arch)>0)
        {
            if(p.dni==dni)
            {
                p.eliminado =0;
                fseek (arch, sizeof (pacientes)*-1, SEEK_CUR);
                fwrite(&p, sizeof (pacientes), 1, arch);
                gotoxy(45,8);printf("El paciente se reactivo correctamente");
                flag=1;
            }
        }
        fclose(arch);
    }
}


void menu_modifica_campo_persona()
{
    menu:
    BORRAR;
    system("COLOR E");
    marco_menu();
    int opc,dni;
    char rta;


    gotoxy(48,2);printf("MODIFICA PACIENTE");
    gotoxy(35,7);printf("Seleccione el campo que desea modificar");

    gotoxy(43,9);printf("1) NOMBRE Y APELLIDO");
    gotoxy(43,10);printf("2) DNI");
    gotoxy(43,11);printf("3) EDAD");
    gotoxy(43,12);printf("4) TELEFONO");
    gotoxy(43,13);printf("5) DIRECCION");
    gotoxy(43,14);printf("6) SALIR...");
    gotoxy(45,15);printf("OPCION SELECCIONADA...");
    gotoxy(70,15);scanf("%d",&opc);

    do
    {
        switch(opc)
        {
        case 1:
            BORRAR;
            marco_menu();
            gotoxy(40,2);printf("MODIFICA NOMBRE Y APELLIDO");
            gotoxy(30,5);printf("Ingrese el DNI del paciente que desea modificar: ");
            fflush(stdin);
            gotoxy(80,5);scanf("%d",&dni);
            modificarNombreYapellido(dni);
            getch();
            goto menu;

        case 2:
            BORRAR;
            marco_menu();
            gotoxy(50,2);printf("MODIFICA DNI");
            gotoxy(30,5);printf("Ingrese el DNI del paciente que desea modificar: ");
            fflush(stdin);
            gotoxy(80,5);scanf("%d",&dni);
            modificarDni(dni);
            goto menu;

        case 3:
            BORRAR;
            marco_menu();
            gotoxy(48,2);printf("MODIFICA EDAD");
            gotoxy(30,5);printf("Ingrese el DNI del paciente que desea modificar: ");
            fflush(stdin);
            gotoxy(80,5);scanf("%d",&dni);
            modificarEdad(dni);
            goto menu;

        case 4:
            BORRAR;
            marco_menu();
            gotoxy(45,2);printf("MODIFICA TELEFONO");
            gotoxy(30,5);printf("Ingrese el DNI del paciente que desea modificar: ");
            fflush(stdin);
            gotoxy(80,5);scanf("%d",&dni);
            modificarTel(dni);
            goto menu;

        case 5:
            BORRAR;
            marco_menu();
            gotoxy(45,2);printf("MODIFICA DOMICILIO");
            gotoxy(30,5);printf("Ingrese el DNI del paciente que desea modificar: ");
            fflush(stdin);
            gotoxy(80,5);scanf("%d",&dni);
            modificarDireccion(dni);
            goto menu;

        case 6:
            BORRAR;
            break;
        }
    }
    while(opc!=6);
}

void modificarNombreYapellido(int dni)
{
    nodoArbol * arbol=inicArbol();
    arbol=carga_arbol();
    int existe=buscarPaciente(arbol,dni);
    int flag=0;
    char rta;

    if(existe==1)
    {
        pacientes p;
        FILE * arch=fopen(ARCHIVO_PACIENTES,"r+b");

        if(arch)
        {
            while(flag==0 && fread(&p,sizeof(pacientes),1,arch)>0)
            {
                if(p.dni==dni)
                {
                    flag=1;
                    fseek(arch,-1*sizeof(pacientes),SEEK_CUR);///encuentra paciente y se posiciona para modificar
                    gotoxy(38,6);printf("Ingrese el nuevo Apellido y Nombre : ");
                    fflush(stdin);
                    gets(p.nomb_apell);

                    int x=45;
                    int y=8;
                    imprimirUnPaciente(p,x,y);
                    gotoxy(40,16);printf("Los datos son correctos? s/n : ");
                    fflush(stdin);
                    gotoxy(70,16);scanf("%c",&rta);
                    if(rta=='s'|| rta=='S')
                    {
                        fwrite(&p,sizeof(pacientes),1,arch);
                        gotoxy(45,18);printf("MODIFICACION EXITOSA");
                        getch();
                    }
                }
            }
            fclose(arch);
        }
    }
    else
    {
        gotoxy(30,6);printf("El paciente que desea modificar no existe en la base de datos");
        getch();
    }
}
void modificarDni (int dni)
{
    nodoArbol * arbol=inicArbol();
    arbol=carga_arbol();
    int existe=buscarPaciente(arbol,dni);
    int flag;
    char rta;

    if(existe==1)
    {
        pacientes p;
        FILE * arch=fopen(ARCHIVO_PACIENTES,"r+b");

        if(arch)
        {
            while(flag==0 && fread(&p,sizeof(pacientes),1,arch)>0)
            {
                if(p.dni==dni)
                {
                    flag=1;
                    fseek(arch,-1*sizeof(pacientes),SEEK_CUR);///encuentra paciente y se posiciona para modificar
                    gotoxy(38,6);printf("Ingrese el nuevo DNI : ");
                    fflush(stdin);
                    scanf("%d",&p.dni);
                    int x=45;
                    int y=8;
                    imprimirUnPaciente(p,x,y);
                    gotoxy(70,16);printf("Los datos son correctos? s/n : ");
                    fflush(stdin);
                    scanf("%c",&rta);
                    if(rta=='s'|| rta=='S')
                    {
                        fwrite(&p,sizeof(pacientes),1,arch);
                        gotoxy(45,18);printf("MODIFICACION EXITOSA");

                        getch();
                    }
                }
            }
            fclose(arch);
        }
    }
    else
    {
         gotoxy(30,6);printf("El paciente que desea modificar no existe en la base de datos");
        getch();
    }

}
void modificarEdad (int dni)
{
    nodoArbol * arbol=inicArbol();
    arbol=carga_arbol();
    int existe=buscarPaciente(arbol,dni);
    int flag=0;
    char rta;

    if(existe==1)
    {
        pacientes p;
        FILE * arch=fopen(ARCHIVO_PACIENTES,"r+b");

        if(arch)
        {
            while(flag==0 && fread(&p,sizeof(pacientes),1,arch)>0)
            {
                if(p.dni==dni)
                {
                    flag=1;
                    fseek(arch,-1*sizeof(pacientes),SEEK_CUR);///encuentra paciente y se posiciona para modificar
                    gotoxy(38,6);printf("Ingrese la nueva EDAD : ");
                    fflush(stdin);
                    scanf("%d",&p.edad);
                    int x=45, y=8;
                    imprimirUnPaciente(p,x,y);
                    gotoxy(40,16);printf("Los datos son correctos? s/n : ");
                    fflush(stdin);
                    gotoxy(70,16);scanf("%c",&rta);
                    if(rta=='s'|| rta=='S')
                    {
                        fwrite(&p,sizeof(pacientes),1,arch);
                        gotoxy(45,18);printf("MODIFICACION EXITOSA");

                        getch();
                    }
                }
            }
            fclose(arch);
        }
    }
    else
    {
         gotoxy(30,6);printf("El paciente que desea modificar no existe en la base de datos");
        getch();
    }
}
void modificarTel (int dni)
{
    nodoArbol * arbol=inicArbol();
    arbol=carga_arbol();
    int existe=buscarPaciente(arbol,dni);
    int flag=0;
    char rta;

    if(existe==1)
    {
        pacientes p;
        FILE * arch=fopen(ARCHIVO_PACIENTES,"r+b");

        if(arch)
        {
            while(flag==0 && fread(&p,sizeof(pacientes),1,arch)>0)
            {
                if(p.dni==dni)
                {
                    flag=1;
                    fseek(arch,-1*sizeof(pacientes),SEEK_CUR);///encuentra paciente y se posiciona para modificar
                    gotoxy(38,6);printf("Ingrese el nuevo TELEFONO: ");
                    fflush(stdin);
                    gets(p.telefono);
                    int x=45;
                    int y=8;
                    imprimirUnPaciente(p,x,y);
                    gotoxy(40,16);printf("Los datos son correctos? s/n : ");
                    fflush(stdin);
                    gotoxy(70,16);scanf("%c",&rta);
                    if(rta=='s'|| rta=='S')
                    {
                        fwrite(&p,sizeof(pacientes),1,arch);
                        gotoxy(45,18);printf("MODIFICACION EXITOSA");

                        getch();
                    }
                }
            }
            fclose(arch);
        }
    }
    else
    {
         gotoxy(30,6);printf("El paciente que desea modificar no existe en la base de datos");
        getch();
    }
}
void modificarDireccion (int dni)
{
    nodoArbol * arbol=inicArbol();
    arbol=carga_arbol();
    int existe=buscarPaciente(arbol,dni);
    int flag=0;
    char rta;

    if(existe==1)
    {
        pacientes p;
        FILE * arch=fopen(ARCHIVO_PACIENTES,"r+b");

        if(arch)
        {
            while(flag==0 && fread(&p,sizeof(pacientes),1,arch)>0)
            {
                if(p.dni==dni)
                {
                    flag=1;
                    fseek(arch,-1*sizeof(pacientes),SEEK_CUR);///encuentra paciente y se posiciona para modificar
                    gotoxy(38,6);printf("Ingrese la nueva DIRECCION: ");
                    fflush(stdin);
                    gets(p.direccion);
                    int x=45;
                    int y=8;
                    imprimirUnPaciente(p,x,y);
                    gotoxy(40,16);printf("Los datos son correctos? s/n : ");
                    fflush(stdin);
                    gotoxy(70,16);scanf("%c",&rta);
                    if(rta=='s'|| rta=='S')
                    {
                        fwrite(&p,sizeof(pacientes),1,arch);
                        gotoxy(45,18);printf("MODIFICACION EXITOSA");

                        getch();
                    }
                }
            }
            fclose(arch);
        }
    }
    else
    {
         gotoxy(30,6);printf("El paciente que desea modificar no existe en la base de datos");
        getch();
    }
}

void borrarPaciente (nodoArbol * arbol, int dni)
{
    nodoArbol * buscado =busca_nodopaciente_en_arbol(arbol,dni);

    pacientes p;
    int flag=0;

    if (buscado== NULL)
    {
        printf ("\n\t No se encuentra el dni en el archivo \n");
        getch();
        BORRAR;
    }
    else
    {
        if (buscado->p.eliminado==1)
        {
            printf ("\n El paciente ya se encuentra dado de baja\n");
            getch();
        }
        else
        {
            if (buscado->listaIngresos!=NULL)
            {
                while (flag ==0 && buscado->listaIngresos!=NULL)
                {
                    if ( buscado->listaIngresos->lab.vigencia==0)
                    {
                        printf ("\n El paciente no se puede eliminar, posee ingresos activos\n");
                        flag =1;
                        getch();

                    }
                    buscado->listaIngresos= buscado->listaIngresos->siguiente;
                }

                if (flag ==0)
                {

                    FILE *arc=fopen(ARCHIVO_PACIENTES,"r+b");
                    if (arc)
                    {
                        while (fread(&p,sizeof (pacientes),1, arc)>0)
                        {
                            if (p.dni == dni)
                            {
                                p.eliminado = 1;
                                fseek(arc,-1*sizeof(pacientes),SEEK_CUR);
                                fwrite(&p, sizeof(pacientes),1,arc);
                                int x=45;
                                int y=8;
                                imprimirUnPaciente(p,x,y);
                                puts("\n\t ------------------------------------ \n");
                                BORRAR;
                                printf ("\n el paciente ha sido eliminado");
                                getch();

                            }
                        }
                        fclose (arc);
                    }

                }

            }
            else
            {
                FILE *arc=fopen(ARCHIVO_PACIENTES,"r+b");

                int encontrado=0;

                if (arc)
                {
                    while (encontrado==0 && fread(&p,sizeof (pacientes),1, arc)>0)
                    {
                        if (p.dni == dni)
                        {
                            p.eliminado = 1;
                            fseek(arc,-1*sizeof(pacientes),SEEK_CUR);
                            fwrite(&p, sizeof(pacientes),1,arc);
                            int x=45;
                            int y=8;
                            imprimirUnPaciente(p,x,y);
                            puts("\n\t ------------------------------------ \n");
                            BORRAR;
                            printf ("\n el paciente ha sido eliminado");
                            encontrado=1;
                        }
                    }
                    fclose (arc);
                }

            }
        }
    }
}

void listado_pacientes_vigentes(nodoArbol * arbolpac)
{
    if(arbolpac)
    {
        listado_pacientes_vigentes(arbolpac->izq);
        if(arbolpac->p.eliminado==0)
        {
            mostrar_un_paciente_nodo(arbolpac);
        }
        listado_pacientes_vigentes(arbolpac->der);
    }

}

void listado_pacientes_eliminados(nodoArbol * arbolpac)
{
    if(arbolpac)
    {
        listado_pacientes_eliminados(arbolpac->izq);
        if(arbolpac->p.eliminado==1)
        {
            mostrar_un_paciente_nodo(arbolpac);
        }
        listado_pacientes_eliminados(arbolpac->der);
    }

}
///carga arbol de la base de datos de los 3 archivos (empleado,ingresos_lab y practicasXingreso)

nodoArbol * carga_arbol()
{
    nodoArbol * arbol=inicArbol();

    FILE * pac=fopen(ARCHIVO_PACIENTES,"rb");
    pacientes pacientito;
    FILE * ing=fopen(ARCHIVO_INGRESOS,"rb");
    laboratorios ingreso;
    FILE * prac=fopen(ARCHIVO_PRACXINGRESO,"rb");
    pracXingreso practica;

    if(pac)
    {
        if(ing)
        {
            if(prac)
            {
                ///carga los pacientes al arbol
                while(fread(&pacientito,sizeof(pacientes),1,pac)>0)
                {
                    ///cargo paciente en el arbol
                    arbol=insertarPacientes(arbol,pacientito);

             ///verifico que el paciente tenga ingresos y si tiene procedo a cargar la lista de ingresos del nodo arbol paciente

                    if(valida_existencia_de_ingresos_x_paciente(pacientito.dni)==1)
                    {
                        nodoArbol * arbolpaciente=busca_nodopaciente_en_arbol(arbol,pacientito.dni);

                        while(fread(&ingreso,sizeof(laboratorios),1,ing)>0)
                        {
                            ///cargo el ingreso de acuerdo al paciente
                            if(ingreso.dni_paciente==pacientito.dni)
                            {
                                arbolpaciente->listaIngresos=agregarAlFinalIngresos(arbolpaciente->listaIngresos,crearNodoIngreso(ingreso));
                            }
                              ///cargo las practicas del ingreso
                             while(fread(&practica,sizeof(pracXingreso),1,prac)>0)
                            {
                                if(practica.nro_de_ingreso == ingreso.Nro_de_ingreso)
                                {
                                   arbolpaciente->listaIngresos->listaPracticas=agregarAlFinalListaPracticas(arbolpaciente->listaIngresos->listaPracticas,crearNodoPracticas(practica));
                                }
                            }
                        }

                    }
                    fseek(prac,0,SEEK_SET);///reinicio el cursor del archivo practicas
                    fseek(ing,0,SEEK_SET);///reinicio el cursir del archivo ingresos
                }
                fclose(prac);
            }
            fclose(ing);
        }
        fclose(pac);
    }
    return arbol;
}

int valida_existencia_de_ingresos_x_paciente(int dni_paciente)
{
    FILE * arch=fopen(ARCHIVO_INGRESOS,"rb");
    laboratorios lab;
    int existeIngreso=0;

    if(arch)
    {
        while(existeIngreso==0 && fread(&lab,sizeof(laboratorios),1,arch)>0)
        {
            if(lab.dni_paciente==dni_paciente)
            {
                if(lab.vigencia==0)
                {
                    existeIngreso=1;
                }
                else
                {
                    existeIngreso=-1;
                }
            }
        }
        fclose(arch);
    }

return existeIngreso;
}

nodoArbol * busca_nodopaciente_en_arbol(nodoArbol * arbol, int dni)
{
    nodoArbol * pacientebuscado=inicArbol();

    if(arbol->p.dni==dni)
    {
        pacientebuscado=arbol;
    }
    else
    {
        if(dni < arbol->p.dni)
        {
            pacientebuscado=busca_nodopaciente_en_arbol(arbol->izq,dni);
        }
        else
        {
            pacientebuscado=busca_nodopaciente_en_arbol(arbol->der,dni);
        }
    }
    return pacientebuscado;
}

nodoArbol * crear_nodo_arbol(pacientes p)
{
    nodoArbol * nuevo=(nodoArbol*)malloc(sizeof(nodoArbol));

    nuevo->p=p;
    nuevo->izq=NULL;
    nuevo->der=NULL;

    return nuevo;
}

nodoArbol * carga_arbol_un_paciente(nodoArbol * arbol,nodoArbol * nuevo)
{
    if(arbol==NULL)
    {
        arbol=nuevo;
    }
    else
    {
        if(nuevo->p.dni > arbol->p.dni)
        {
            arbol->der=carga_arbol_un_paciente(arbol->der,nuevo);
        }
        else
        {
            arbol->izq=carga_arbol_un_paciente(arbol->izq,nuevo);
        }
    }
    return arbol;
}

void mostrar_arbol(nodoArbol * arbol)
{
    if(arbol)
    {
        mostrar_arbol(arbol->izq);
        printf("\nDNI = [%d]",arbol->p.dni);
        printf("\nNOMBRE = %s",arbol->p.nomb_apell);
        printf("\neliminado = %d",arbol->p.eliminado);
        printf("\n======================================\n");
        mostrar_arbol(arbol->der);
    }
}

void mostrar_un_paciente_nodo(nodoArbol * arbol)
{
    printf("\n\t\t\t\t             DNI = [%d]",arbol->p.dni);
    printf("\n\t\t\t\t          NOMBRE = %s",arbol->p.nomb_apell);
    printf("\n\t\t\t\t            EDAD = %d",arbol->p.edad);
    printf("\n\t\t\t\t        DOMICILIO = %s",arbol->p.direccion);
    printf("\n\t\t\t\t         TELEFONO = %s",arbol->p.telefono);
    printf("\n\t\t\t\t==============================================\n");
}







