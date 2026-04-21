#include "conexiones.h"
#include <string.h>
#include <stdio.h>

Conexion conexion_crear(int id, const char *nombre, int origen, int destino, int activa, int id_obj, int id_puz) {
    Conexion nueva_conexion;
    nueva_conexion.id = id;
    nueva_conexion.id_sala_origen = origen; //Sala en la que está el jugador
    nueva_conexion.id_sala_destino = destino; //Sala a la que llegará el jugador
    nueva_conexion.activa = activa; //1 si está abierta, 0 si está cerrada
    nueva_conexion.id_objeto_necesario = id_obj; //Condición para abrir una conexión
    nueva_conexion.id_puzzle_necesario = id_puz; //Condición para abrir una conexión
    
    strncpy(nueva_conexion.nombre, nombre, MAX_NOMBRE_CONEXION - 1);
    nueva_conexion.nombre[MAX_NOMBRE_CONEXION - 1] = '\0'; //Aseguramos que la cadena termine correctamente
    
    return nueva_conexion; 
}

int conexion_intentar_abrir_objeto(Conexion *c, int id_objeto) {
    int exito = 0; 
    if (c->activa == 1) { //Caso 1: la conexión está disponible, es decir no necesitas nada más para pasar
        exito = 1;
    } else if (c->id_objeto_necesario != -1 && c->id_objeto_necesario == id_objeto) { //Caso 2: Puerta cerrada, Se comprueba si necesita algún objeto y si el objeto que usasmos es el correcto
        c->activa = 1; 
        exito = 1;
    }
    return exito; 
}

int conexion_intentar_abrir_puzzle(Conexion *c, int id_puzzle) {
    int exito = 0;
    if (c->activa == 1) {//Caso 1: la conexión está disponible, es decir no necesitas nada más para pasar
        exito = 1;
    } else if (c->id_puzzle_necesario != -1 && c->id_puzzle_necesario == id_puzzle) {//Caso 2: Puerta cerrada, Se comprueba si necesita resolver algún puzzle y si la respuesta que damos es correcta
        c->activa = 1; 
        exito = 1;
    }
    return exito; 
}