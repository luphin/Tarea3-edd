#include "funciones_Hashings.cpp"


producto* crear_Hashing_Productos(){
    fstream productos;
    productos.open("productos.dat", ios::in);
    if(!productos.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1); 
    };
    int n_productos;
    productos.read((char*)&n_productos, sizeof(int));
    producto* hash_Productos = new producto[n_productos/0.7];
    for (int i = 0 ; i < n_productos ; i++){
        producto nuevo;
        productos.read((char*)&nuevo, sizeof(producto));
        hashInsertProducto(hash_Productos, nuevo);
    };
    productos.close();
    return hash_Productos;
};

oferta* crear_Hashing_Ofertas(){
    ifstream ofertas;
    ofertas.open("ofertas.dat", ios::binary);
    if(!ofertas.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1); 
    };
    int n_ofertas;
    ofertas.read((char*)&n_ofertas, sizeof(int));
    oferta* hash_Ofertas = new oferta[n_ofertas/0.7];
    for (int i = 0 ; i < n_ofertas ; i++){
        oferta nuevo;
        ofertas.read((char*)&nuevo, sizeof(oferta));
        hashInsertOfertas(hash_Ofertas, nuevo);
    };
    ofertas.close();
    return hash_Ofertas;
};

int main(){
    oferta* hash_Ofertas = crear_Hashing_Ofertas();
    producto* hash_Productos = crear_Hashing_Productos();
    fstream compras;
    compras.open("compras.txt", ios::in);
    if(!compras.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1); 
    };
    int n_Clientes;
    compras >> n_Clientes;
    for (int i = 0 ; i < n_Clientes ; i++){
        int n_Compras;
        compras >> n_Compras;
        for (int j = 0 ; j < n_Compras ; j++){
            
        };
    };
    return 0;
};