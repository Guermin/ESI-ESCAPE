#include "puzzles.h"
#include <stdio.h>
#include <string.h>

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

void puzzle_mostrar_pregunta(Puzzle p) {
    printf("\n[ PUZLE ENCONTRADO ]\n");
    printf("%s\n", p.pregunta);
}