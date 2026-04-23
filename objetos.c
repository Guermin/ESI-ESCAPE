#include "objetos.h"
#include <stdio.h>
#include <string.h>

/**
 * Constructor funcional para la estructura Objeto.
 * * @param id           Identificador numérico único del objeto.
 * @param nombre       Puntero a la cadena que contiene el nombre (paso por referencia constante).
 * @param descripcion  Puntero a la cadena que contiene la descripción.
 * @return             Una estructura de tipo Objeto inicializada por copia.
 */

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
/**
 * Muestra los datos del objeto por salida estándar.
 * * @param obj  Estructura Objeto pasada por VALOR.
 * Se crea una copia local en el stack de la función, 
 * protegiendo al objeto original de modificaciones.
 */
void objeto_mostrar_info(Objeto obj) {
    printf("\n[ OBJETO: %s ]\n", obj.nombre);
    printf("%s\n", obj.descripcion);
}