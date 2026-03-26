#ifndef SALAS_H
#define SALAS_H

#define MAX_NOMBRE_SALA 50
#define MAX_DESC_SALA 500
#define MAX_OBJETOS_SALA 5
#define MAX_PUZZLES_SALA 2

typedef enum {
    INICIAL,
    NORMAL,
    SALIDA
} TipoSala;

typedef struct{
    int id;
    char nombre[MAX_NOMBRE_SALA];
    char descripcion [MAX_DESC_SALA];
    TipoSala tipo;
    int id_objetos[MAX_OBJETOS_SALA];
    int id_puzzles[MAX_PUZZLES_SALA];
}Sala;

/*  PRE: id válido, nombre válido, descripción válida y tipo válido
    POST: Devuelve una sala con todos sus datos*/
Sala sala_crear(int id, const char *nombre, const char *descripcion, TipoSala tipo);

/* PRE: 's' válida. 
   POST: Añade el ID en el primer hueco libre. Devuelve 1 o 0. */
int sala_añadir_objeto(Sala *s, int id_objeto);

/* PRE: 's' válida. 
    POST: Busca el ID y lo sustituye por -1. Devuelve 1 o 0. 
*/
int sala_quitar_objeto(Sala *s, int id_objeto);

/* PRE: 's' válida. 
   POST: Devuelve 1 si el objeto está en el suelo de la sala, 0 si no. */
int sala_tiene_objeto(Sala s, int id_objeto);

/* PRE: 's' válida. 
   POST: Añade el puzle en el primer hueco libre. Devuelve 1 o 0. */
int sala_añadir_puzzle(Sala *s, int id_puzzle);

/* PRE: 's' válida. 
   POST: Devuelve 1 si el puzle está en la sala, 0 si no. */
int sala_tiene_puzzle(Sala s, int id_puzzle);

#endif
