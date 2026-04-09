#include "conexiones.h"
#include <string.h>
#include <stdio.h>

Conexion conexion_crear(int id, const char *nombre, int origen, int destino, int activa, int id_obj, int id_puz) {
    Conexion nueva_conexion;
    nueva_conexion.id = id;
    nueva_conexion.id_sala_origen = origen;
    nueva_conexion.id_sala_destino = destino;
    nueva_conexion.activa = activa;
    nueva_conexion.id_objeto_necesario = id_obj;
    nueva_conexion.id_puzzle_necesario = id_puz;
    
    strncpy(nueva_conexion.nombre, nombre, MAX_NOMBRE_CONEXION - 1);
    nueva_conexion.nombre[MAX_NOMBRE_CONEXION - 1] = '\0';
    
    return nueva_conexion; 
}

int conexion_intentar_abrir_objeto(Conexion *c, int id_objeto) {
    int exito = 0; 
    if (c->activa == 1) {
        exito = 1;
    } else if (c->id_objeto_necesario != -1 && c->id_objeto_necesario == id_objeto) {
        c->activa = 1; 
        exito = 1;
    }
    return exito; 
}

int conexion_intentar_abrir_puzzle(Conexion *c, int id_puzzle) {
    int exito = 0;
    if (c->activa == 1) {
        exito = 1;
    } else if (c->id_puzzle_necesario != -1 && c->id_puzzle_necesario == id_puzzle) {
        c->activa = 1; 
        exito = 1;
    }
    return exito; 
}