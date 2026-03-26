#include "objetos.h"
#include <stdio.h>
#include <string.h>

Objeto objeto_crear(int id, const char *nombre, const char *descripcion) {
    Objeto nuevo_objeto;
    nuevo_objeto.id = id;
    
    // Usamos strncpy para evitar desbordamientos de memoria.
    strncpy(nuevo_objeto.nombre, nombre, MAX_NOMBRE_OBJETO - 1);
    nuevo_objeto.nombre[MAX_NOMBRE_OBJETO - 1] = '\0';
    
    strncpy(nuevo_objeto.descripcion, descripcion, MAX_DESC_OBJETO - 1);
    nuevo_objeto.descripcion[MAX_DESC_OBJETO - 1] = '\0';
    
    return nuevo_objeto; 
}

void objeto_mostrar_info(Objeto obj) {
    printf("\n[ OBJETO: %s ]\n", obj.nombre);
    printf("%s\n", obj.descripcion);
}