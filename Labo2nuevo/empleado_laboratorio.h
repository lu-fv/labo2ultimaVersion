#ifndef EMPLEADO_LABORATORIO_H_INCLUDED
#define EMPLEADO_LABORATORIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "conio.h"
#include "pacientes.h"
#include "ingresos_Labo.h"
#include "practicas_ingreso.h"
#include "practicas_Labo.h"
#include "diseño.h"
#include "estructuras.h"

#define ARCHIVO_PACIENTES "pacientes.dat"
#define ARCHIVO_EMPLEADOS "archivo_empleados.dat"
#define ARCHIVO_PRACXINGRESO "practicaXingreso.dat"
#define ARCHIVO_INGRESOS "ingresos.dat"
#define Practicas_Laboratorio "practicas.dat"

#define BORRAR system("cls")
#define PAUSA system("pause")


empleados_laboratorio crearRegistroEmpleados();
void mostrar_un_empleado(empleados_laboratorio empleado, int x, int y);
void alta_empleado(char archivoEmpleado[]);
int verificar_archivo_empleados(char archivo[],int DNI);
int verificar_usuario_unico(char archivo[],char usuarioNuevo[]);
void baja_empleado(char archivoEmpleado[],int dni);
void modificacion_de_empleado(char archivoEmpleados[],int dni);
void listado_empleados_vigentes(char archivoEmpleados[]);
int cargar_arreglo_ordenado_x_apellido(empleados_laboratorio * arreglo, empleados_laboratorio empleado, int validos);
void mostrar_arreglo_empleados(empleados_laboratorio arreglo[],int validos);
void listado_empleados_eliminados(char archivoEmpleados[]);
int validacion_usuarioYclave(char archivoEmpleados[], char perfil[]);
void mostrar_archivo(char archivo[]);
void menu_modifica_campo_registro(FILE * archivo, empleados_laboratorio empleado);
void reactivacion_empleado(char archivoEmpleado[], int dni);

#endif // EMPLEADO_LABORATORIO_H_INCLUDED
