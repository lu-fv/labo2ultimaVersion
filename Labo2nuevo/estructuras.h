#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

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
#include "diseño.h"

#define ARCHIVO_PACIENTES "pacientes.dat"
#define ARCHIVO_EMPLEADOS "archivo_empleados.dat"
#define ARCHIVO_PRACXINGRESO "practicaXingreso.dat"
#define ARCHIVO_INGRESOS "ingresos.dat"
#define Practicas_Laboratorio "practicas.dat"

#define BORRAR system("cls")
#define PAUSA system("pause")

typedef struct
{
    int dni;
    char ape_nombre [40];
    char usuario [20];
    char clave [20];
    char perfil [20];
    int eliminado;///0 por defecto
} empleados_laboratorio;

typedef struct
{
    char nomb_apell[40];
    int edad;
    int dni;
    char telefono[15];
    char direccion[30];
    int eliminado;///0 vigente,1 eliminado
} pacientes;

typedef struct
{
    int Nro_de_ingreso;
    char fecha_de_ingreso[10]; //por defecto la actual
    char fecha_de_retiro [10];
    int dni_paciente;
    int medico_matricula;
    int vigencia;///0 vigente, 1 NO vigente
}laboratorios;

typedef struct
{
    int nro_de_ingreso;
    int nro_de_practica;
    char nombre[20];
    int vigencia;///0 vigente,1 NO vigente
    char resultado [40];
}pracXingreso;

typedef struct
{
    int nro_de_practica;
    char nombre[30];
    int vigencia;///0 vigente,1 NO vigente
} practicas;

typedef struct nodoArbol
{
    pacientes p;
    struct nodoListaIngresos * listaIngresos;
    struct nodoArbol * izq;
    struct nodoArbol * der;
}nodoArbol;

typedef struct nodoListaIngresos
{
    laboratorios lab;
    struct nodoListaPracticas * listaPracticas;
    struct nodoListaIngresos * siguiente;
}nodoListaIngresos;

typedef struct nodoListaPracticas
{
    pracXingreso datoPractica;
    struct nodoListaPracticas * siguiente;
}nodoListaPracticas;




#endif // ESTRUCTURAS_H_INCLUDED
