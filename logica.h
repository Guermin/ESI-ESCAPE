#ifndef LOGICA_H
#define LOGICA_H

#include "partida.h"


/* PRE:  'nombre_logueado' es una cadena pre-reservada.
 * POST: Pide credenciales. Si el usuario existe, inicia sesión. Si no, permite crear un perfil nuevo guardándolo en Jugadores.txt. Devuelve 1 en éxito, 0 en fallo/salida.
 */
int logica_sistema_login(char *nombre_logueado);

/* PRE:  'p' es un puntero inicializado.
 * POST: Muestra el menú de Login del PDF y decide si arrancar o salir. Devuelve 1 si el jugador elige entrar, o 0 si decide salir. 
 */
int logica_menu_principal(EstadoPartida *p);

/* PRE:  'p' es un puntero válido y los datos están cargados.
 * POST: Entra en el bucle principal de juego de 10 opciones. Finaliza cuando se alcanza la victoria o la opción Volver. 
 */
void logica_arrancar_bucle(EstadoPartida *p);



#endif