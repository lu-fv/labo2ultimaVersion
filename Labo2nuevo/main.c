#include <stdio.h>
#include <stdlib.h>
#include "diseño.h"
#define BORRAR system("cls")
#define PAUSA system("pause")


int main()
{
    nodoArbol * arbol=inicArbol();
    arbol=carga_arbol();
    mostrar_arbol(arbol);
    PAUSA;
    menu();


    ///carga el archivo empleados
    /*char rta='s';

    while(rta=='s')
    {
        alta_empleado(ARCHIVO_EMPLEADOS);
        printf("\nDesea ingresar un nuevo empleado? s/n : ");
        fflush(stdin);
        scanf("%c",&rta);
        BORRAR;
    }*/

    return 0;
}
