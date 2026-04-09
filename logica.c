#include "logica.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




/* PRE: Ninguna.
 * POST: Vacía el buffer estándar de entrada para evitar saltos de línea basura en los scanf.
 */
void limpiar_buffer() {
    int c, fin = 0;
    while (fin == 0) {
        c = getchar();
        if (c == '\n' || c == EOF) fin = 1;
    }
}



int logica_sistema_login(char *nombre_logueado) {
    int exito = 0;
    char usuario[50], pass[50], linea[1000], copia[1000], nuevo_nombre[50];
    char nombre_completo[50], user_file[50], pass_file[50];
    char *trozo = NULL;
    FILE *f = NULL;
    int encontrado = 0, id_max = 0, id_actual = 0, reg = 0;

    printf("==============================\n");
    printf("    LOGIN ESI ESCAPE\n");
    printf("==============================\n");
    
    printf("Usuario: ");
    if (fgets(usuario, 50, stdin) != NULL) {
        usuario[strcspn(usuario, "\n")] = '\0';
        usuario[strcspn(usuario, "\r")] = '\0';
    }
    printf("Contrasena: ");
    if (fgets(pass, 50, stdin) != NULL) {
        pass[strcspn(pass, "\n")] = '\0';
        pass[strcspn(pass, "\r")] = '\0';
    }

    f = fopen("Jugadores.txt", "r");
    if (f != NULL) {
        while (fgets(linea, sizeof(linea), f) != NULL && encontrado == 0) {
            linea[strcspn(linea, "\n")] = '\0';
            linea[strcspn(linea, "\r")] = '\0';

            strcpy(copia, linea); 
            trozo = strtok(copia, "-");
            if (trozo != NULL) {
                id_actual = atoi(trozo);
                if (id_actual > id_max) id_max = id_actual; 

                trozo = strtok(NULL, "-");
                if (trozo != NULL) strcpy(nombre_completo, trozo);

                trozo = strtok(NULL, "-");
                if (trozo != NULL) strcpy(user_file, trozo);

                trozo = strtok(NULL, "-");
                if (trozo != NULL) strcpy(pass_file, trozo);

                if (strcmp(usuario, user_file) == 0 && strcmp(pass, pass_file) == 0) {
                    encontrado = 1;
                    strcpy(nombre_logueado, user_file);
                    exito = 1;
                }
            }
        }
        fclose(f);
    }

    if (encontrado == 1) {
        printf("\n[SISTEMA]: Login correcto. Bienvenido de nuevo, %s.\n", nombre_logueado);
    } else {
        printf("\n[SISTEMA]: Usuario no encontrado o contrasena incorrecta.\n");
        printf("Deseas registrar un nuevo perfil con estos datos? (1 = Si, 0 = No): ");
        scanf("%d", &reg); 
        limpiar_buffer();
        
        if (reg == 1) {
            printf("Introduce tu Nombre Completo: ");
            if (fgets(nuevo_nombre, 50, stdin) != NULL) {
                nuevo_nombre[strcspn(nuevo_nombre, "\n")] = '\0';
                nuevo_nombre[strcspn(nuevo_nombre, "\r")] = '\0';
            }
            
            f = fopen("Jugadores.txt", "a");
            if (f != NULL) {
                fprintf(f, "\n%02d-%s-%s-%s-", id_max + 1, nuevo_nombre, usuario, pass);
                fclose(f);
                strcpy(nombre_logueado, usuario);
                printf("\n[SISTEMA]: Registro completado. Cuenta vinculada a %s.\n", usuario);
                exito = 1;
            }
        } else {
            printf("\n[SISTEMA]: Saliendo del juego...\n");
        }
    }
    return exito;
}

/* PRE:  'p' es un puntero válido que apunta a una partida inicializada.
 * POST: Busca la sala actual del jugador y muestra por pantalla su nombre y descripción.
 */
void accion_describir_sala(EstadoPartida *p) {
    Sala *sala_actual = partida_obtener_sala(p, p->jugador_actual.id_sala_actual);
    if (sala_actual != NULL) {
        printf("\n--- SALA: %s ---\n", sala_actual->nombre);
        printf("%s\n", sala_actual->descripcion);
    }
}

/* PRE:  'p' es un puntero válido.
 * POST: Muestra por pantalla los objetos que hay tirados en la sala actual y las conexiones que salen de ella (indicando si están bloqueadas o abiertas).
 */
void accion_examinar(EstadoPartida *p) {
    Sala *sala = partida_obtener_sala(p, p->jugador_actual.id_sala_actual);
    int i = 0;
    Objeto *obj = NULL;
    Conexion *con = NULL;

    if (sala != NULL) {
        printf("\n[ EXAMINANDO LA SALA ]\n>> OBJETOS SUELO:\n");
        while (i < MAX_OBJETOS_SALA) {
            if (sala->id_objetos[i] != -1) {
                obj = partida_obtener_objeto(p, sala->id_objetos[i]);
                if (obj != NULL) printf("  - [OB%02d] %s\n", obj->id, obj->nombre);
            }
            i++;
        }
        
        printf("\n>> CONEXIONES:\n");
        i = 0;
        while (i < p->num_conexiones) {
            con = &(p->conexiones[i]);
            if (con->id_sala_origen == sala->id) {
                printf("  - [C%02d] %s ", con->id, con->nombre);
                if (con->activa == 1) printf("(ABIERTA)\n");
                else printf("(BLOQUEADA)\n");
            }
            i++;
        }
    }
}

