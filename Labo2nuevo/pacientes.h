#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "conio.h"
#include "ingresos_Labo.h"
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


pacientes cargaPacientes(int dni);
void imprimirUnPaciente(pacientes p,int x,int y);
nodoArbol * inicArbol();
nodoArbol * crearNodoPacientes (pacientes p);
nodoArbol * insertarPacientes( nodoArbol * arbol, pacientes p);
int posicionPaciente(FILE* arc, int dni);
int buscarPaciente(nodoArbol * arbol, int dni);
void reactivaPaciente(int dni);
void altaPacientes();

void menu_modifica_campo_persona();
void modificarNombreYapellido(int dni);
void modificarDni(int dni);
void modificarEdad(int dni);
void modificarTel(int dni);
void modificarDireccion(int dni);

void borrarPaciente (nodoArbol * arbol,int dni);

nodoArbol * carga_arbol();
int valida_existencia_de_ingresos_x_paciente(int dni_paciente);
nodoArbol * busca_nodopaciente_en_arbol(nodoArbol * arbol, int dni);
nodoArbol * crear_nodo_arbol(pacientes p);
nodoArbol * carga_arbol_un_paciente(nodoArbol * arbol,nodoArbol * nuevo);
void mostrar_arbol(nodoArbol * arbol);///de prueba
void mostrar_un_paciente_nodo(nodoArbol * arbol);///de prueba
void listado_pacientes_vigentes(nodoArbol * arbolpac);
void listado_pacientes_eliminados(nodoArbol * arbolpac);

#endif // PACIENTES_H_INCLUDED
