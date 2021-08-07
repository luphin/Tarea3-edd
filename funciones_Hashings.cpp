#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define M 255
#define VACIA -1
#define C1 1
#define C2 0
#define C3 0
#define l 31  //como dice el enunciado

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

/*****
* int h
******
* Calculo del primer codigo de posición del hashing
******
* Input:
* int cod_producto : El codigo al cual se calculará la posición
******
* Returns:
* int, codigo de la posición del hashing
*****/
int h(int cod_producto){
    return cod_producto % 10;
}

/*****
* int p
******
* Calculo del codigo de resolución de conflictos del hashing
******
* Input:
* int cod_producto : El codigo al cual se calculará la posición
* int i : Número de la cantidad de colisiones hasta el momento
******
* Returns:
* int, codigo de la posición del hashing tras la colisión
*****/
int p(int cod_producto, int i) {
    if (i == 0) return 0;
    return C1*i*i + C2*i + C3;
}

/*****
* int hashInsertProducto
******
* Función que inserta elementos en la lista de hashing
******
* Input:
* producto HT[] : Arreglo "Hashing" donde insertar los elementos 
* producto I : Elemento a insertar en el arreglo
* int longitud : Largo del arreglo "Hashing"
******
* Returns:
* int, 0 si la inserción fue infructuosa, 1 si la inserción fue exitosa
*****/
int hashInsertProducto(producto HT[], producto I, int longitud) {   //se agrego longitud para tener el largo de array
//    cout << I.cod_producto << endl;
//    cout << I.precio << endl;
//    cout << I.nombre_producto << endl;    
    
    int inicio, i;
    int pos = inicio = h(I.cod_producto);
    for (i = 1; HT[pos].cod_producto != VACIA && HT[pos].cod_producto != I.cod_producto; i++){
        pos = (inicio + p(I.cod_producto, i)) % longitud; // próxima ranura en la secuencia
    }
    if (HT[pos].cod_producto == I.cod_producto){
        return 0; // inserción no exitosa: cod_producto repetida
    } else {
        HT[pos].cod_producto = I.cod_producto;
        HT[pos].precio = I.precio;
        for (int j = 0 ; j < l ; j++) {
            HT[pos].nombre_producto[j] = I.nombre_producto[j];
        }
        return 1; // inserción exitosa  
    }
}

/*****
* int hashInsertOferta
******
* Función que inserta elementos en la lista de hashing
******
* Input:
* oferta HT[] : Arreglo "Hashing" donde insertar los elementos 
* oferta I : Elemento a insertar en el arreglo
* int longitud : Largo del arreglo "Hashing"
******
* Returns:
* int, 0 si la inserción fue infructuosa, 1 si la inserción fue exitosa
*****/
int hashInsertOfertas(oferta HT[], oferta I, int longitud) {  //se agrego longitud para tener el largo de array
//    cout << I.cod_producto << endl;
//    cout << I.cantidad_descuento << endl;
//    cout << I.descuento << endl;
    
    int inicio, i;
    int pos = inicio = h(I.cod_producto);
    for (i = 1; HT[pos].cod_producto != VACIA && HT[pos].cod_producto != I.cod_producto; i++){
        pos = (inicio + p(I.cod_producto, i)) % longitud; // próxima ranura en la secuencia
    }
    if (HT[pos].cod_producto == I.cod_producto){
        return 0; // inserción no exitosa: cod_producto repetida
    } else {
        HT[pos].cod_producto = I.cod_producto;
        HT[pos].cantidad_descuento = I.cantidad_descuento;
        HT[pos].descuento = I.descuento;
        for (int j = 0 ; j < 10 ; j++){
            HT[pos].productos_equivalentes[j] = I.productos_equivalentes[j];
        }
        return 1; // inserción exitosa
    }
}

/*****
* producto hashSearchProducto
******
* Función que busca elementos en la lista de hashing
******
* Input:
* producto HT[] : Arreglo "Hashing" donde buscar los elementos 
* int k : Codigo del elemento a buscar
******
* Returns:
* producto, HT[pos] si la busqueda fue exitosa, val_invalido si la busqueda fue infructuosa
*****/
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

/*****
* oferta hashSearchOferta
******
* Función que busca elementos en la lista de hashing
******
* Input:
* oferta HT[] : Arreglo "Hashing" donde buscar los elementos 
* int k : Codigo del elemento a buscar
******
* Returns:
* oferta, HT[pos] si la busqueda fue exitosa, val_invalido si la busqueda fue infructuosa
*****/
oferta hashSearchOferta(oferta HT[], int k) {
    int inicio, i;
    int pos = inicio = h(k);
    for (i = 1; HT[pos].cod_producto != VACIA && HT[pos].cod_producto != k; i++)
        pos = (inicio + p(k, i)) % M; 
    if (HT[pos].cod_producto == k){
        return HT[pos]; 
    } else {
        oferta val_invalido;
        val_invalido.cod_producto = -1;
        val_invalido.descuento = -1;
        val_invalido.cantidad_descuento = -1;
        return val_invalido;
    }
}