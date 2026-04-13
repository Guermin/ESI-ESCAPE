#include "ficheros.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




/* PRE:  'cadena' no es NULL.
 * POST: Busca el primer dígito en un texto ignorando prefijos y devuelve su valor numérico.
 */
int extraer_numero(char *cadena) {
    int i = 0, num = 0, encontrado = 0;
    while (cadena[i] != '\0' && encontrado == 0) {
        if (cadena[i] >= '0' && cadena[i] <= '9') {
            num = atoi(&cadena[i]); 
            encontrado = 1;
        }
        i++;
    }
    return num; 
}


/* PRE: 'p' válida. 
 * POST: Lee Salas.txt usando strtok y devuelve 1 en caso de éxito o 0 en caso de fallo.
 */
int cargar_salas(EstadoPartida *p) {
    int exito = 0;
    FILE *f = fopen("Salas.txt", "r");
    char linea[1000]; char *trozo = NULL;
    int id, tipo; char n[MAX_NOMBRE_SALA], d[MAX_DESC_SALA];
    
    if (f != NULL) {
        exito = 1;
        while (fgets(linea, sizeof(linea), f) != NULL && p->num_salas < MAX_SALAS_PARTIDA) {
            linea[strcspn(linea, "\n")] = '\0';
            linea[strcspn(linea, "\r")] = '\0';
            
            trozo = strtok(linea, "-");
            if (trozo != NULL) {
                id = extraer_numero(trozo); 
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) strcpy(n, trozo);
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) {
                    if (strcmp(trozo, "INICIAL") == 0) tipo = 0;
                    else if (strcmp(trozo, "SALIDA") == 0) tipo = 2;
                    else tipo = 1;
                }
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) strcpy(d, trozo);
                
                Sala nueva = sala_crear(id, n, d, (TipoSala)tipo);
                partida_añadir_sala(p, nueva);
            }
        }
        fclose(f);
    }
    return exito;
}

/* PRE: 'p' válida. 
 * POST: Lee Objetos.txt y los mete en sus salas. Devuelve 1 en caso de éxito o 0 en caso de fallo.
 */
int cargar_objetos(EstadoPartida *p) {
    int exito = 0;
    FILE *f = fopen("Objetos.txt", "r");
    char linea[1000]; char *trozo = NULL;
    int id, sala_loc; char n[MAX_NOMBRE_OBJETO], d[MAX_DESC_OBJETO];
    Sala *dest = NULL;
    
    if (f != NULL) {
        exito = 1;
        while (fgets(linea, sizeof(linea), f) != NULL && p->num_objetos < MAX_OBJETOS_PARTIDA) {
            linea[strcspn(linea, "\n")] = '\0';
            linea[strcspn(linea, "\r")] = '\0';
            
            trozo = strtok(linea, "-");
            if (trozo != NULL) {
                id = extraer_numero(trozo);
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) strcpy(n, trozo);
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) strcpy(d, trozo);
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) {
                    sala_loc = atoi(trozo);
                    
                    Objeto nuevo = objeto_crear(id, n, d);
                    partida_añadir_objeto(p, nuevo);
                    
                    dest = partida_obtener_sala(p, sala_loc);
                    if (dest != NULL) sala_añadir_objeto(dest, id);
                }
            }
        }
        fclose(f);
    }
    return exito;
}

/* PRE: 'p' válida. 
 * POST: Lee Puzles.txt. Devuelve 1 en caso de éxito o 0 en caso de fallo.
 */
int cargar_puzzles(EstadoPartida *p) {
    int exito = 0;
    FILE *f = fopen("Puzles.txt", "r");
    char linea[1000]; char *trozo = NULL;
    int id, sala_loc, tipo; char preg[MAX_PREGUNTA], sol[MAX_SOLUCION];
    Sala *dest = NULL;
    
    if (f != NULL) {
        exito = 1;
        while (fgets(linea, sizeof(linea), f) != NULL && p->num_puzzles < MAX_PUZZLES_PARTIDA) {
            linea[strcspn(linea, "\n")] = '\0';
            linea[strcspn(linea, "\r")] = '\0';
            
            trozo = strtok(linea, "-");
            if (trozo != NULL) {
                id = extraer_numero(trozo);
                
                trozo = strtok(NULL, "-");
                trozo = strtok(NULL, "-");
                if (trozo != NULL) sala_loc = atoi(trozo);
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) {
                    if (strcmp(trozo, "Palabra") == 0) tipo = 1;
                    else tipo = 0;
                }
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) strcpy(preg, trozo);
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) {
                    strcpy(sol, trozo);
                    Puzzle nuevo = puzzle_crear(id, preg, sol, (TipoPuzzle)tipo);
                    partida_añadir_puzzle(p, nuevo);
                    
                    dest = partida_obtener_sala(p, sala_loc);
                    if (dest != NULL) sala_añadir_puzzle(dest, id);
                }
            }
        }
        fclose(f);
    }
    return exito;
}

/* PRE: 'p' válida. 
 * POST: Lee Conexiones.txt y las carga en la partida. Devuelve 1 en caso de éxito o 0 en caso de fallo.
 */
int cargar_conexiones(EstadoPartida *p) {
    int exito = 0;
    FILE *f = fopen("Conexiones.txt", "r");
    char linea[1000]; char *trozo = NULL;
    int id, orig, dest, act, id_obj, id_puz; char n[MAX_NOMBRE_CONEXION];
    
    if (f != NULL) {
        exito = 1;
        while (fgets(linea, sizeof(linea), f) != NULL && p->num_conexiones < MAX_CONEXIONES_PARTIDA) {
            linea[strcspn(linea, "\n")] = '\0';
            linea[strcspn(linea, "\r")] = '\0';
            
            id_obj = -1; id_puz = -1;
            
            trozo = strtok(linea, "-");
            if (trozo != NULL) {
                id = extraer_numero(trozo);
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) orig = atoi(trozo);
                
                trozo = strtok(NULL, "-");
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) dest = atoi(trozo);
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) strcpy(n, trozo);
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) {
                    if (strcmp(trozo, "Activa") == 0) act = 1;
                    else act = 0;
                }
                
                trozo = strtok(NULL, "-");
                if (trozo != NULL) {
                    if (trozo[0] == 'O' || trozo[0] == 'o') id_obj = extraer_numero(trozo);
                    else if (trozo[0] == 'P' || trozo[0] == 'p') id_puz = extraer_numero(trozo);
                    
                    Conexion nueva = conexion_crear(id, n, orig, dest, act, id_obj, id_puz);
                    partida_añadir_conexion(p, nueva);
                }
            }
        }
        fclose(f);
    }
    return exito;
}
