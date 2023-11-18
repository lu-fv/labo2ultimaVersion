#ifndef PRACTICAS_LABO_H_INCLUDED
#define PRACTICAS_LABO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "conio.h"
#include "pacientes.h"
#include "ingresos_Labo.h"
#include "practicas_ingreso.h"
#include "empleado_laboratorio.h"
#include "diseño.h"

#define ARCHIVO_PACIENTES "pacientes.dat"
#define ARCHIVO_EMPLEADOS "archivo_empleados.dat"
#define ARCHIVO_PRACXINGRESO "practicaXingreso.dat"
#define ARCHIVO_INGRESOS "ingresos.dat"
#define Practicas_Laboratorio "practicas.dat"

#define BORRAR system("cls")
#define PAUSA system("pause")



practicas CrearPracticaLaboratorio ();
int autoincrementalPracticas(char archivo[]);
int verificarSiExistePractica(char archivo[], char PracticaNueva[]);
void AltaDePracticasNuevas();
///void bajaDePractica(char archivo[],char nombrePractica[],nodoArbol * arbol);
void ModificacionArchivoPracticas(char nombreArchivo[],char nombrePractica[]);
practicas buscaPoscionPractica(FILE * arch,char nombrePractica[]);
void reactivacion_Practica(char archivoPractica[], char nombrePractica[]);
void listado_practicas_ordenadas_alfabeticamente(char archivoP[]);
int cargar_arreglo_practicas_ordenado_x_apellido(practicas * arreglo, practicas p, int validos);
void mostrar_arreglo_practicas(practicas arreglo[],int validos);
void mostrar_una_practica(practicas p, int x, int y);
void busca_practica_y_muestra(char archivoPrac[], char nomPrac[]);
///int verificar_si_practica_es_utilizada(nodoArbol * arbol, int idPractica);

#endif // PRACTICAS_LABO_H_INCLUDED
