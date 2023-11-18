#ifndef PRACTICAS_INGRESO_H_INCLUDED
#define PRACTICAS_INGRESO_H_INCLUDED

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


void alta_de_UNA_practXingreso(int numIngreso);
pracXingreso crear_registro_practXingreso(int numIngreso, int * ok);
int verifica_existe_ingreso(int numIngreso);
void listado_pract_vigentes();
int busca_num_practica_vigente(char nombrepractica[]);
nodoListaPracticas * crearNodoPracticas(pracXingreso p);
nodoListaPracticas * agregarAlFinalListaPracticas(nodoListaPracticas * origen, nodoListaPracticas * nuevo);


#endif // PRACTICAS_INGRESO_H_INCLUDED
