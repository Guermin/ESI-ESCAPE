#include "inventario.h"
#include <stdlib.h> 

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

int inventario_añadir(Inventario *inv, int id_objeto) {
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

int inventario_tiene(Inventario inv, int id_objeto) {
    int encontrado = 0, i = 0;
    while (i < inv.cantidad && encontrado == 0) {
        if (inv.ids_objetos[i] == id_objeto) encontrado = 1;
        i++;
    }
    return encontrado; 
}

void inventario_destruir(Inventario *inv) {
    if (inv->ids_objetos != NULL) {
        free(inv->ids_objetos);
        inv->ids_objetos = NULL;
    }
    inv->cantidad = 0;
    inv->capacidad = 0;
}