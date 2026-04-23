#include "inventario.h"
#include <stdlib.h> 

/**
 * Inicializa un inventario vacío con memoria dinámica.
 * @return Una estructura Inventario con memoria reservada en el heap.
 */
Inventario inventario_crear() {
    Inventario nuevo_inv;
    nuevo_inv.cantidad = 0;
    nuevo_inv.capacidad = CAPACIDAD_INICIAL_INV;
    
    // Reserva de memoria inicial requerida por la asignatura
    nuevo_inv.ids_objetos = (int *)malloc(nuevo_inv.capacidad * sizeof(int));
    if (nuevo_inv.ids_objetos == NULL) {
        nuevo_inv.capacidad = 0; 
    }
    return nuevo_inv; 
}
/**
 * Anade un objeto al inventario, redimensionando si es necesario.
 * @param inv       Puntero al inventario (paso por referencia para modificar capacidad/cantidad).
 * @param id_objeto El identificador que queremos guardar.
 * @return          1 si se anadió con éxito, 0 si hubo error de memoria.
 */

int inventario_anadir(Inventario *inv, int id_objeto) {
    int exito = 0;
    int *temp = NULL; 
    
    // Si llegamos al límite, ampliamos la memoria usando realloc
    if (inv->cantidad == inv->capacidad) {
        temp = (int *)realloc(inv->ids_objetos, (inv->capacidad + CAPACIDAD_INICIAL_INV) * sizeof(int));
        if (temp != NULL) { 
            inv->ids_objetos = temp;
            inv->capacidad = inv->capacidad + CAPACIDAD_INICIAL_INV;
        }
    }
    
    if (inv->cantidad < inv->capacidad) {
        inv->ids_objetos[inv->cantidad] = id_objeto; 
        inv->cantidad = inv->cantidad + 1;
        exito = 1;
    }
    return exito; 
}
/**
 * Elimina un objeto buscando su ID y desplazando los elementos restantes.
 * @param inv       Puntero al inventario original.
 * @param id_objeto ID del objeto a borrar.
 * @return          1 si se encontró y borró, 0 si no existía.
 */
int inventario_quitar(Inventario *inv, int id_objeto) {
    int exito = 0, i = 0, pos = -1;
    
    while (i < inv->cantidad && pos == -1) {
        if (inv->ids_objetos[i] == id_objeto) pos = i;
        i++;
    }
    
    // Algoritmo de borrado y desplazamiento a la izquierda en un vector
    if (pos != -1) {
        i = pos;
        while (i < inv->cantidad - 1) {
            inv->ids_objetos[i] = inv->ids_objetos[i + 1]; 
            i++;
        }
        inv->cantidad = inv->cantidad - 1; 
        exito = 1;
    }
    return exito; 
}
/**
 * Comprueba si un objeto existe en el inventario.
 * @param inv       Pasado por VALOR (copia), ya que no vamos a modificar el inventario.
 * @param id_objeto ID a buscar.
 * @return          1 si existe, 0 si no.
 */
int inventario_tiene(Inventario inv, int id_objeto) {
    int encontrado = 0, i = 0;
    while (i < inv.cantidad && encontrado == 0) {
        if (inv.ids_objetos[i] == id_objeto) encontrado = 1;
        i++;
    }
    return encontrado; 
}
/**
 * Libera la memoria dinámica para evitar fugas de memoria (memory leaks).
 * @param inv       Puntero al inventario que queremos limpiar.
 */
void inventario_destruir(Inventario *inv) {
    if (inv->ids_objetos != NULL) {
        free(inv->ids_objetos);
        inv->ids_objetos = NULL;
    }
    inv->cantidad = 0;
    inv->capacidad = 0;
}