#include <stdio.h>
#include <stdlib.h>
#include "partida.h"
#include "ficheros.h"
#include "logica.h"


int main() {
   int exito_carga = 0;
    int app_abierta = 1; 
    int quiere_jugar = 0;
    int login_ok = 0;
    char nombre_usuario[50];
    EstadoPartida mi_partida;
    // Login
    login_ok = logica_sistema_login(nombre_usuario);
    
    if (login_ok == 1) {
        // Si pasa el login, creamos la partida con su nombre
        mi_partida = partida_crear(nombre_usuario, 1);
        exito_carga = ficheros_cargar_todo(&mi_partida);
        
        if (exito_carga == 1) {
            
            while (app_abierta == 1) {
                quiere_jugar = logica_menu_principal(&mi_partida);
                
                if (quiere_jugar == 1) {
                    logica_arrancar_bucle(&mi_partida);
                } else {
                    app_abierta = 0; 
                }
            }
            
        } else {
            printf("Abortando ejecucion por errores en la base de datos de salas.\n");
        }
        partida_destruir(&mi_partida);
    }
    
    return 0;
}