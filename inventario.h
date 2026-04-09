#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "objetos.h" 

#define CAPACIDAD_INICIAL_INV 2 

// Estructura dinámica que maneja la mochila
typedef struct {
    int *ids_objetos;  // Puntero para la memoria dinámica (malloc/realloc)
    int cantidad;      // Número real de objetos que llevamos
    int capacidad;     // Huecos totales reservados en memoria
} Inventario;

/* * PRE:  Ninguna.
 * POST: Devuelve Inventario pidiendo memoria dinámica inicial. Capacidad será 0 si falla malloc. 
 */
Inventario inventario_crear();

/* * PRE:  'inv' es puntero válido. 'id_objeto' >= 0.
 * POST: Añade el ID al final. Si se queda sin capacidad, hace un realloc. Devuelve 1 o 0. 
 */
int inventario_añadir(Inventario *inv, int id_objeto);

/* * PRE:  'inv' es puntero válido. 'id_objeto' >= 0.
 * POST: Borra el ID y desplaza a la izquierda todos los elementos restantes. Devuelve 1 o 0. 
 */
int inventario_quitar(Inventario *inv, int id_objeto);

/* * PRE:  'inv' es válido. 'id_objeto' >= 0.
 * POST: Devuelve 1 si el ID está en la mochila, 0 si no. 
 */
int inventario_tiene(Inventario inv, int id_objeto);

/* * PRE:  'inv' es puntero válido.
 * POST: Libera la memoria del vector dinámico con free() para evitar memory leaks. 
 */
void inventario_destruir(Inventario *inv);

#endif