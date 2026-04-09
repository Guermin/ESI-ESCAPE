#ifndef LOGICA_H
#define LOGICA_H

#include "partida.h"


/* * PRE:  'nombre_logueado' es una cadena pre-reservada.
 * POST: Pide credenciales. Si el usuario existe, inicia sesión. Si no, permite 
 * crear un perfil nuevo guardándolo en Jugadores.txt. Devuelve 1 en éxito, 0 en fallo/salida.
 */
int logica_sistema_login(char *nombre_logueado);




#endif