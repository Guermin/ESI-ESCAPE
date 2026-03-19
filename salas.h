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


Sala sala_crear(int id, const char *nombre, const char *descripcion, TipoSala tipo);

void sala_mostrar_info(Sala sala);

#endif