/* PRE:  'p' es un puntero válido.
 * POST: Pide al usuario el ID de una conexión. Si existe, está en la sala actual y está activa, actualiza la sala actual del jugador a la sala de destino.
 */
void accion_entrar_sala(EstadoPartida *p) {
    int id_con;
    Conexion *con = NULL;
    
    printf("Numero de la conexion (ej: 1 para C01): ");
    scanf("%d", &id_con); 
    limpiar_buffer();
    
    con = partida_obtener_conexion(p, id_con);
    
    if (con == NULL) printf("No existe.\n");
    else if (con->id_sala_origen != p->jugador_actual.id_sala_actual) printf("No esta aqui.\n");
    else if (con->activa == 0) printf("BLOQUEADA.\n");
    else { 
        jugador_mover(&(p->jugador_actual), con->id_sala_destino); 
        printf("Cruzando...\n"); 
    }
}

/* PRE:  'p' es un puntero válido.
 * POST: Pide al usuario un ID de objeto. Si el objeto está en la sala y la mochila del jugador no está llena, mueve el objeto de la sala al inventario.
 */
void accion_coger_objeto(EstadoPartida *p) {
    int id_obj, exito = 0;
    Sala *s = partida_obtener_sala(p, p->jugador_actual.id_sala_actual);
    Objeto *obj = NULL;

    printf("Numero del objeto a coger (ej: 1 para OB01): ");
    scanf("%d", &id_obj); 
    limpiar_buffer();

    if (s != NULL) {
        if (sala_tiene_objeto(*s, id_obj) == 1) {
            obj = partida_obtener_objeto(p, id_obj);
            if (obj != NULL) {
                exito = jugador_recoger_objeto(&(p->jugador_actual), id_obj);
                if (exito == 1) {
                    sala_quitar_objeto(s, id_obj);
                    printf("Has guardado [OB%02d].\n", obj->id);
                } else printf("Mochila llena/Error.\n");
            }
        } else printf("No esta aqui.\n");
    }
}



/* PRE:  'p' es un puntero válido.
 * POST: Pide al usuario un ID de objeto. Si el jugador lo tiene en su inventario  y la sala actual tiene espacio, mueve el objeto del inventario a la sala.
 */
void accion_soltar_objeto(EstadoPartida *p) {
    int id_obj, exito = 0;
    Sala *s = partida_obtener_sala(p, p->jugador_actual.id_sala_actual);
    
    printf("Numero del objeto a soltar (ej: 1 para OB01): ");
    scanf("%d", &id_obj); 
    limpiar_buffer();

    if (jugador_tiene_objeto(p->jugador_actual, id_obj) == 1) {
        exito = sala_añadir_objeto(s, id_obj);
        if (exito == 1) {
            jugador_soltar_objeto(&(p->jugador_actual), id_obj);
            printf("Objeto tirado.\n");
        } else printf("Suelo lleno.\n");
    } else printf("No lo tienes.\n");
}

/* PRE:  'p' es un puntero válido.
 * POST: Muestra por pantalla la lista de todos los objetos contenidos actualmente en la mochila del jugador.
 */
void accion_inventario(EstadoPartida *p) {
    int i = 0; 
    Objeto *obj = NULL;
    
    printf("\n=== INVENTARIO ===\n");
    if (p->jugador_actual.mochila.cantidad == 0) printf(" (Vacio)\n");
    else {
        while (i < p->jugador_actual.mochila.cantidad) {
            obj = partida_obtener_objeto(p, p->jugador_actual.mochila.ids_objetos[i]);
            if (obj != NULL) printf(" - [OB%02d] %s\n", obj->id, obj->nombre);
            i++;
        }
    }
}

/* PRE:  'p' es un puntero válido.
 * POST: Pide al usuario un ID de conexión y un ID de objeto. Si la conexión requiere ese objeto para abrirse y el jugador lo tiene, cambia el estado de la conexión a activa.
 */
void accion_usar_objeto(EstadoPartida *p) {
    int id_con, id_obj, exito = 0;
    Conexion *con = NULL;
    
    printf("Numero de conexion (ej: 1 para C01): ");
    scanf("%d", &id_con); 
    limpiar_buffer();
    
    con = partida_obtener_conexion(p, id_con);
    
    if (con == NULL) printf("Invalida.\n");
    else if (con->id_sala_origen != p->jugador_actual.id_sala_actual) printf("No esta aqui.\n");
    else if (con->activa == 1) printf("ABIERTA.\n");
    else if (con->id_objeto_necesario == -1) printf("No se abre con objetos.\n");
    else {
        printf("Numero del objeto a usar (ej: 1): ");
        scanf("%d", &id_obj); 
        limpiar_buffer();
        
        if (jugador_tiene_objeto(p->jugador_actual, id_obj) == 1) {
            exito = conexion_intentar_abrir_objeto(con, id_obj);
            if (exito == 1) printf("Exito. Conexion ABIERTA.\n");
            else printf("Ese objeto no sirve.\n");
        } else printf("No lo tienes.\n");
    }
}
