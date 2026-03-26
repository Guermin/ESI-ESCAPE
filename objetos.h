#ifndef OBJETOS_H
#define OBJETOS_H

#define MAX_NOMBRE_OBJETO 50
#define MAX_DESC_OBJETO 500

// Estructura básica que representa un ítem físico en el juego
typedef struct {
    int id;                                  
    char nombre[MAX_NOMBRE_OBJETO];          
    char descripcion[MAX_DESC_OBJETO];       
} Objeto;

/* * PRE:  'id' >= 0. 'nombre' y 'descripcion' no son cadenas NULL.
 * POST: Devuelve un Objeto inicializado con los textos truncados de forma segura 
 * para no desbordar los vectores estáticos. 
 */
Objeto objeto_crear(int id, const char *nombre, const char *descripcion);

/* * PRE:  'obj' es una estructura válida.
 * POST: Muestra por salida estándar el formato de inspección del objeto. 
 */
void objeto_mostrar_info(Objeto obj);

#endif