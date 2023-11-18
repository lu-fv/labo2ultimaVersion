#ifndef INGRESOS_LABO_H_INCLUDED
#define INGRESOS_LABO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "conio.h"
#include "pacientes.h"
#include "practicas_ingreso.h"
#include "practicas_Labo.h"
#include "empleado_laboratorio.h"
#include "diseño.h"

#define ARCHIVO_PACIENTES "pacientes.dat"
#define ARCHIVO_EMPLEADOS "archivo_empleados.dat"
#define ARCHIVO_PRACXINGRESO "practicaXingreso.dat"
#define ARCHIVO_INGRESOS "ingresos.dat"
#define Practicas_Laboratorio "practicas.dat"

#define BORRAR system("cls")
#define PAUSA system("pause")


void fechaActual(char fecha[]);
int autoincrementalIngresos(char archivo[]);
laboratorios nuevoRegistroLaboratorio();
nodoListaIngresos * crearNodoIngreso(laboratorios nuevo);///deberia ser pracXingreso en lugar de nodolistapracticas
nodoListaIngresos * agregarAlFinalIngresos(nodoListaIngresos * lista, nodoListaIngresos * nuevo);///deberia ser pracXingreso en lugar de nodolistapracticas
void altaDeLaboratorio();
void bajDeLabXId(int id, char archivo[], nodoArbol * arbol);
void modificacionDeLaboratorio(char archivo[]);
void listadoDeLaboratoriosVigentes(nodoArbol * arbol);
void mostrarListaIngresos(nodoListaIngresos * lista);

#endif // INGRESOS_LABO_H_INCLUDED
