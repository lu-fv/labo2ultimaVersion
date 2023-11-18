#ifndef DISEÒO_H_INCLUDED
#define DISEÒO_H_INCLUDED

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


void gotoxy(int x,int y);
void marco_borde_ancho();
void marco_menu();
void marco_contrasenia();

void menu();
void acceso_administrador();
void acceso_empleado_administrativo();
void acceso_profesional();

void menu_administrador();
void menu_administrador_empleados();
void opc_1_altaempleados();
void opc_2_bajaempleados();
void opc_3_modifempleado();

void menu_administrador_pacientes();
void menu_administrador_practicas();
void menu_administrador_laboratorios();
void menu_administrador_resultados();

void menu_gestion_administrativa();
void menu_gestion_administrativa_pacientes();
void menu_gestion_administrativa_practicas();
void menu_gestion_administrativa_laboratorios();

void menu_bioquimico();
void menu_contrasenia();



///void marco_plantilla();
///void marco_factura();
///void plantilla_laboratorios_x_paciente();
///void factura();


#endif // DISEÒO_H_INCLUDED
