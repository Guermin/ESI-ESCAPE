#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H


typedef struct {
    char id[3];
    char nombre[31];
    char tipo[8];        
    char descripcion[151]; 
} Sala;


typedef struct {
    char id_conexion[4];
    char id_origen[3];
    char id_destino[3];
    char estado[10];
    char condicion[5];
} Conexion;


typedef struct {
    char id[5];
    char nombre[16];
    char descripcion[51];
    char localizacion[11];
} Objeto;


typedef struct {
    char id[4];
    char nombre[16];
    char id_sala[3];
    char tipo[8];
    char descripcion[151];
    char solucion[51];
} Puzle;


typedef struct {
    char id[3];
    char nombre_completo[21];
    char usuario[11];
    char password[9];
    char inventario[20][5]; // 20 objetos, 5 caracteres cada uno.
    int num_objetos_inventario; // Contador saber cuantos objetos tiene el jugador, se declara un contador por cada jugador
} Jugador;

#endif