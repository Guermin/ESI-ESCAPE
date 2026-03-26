#ifndef PUZZLES_H
#define PUZZLES_H

#define MAX_PREGUNTA 300
#define MAX_SOLUCION 50

// Enum para diferenciar si pide un número o texto 
typedef enum {
    TIPO_CODIGO,
    TIPO_PALABRA
} TipoPuzzle;

typedef struct {
    int id;
    char pregunta[MAX_PREGUNTA];
    char solucion[MAX_SOLUCION];
    TipoPuzzle tipo;
    int resuelto; // Bandera (1 = Resuelto, 0 = Pendiente)
} Puzzle;

/* * PRE:  'id' >= 0. 'pregunta' y 'solucion' no son NULL. 'tipo' es válido.
 * POST: Devuelve un Puzzle inicializado y con el estado 'resuelto' a 0 por defecto. 
 */
Puzzle puzzle_crear(int id, const char *pregunta, const char *solucion, TipoPuzzle tipo);

/* * PRE:  'p' es puntero válido a Puzzle. 'intento' no es NULL.
 * POST: Compara la respuesta. Si es correcta, pone 'resuelto' a 1 y devuelve 1. 
 * Si falla, devuelve 0. 
 */
int puzzle_intentar_resolver(Puzzle *p, const char *intento);

/* * PRE:  'p' es un Puzzle válido.
 * POST: Muestra por pantalla el texto del acertijo. 
 */
void puzzle_mostrar_pregunta(Puzzle p); 

#endif