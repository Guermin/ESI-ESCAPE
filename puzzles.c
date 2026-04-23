#include "puzzles.h"
#include <stdio.h>
#include <string.h>

/**
 * Crea e inicializa una nueva estructura de tipo Puzzle.
 * * @param id        Identificador único para el puzzle.
 * @param pregunta  Cadena de texto con el enunciado del acertijo.
 * @param solucion  Cadena de texto con la respuesta correcta.
 * @param tipo      Enumerado o valor que define la categoría del puzzle.
 * @return          Una estructura Puzzle configurada con los datos proporcionados.
 */

Puzzle puzzle_crear(int id, const char *pregunta, const char *solucion, TipoPuzzle tipo) {
    Puzzle nuevo_puzzle;
    nuevo_puzzle.id = id;
    nuevo_puzzle.tipo = tipo;
    nuevo_puzzle.resuelto = 0; 
    
    strncpy(nuevo_puzzle.pregunta, pregunta, MAX_PREGUNTA - 1);
    nuevo_puzzle.pregunta[MAX_PREGUNTA - 1] = '\0';
    
    strncpy(nuevo_puzzle.solucion, solucion, MAX_SOLUCION - 1);
    nuevo_puzzle.solucion[MAX_SOLUCION - 1] = '\0';
    
    return nuevo_puzzle; 
}
/**
 * Verifica si el intento del usuario coincide con la solución almacenada.
 * * @param p         Puntero a la estructura Puzzle (se pasa por referencia para poder modificar 'resuelto').
 * @param intento   Cadena de texto con la respuesta propuesta por el usuario.
 * @return          1 si el puzzle está resuelto (o se acaba de resolver), 0 en caso contrario.
 */

int puzzle_intentar_resolver(Puzzle *p, const char *intento) {
    int exito = 0; 
    
    if (p->resuelto == 1) {
        exito = 1; // Ya estaba resuelto previamente
    } else if (strcmp(p->solucion, intento) == 0) {
        p->resuelto = 1; 
        exito = 1; 
    }
    
    return exito; 
}
/**
 * Imprime por consola el enunciado del puzzle.
 * * @param p         Estructura Puzzle pasada por valor (solo lectura).
 */
void puzzle_mostrar_pregunta(Puzzle p) {
    printf("\n[ PUZLE ENCONTRADO ]\n");
    printf("%s\n", p.pregunta);
}