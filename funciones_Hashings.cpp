#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define M 1000000
#define VACIA -1
#define C1 1
#define C2 0
#define C3 0
#define l 50  //ver si se deja en 50 o se baja a 31 como dice el enunciado

struct producto {
    int cod_producto;
    char nombre_producto[l];
    int precio;
};

struct oferta {
    int cod_producto;
    int cantidad_descuento;
    int descuento;
    int productos_equivalentes[10];
};

int h(int cod_producto){
    return cod_producto % 10;
}

int p(int cod_producto, int i) {
    if (i == 0) return 0;
    return C1*i*i + C2*i + C3;
}

int hashInsertProducto(producto HT[], producto I, int longitud) {   //se agrego longitud para tener el largo de array
    int inicio, i;
    int pos = inicio = h(I.cod_producto);
    for (i = 1; HT[pos].cod_producto != VACIA && HT[pos].cod_producto != I.cod_producto; i++)
    pos = (inicio + p(I.cod_producto, i)) % longitud; // próxima ranura en la secuencia
    if (HT[pos].cod_producto == I.cod_producto){
        return 0; // inserción no exitosa: cod_producto repetida
    } else {
        HT[pos].cod_producto = I.cod_producto;
        HT[pos].precio = I.precio;
        for (int j = 0 ; j < l ; j++) {
            HT[pos].nombre_producto[j] = I.nombre_producto[j];
        return 1; // inserción exitosa
        }
    }
}

int hashInsertOfertas(oferta HT[], oferta I, int longitud) {  //se agrego longitud para tener el largo de array
    int inicio, i;
    int pos = inicio = h(I.cod_producto);
    for (i = 1; HT[pos].cod_producto != VACIA && HT[pos].cod_producto != I.cod_producto; i++)
    pos = (inicio + p(I.cod_producto, i)) % longitud; // próxima ranura en la secuencia
    if (HT[pos].cod_producto == I.cod_producto){
        return 0; // inserción no exitosa: cod_producto repetida
    } else {
        HT[pos].cod_producto = I.cod_producto;
        HT[pos].cantidad_descuento = I.cantidad_descuento;
        HT[pos].descuento = I.descuento;
        for (int j = 0 ; j < 10 ; j++){
            HT[pos].productos_equivalentes[j] = I.productos_equivalentes[j];
        return 1; // inserción exitosa
        }
    }
}



producto hashSearchProducto(producto HT[], int k) {
    int inicio, i;
    int pos = inicio = h(k);
    for (i = 1; HT[pos].cod_producto != VACIA && HT[pos].cod_producto != k; i++)
        pos = (inicio + p(k, i)) % M; // próxima ranura en la secuencia
    if (HT[pos].cod_producto == k){
        return HT[pos]; // registro encontrado, búsqueda exitosa
    } else {
        producto val_invalido;
        val_invalido.cod_producto = -1;
        val_invalido.precio = -1;
        return val_invalido; // Ejercicio: solucionar esto!
    }
}

oferta hashSearchOferta(oferta HT[], int k) {
    int inicio, i;
    int pos = inicio = h(k);
    for (i = 1; HT[pos].cod_producto != VACIA && HT[pos].cod_producto != k; i++)
        pos = (inicio + p(k, i)) % M; // próxima ranura en la secuencia
    if (HT[pos].cod_producto == k){
        return HT[pos]; // registro encontrado, búsqueda exitosa
    } else {
        oferta val_invalido;
        val_invalido.cod_producto = -1;
        val_invalido.descuento = -1;
        val_invalido.cantidad_descuento = -1;
        return val_invalido; // Ejercicio: solucionar esto!
    }
}


/*
Se quitaron algunas comillas que no eran necesarias y generaban errores, se agrego longitud en las lineas 26 y 53 
que corresponden a los hashinsert, de esta forma se sabe la longitud de los array (M)  2/AGOSTO
*/