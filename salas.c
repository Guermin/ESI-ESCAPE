#include "salas.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Crea e inicializa una nueva estructura de tipo Sala.
 * * @param id          Identificador único de la sala.
 * @param nombre      Cadena de caracteres con el nombre corto de la sala.
 * @param descripcion Cadena de caracteres con la descripción detallada de la sala.
 * @param tipo        Enumeración o tipo que define la categoría de la sala (ej. normal, salida, etc.).
 * * @return Sala La estructura inicializada con sus datos básicos y sin objetos ni puzles.
 */
Sala sala_crear(int id, const char *nombre, const char *descripcion, TipoSala tipo) {
    Sala nueva_sala;
    int i;
    
    nueva_sala.id = id;
    nueva_sala.tipo = tipo;
    
    strncpy(nueva_sala.nombre, nombre, MAX_NOMBRE_SALA - 1);
    nueva_sala.nombre[MAX_NOMBRE_SALA - 1] = '\0'; 
    
    strncpy(nueva_sala.descripcion, descripcion, MAX_DESC_SALA - 1);
    nueva_sala.descripcion[MAX_DESC_SALA - 1] = '\0'; 

    for (i = 0; i < MAX_OBJETOS_SALA; i++) nueva_sala.id_objetos[i] = -1;
    for (i = 0; i < MAX_PUZZLES_SALA; i++) nueva_sala.id_puzzles[i] = -1;
    
    return nueva_sala; 
}

/**
 * @brief Añade un objeto al primer hueco disponible en la sala.
 * * @param s         Puntero a la sala donde se va a dejar el objeto.
 * @param id_objeto Identificador del objeto que se desea añadir.
 * * @return int 1 si se ha añadido con éxito, 0 si la sala está llena (no hay huecos a -1).
 */
int sala_añadir_objeto(Sala *s, int id_objeto) {
    int exito = 0, i = 0;
    while (i < MAX_OBJETOS_SALA && exito == 0) { 
        if (s->id_objetos[i] == -1) { 
            s->id_objetos[i] = id_objeto; 
            exito = 1;
        }
        i++;
    }
    return exito;
}

/**
 * @brief Retira un objeto específico de la sala, dejando su hueco libre.
 * * @param s         Puntero a la sala de la que se va a quitar el objeto.
 * @param id_objeto Identificador del objeto a retirar.
 * * @return int 1 si el objeto se encontró y retiró con éxito, 0 en caso contrario.
 */
int sala_quitar_objeto(Sala *s, int id_objeto) { 
    int exito = 0, i = 0;
    while (i < MAX_OBJETOS_SALA && exito == 0) {
        if (s->id_objetos[i] == id_objeto) {
            s->id_objetos[i] = -1; 
            exito = 1;
        }
        i++;
    }
    return exito;
}

/**
 * @brief Comprueba si un objeto concreto se encuentra actualmente en la sala.
 * * @param s         Estructura de la sala en la que se va a buscar.
 * @param id_objeto Identificador del objeto buscado.
 * * @return int 1 si el objeto está en la sala, 0 si no se encuentra.
 */
int sala_tiene_objeto(Sala s, int id_objeto) {
    int encontrado = 0, i = 0;
    while (i < MAX_OBJETOS_SALA && encontrado == 0) { 
        if (s.id_objetos[i] == id_objeto) encontrado = 1;
        i++;
    }
    return encontrado;
}

/**
 * @brief Añade un puzle al primer hueco disponible en la sala.
 * * @param s         Puntero a la sala donde se ubicará el puzle.
 * @param id_puzzle Identificador del puzle a añadir.
 * * @return int 1 si se ha añadido con éxito, 0 si no quedan huecos disponibles.
 */
int sala_añadir_puzzle(Sala *s, int id_puzzle) {
    int exito = 0, i = 0;
    while (i < MAX_PUZZLES_SALA && exito == 0) { 
        if (s->id_puzzles[i] == -1) {
            s->id_puzzles[i] = id_puzzle; 
            exito = 1;
        }
        i++;
    }
    return exito;
}

/**
 * @brief Comprueba si un puzle concreto se encuentra asociado a la sala.
 * * @param s         Estructura de la sala en la que se va a buscar.
 * @param id_puzzle Identificador del puzle buscado.
 * * @return int 1 si el puzle está en la sala, 0 si no se encuentra.
 */
int sala_tiene_puzzle(Sala s, int id_puzzle) {
    int encontrado = 0, i = 0;
    while (i < MAX_PUZZLES_SALA && encontrado == 0) { 
        if (s.id_puzzles[i] == id_puzzle) encontrado = 1;
        i++;
    }
    return encontrado;
}