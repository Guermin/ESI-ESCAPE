#ifndef PUZZLES_H
#define PUZZLES_H

//Tamaño máximo para los textos de los puzles
#define MAX_PREGUNTA 300
#define MAX_SOLUCION 50


typedef enum {
    TIPO_CODIGO,  
    TIPO_PALABRA  
} TipoPuzzle;

typedef struct {
    int id;                             
    char pregunta[MAX_PREGUNTA];        // texto del acertijo
    char solucion[MAX_SOLUCION];        // Guardamos la respuesta corecta como texto
    TipoPuzzle tipo;                    
    int resuelto;                       // 1 si el jugador ya lo ha acertado, 0 si no
} Puzzle;

/*
 * PRE:  Los punteros 'pregunta' y 'solucion' no deben ser nulos.
 * POST: Devuelve un Puzzle inicializado con los datos, marcado como 0 (NO resuelto) por defecto.
 */
Puzzle puzzle_crear(int id, const char *pregunta, const char *solucion, TipoPuzzle tipo);

/*
 * PRE:  'p' debe ser un puntero a un puzzle válido. 'intento' no debe ser nulo.
 * POST: Compara el intento del jugador con la solución. Si coincide, cambia el estado
 *       del puzzle a 1 (resuelto) y devuelve 1. Si falla, devuelve 0.
 */
int puzzle_intentar_resolver(Puzzle *p, const char *intento);

#endif