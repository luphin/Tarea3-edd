#include "funciones_Hashings.cpp"

struct Nodo{
    int code;
    int amount;
};

typedef struct Nodo Nodo;

producto* crear_Hashing_Productos(){
    int longitudA;  //agrego, se almacena el largo del array (M)
    ifstream productos;
    productos.open("productos.dat", ios::in);
    if(!productos.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1); 
    }
    int n_productos;
    productos.read((char*)&n_productos, sizeof(int));
    longitudA = n_productos/0.7;
    producto* hash_Productos = new producto[longitudA]; //para que de un valor entero se pasa a int, caso contrario puede dar un float
    for (int i = 0 ; i < n_productos ; i++){
        producto nuevo;
        productos.read((char*)&nuevo, sizeof(producto));
        hashInsertProducto(hash_Productos, nuevo, longitudA);
    }
    productos.close();
    return hash_Productos;
}

oferta* crear_Hashing_Ofertas(){
    int longitudB;  //agrego, se almacena el largo del array (M)
    ifstream ofertas;
    ofertas.open("ofertas.dat", ios::binary);
    if(!ofertas.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1); 
    }
    int n_ofertas;
    ofertas.read((char*)&n_ofertas, sizeof(int));
    longitudB = n_ofertas/0.7;
    oferta* hash_Ofertas = new oferta[longitudB]; //para que de un valor entero se pasa a int
    for (int i = 0 ; i < n_ofertas ; i++){
        oferta nuevo;
        ofertas.read((char*)&nuevo, sizeof(oferta));
        hashInsertOfertas(hash_Ofertas, nuevo, longitudB);
    }
    ofertas.close();
    return hash_Ofertas;
}


int main(){
    oferta* hash_Ofertas = crear_Hashing_Ofertas();
    producto* hash_Productos = crear_Hashing_Productos();
    fstream compras;
    compras.open("compras.txt", ios::in);
    if(!compras.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1); 
    }
    fstream boletas;
    boletas.open("boletas.txt", ios::out);
    int n_Clientes;  
    compras >> n_Clientes; //obtiene numero de clientes
    for (int i = 0 ; i < n_Clientes ; i++){
        int n_Compras;
        int *Memoria;
        int *Memory;
        compras >> n_Compras; //cantidad de compras
        Memoria = new int[n_Compras];
        Memory = new int[n_Compras];
        for (int j = 0 ; j < n_Compras ; j++){
            compras >> Memoria[j];          
        }
        for (int x = 0; x < n_Compras; x++) {
            for (int q = 0; q < n_Compras-x-1; q++) {
                if(Memoria[q] < Memoria[q+1]){
                    int tmp = Memoria[q+1];
                    Memoria[q+1] = Memoria[q];
                    Memoria[q] = tmp;
                }
            }
        }
        int tipo_productos = 0;
        for (int y = 0 ; y < n_Compras ; y++){ //Se crea una variable, que se llena con el numero de productos distintos
            if (y == n_Compras - 1){
                if (Memoria[y] != Memoria[y - 1]){
                    tipo_productos++;
                }
            } else if (Memoria[y] != Memoria[y + 1]){
                tipo_productos++;
            }
        }
        Nodo tipo_compras[tipo_productos];
        int contador = 0;
        for (int z = 0 ; z < n_Compras ; z++){
            if (z != 0){
                if (Memoria[z] != Memoria[z - 1]){
                    contador++;
                }
            }
            Nodo elem;
            elem.code = Memoria[z];
            if (tipo_compras[contador].code != elem.code){
                tipo_compras[contador] = elem;
            }
            tipo_compras[contador].amount++;
        }
        int val_a_pagar = 0;
        for (int a = 0 ; a < tipo_productos ; a++){
            //Aqui va el calculo del valor, comprobando por equivalentes, y sumar el precio a val_a_pagar
        }
        boletas << val_a_pagar;
    }
    compras.close();
    return 0;
}

