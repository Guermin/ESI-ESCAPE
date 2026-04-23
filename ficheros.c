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
                partida_anadir_sala(p, nueva);
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
                    partida_anadir_objeto(p, nuevo);
                    
                    dest = partida_obtener_sala(p, sala_loc);
                    if (dest != NULL) sala_anadir_objeto(dest, id);
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
                    partida_anadir_puzzle(p, nuevo);
                    
                    dest = partida_obtener_sala(p, sala_loc);
                    if (dest != NULL) sala_anadir_puzzle(dest, id);
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
                    partida_anadir_conexion(p, nueva);
                }
            }
        }
        fclose(f);
    }
    return exito;
}


int ficheros_cargar_todo(EstadoPartida *p) {
    int exito_total = 0;
    int s_ok, o_ok, p_ok, c_ok;
    
    printf("Procesando base de datos...\n");
    s_ok = cargar_salas(p);
    o_ok = cargar_objetos(p);
    p_ok = cargar_puzzles(p);
    c_ok = cargar_conexiones(p);
    
    if (s_ok == 1 && o_ok == 1 && p_ok == 1 && c_ok == 1) {
        exito_total = 1;
    }
    return exito_total; 
}

int ficheros_guardar_partida(EstadoPartida *p) {
    int exito = 0, i = 0, j = 0, encontrado = 0;
    FILE *f = fopen("Partida.txt", "w"); 
    
    if (f != NULL) {
        exito = 1;
        fprintf(f, "JUGADOR: 01\n"); 
        fprintf(f, "SALA: %02d\n", p->jugador_actual.id_sala_actual);
        
        while (i < p->num_objetos) {
            if (jugador_tiene_objeto(p->jugador_actual, p->objetos[i].id) == 1) {
                fprintf(f, "OBJETO: OB%02d-Inventario\n", p->objetos[i].id);
            } else {
                j = 0; encontrado = 0;
                while (j < p->num_salas && encontrado == 0) {
                    if (sala_tiene_objeto(p->salas[j], p->objetos[i].id) == 1) {
                        fprintf(f, "OBJETO: OB%02d-%02d\n", p->objetos[i].id, p->salas[j].id);
                        encontrado = 1;
                    }
                    j++;
                }
            }
            i++;
        }
        
        i = 0;
        while (i < p->num_conexiones) {
            fprintf(f, "CONEXIÓN: C%02d-%s\n", p->conexiones[i].id, p->conexiones[i].activa == 1 ? "Activa" : "Bloqueada");
            i++;
        }
        
        i = 0;
        while (i < p->num_puzzles) {
            fprintf(f, "PUZLE: P%02d-%s\n", p->puzzles[i].id, p->puzzles[i].resuelto == 1 ? "Resuelto" : "Pendiente");
            i++;
        }
        
        fclose(f);
        printf("[SISTEMA]: Partida guardada en Partida.txt.\n");
    }
    return exito;
}

int ficheros_cargar_partida(EstadoPartida *p) {
    int exito = 0;
    FILE *f = fopen("Partida.txt", "r"); 
    char linea[1000]; char *trozo = NULL;
    int id_elemento = 0, i = 0, j = 0;
    Sala *s = NULL; Conexion *con = NULL; Puzzle *puz = NULL;

    if (f != NULL) {
        exito = 1;
        
        // Vaciamos la mochila y el suelo de las salas de la partida base
        p->jugador_actual.mochila.cantidad = 0;
        for (i = 0; i < p->num_salas; i++) {
            for (j = 0; j < MAX_OBJETOS_SALA; j++) 
            p->salas[i].id_objetos[j] = -1;
        }

        while (fgets(linea, sizeof(linea), f) != NULL) {
            linea[strcspn(linea, "\n")] = '\0';
            linea[strcspn(linea, "\r")] = '\0';

            if (strncmp(linea, "SALA:", 5) == 0) {
                p->jugador_actual.id_sala_actual = extraer_numero(linea);
            } 
            else if (strncmp(linea, "OBJETO:", 7) == 0) {
                id_elemento = extraer_numero(linea); 
                
                if (strstr(linea, "Inventario") != NULL) {
                    jugador_recoger_objeto(&(p->jugador_actual), id_elemento);
                } else {
                    trozo = strtok(linea, "-");
                    trozo = strtok(NULL, "-"); 
                    if (trozo != NULL) {
                        s = partida_obtener_sala(p, atoi(trozo));
                        if (s != NULL) sala_anadir_objeto(s, id_elemento);
                    }
                }
            } 
            else if (strncmp(linea, "CONEXIÓN:", 10) == 0 || strncmp(linea, "CONEXION:", 9) == 0) {
                id_elemento = extraer_numero(linea);
                con = partida_obtener_conexion(p, id_elemento);
                if (con != NULL) {
                    if (strstr(linea, "Activa") != NULL) con->activa = 1;
                    else con->activa = 0;
                }
            } 
            else if (strncmp(linea, "PUZLE:", 6) == 0) {
                id_elemento = extraer_numero(linea);
                puz = partida_obtener_puzzle(p, id_elemento);
                if (puz != NULL) {
                    if (strstr(linea, "Resuelto") != NULL) puz->resuelto = 1;
                    else puz->resuelto = 0;
                }
            }
        }
        fclose(f);
        printf("\n[SISTEMA]: Partida cargada con exito. Retomando la accion...\n");
    } else {
        printf("\n[ERROR]: No se ha encontrado el archivo Partida.txt.\n");
    }
    return exito;
}
