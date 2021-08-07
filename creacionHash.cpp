#include "funciones_Hashings.cpp"

/*****
* producto* crear_Hashing_Productos
******
* Función que crea la lista de hashing
******
* Input:
* Esta función no requiere input
******
* Returns:
* producto, *hash_Productos, el arreglo de hashing
*****/
producto* crear_Hashing_Productos(){
    ifstream productos;
    productos.open("productos.dat", ios::in);
    if(!productos.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1); 
    }
    int n_productos;
    productos.read((char*)&n_productos, sizeof(int));
    int longitudA = n_productos/0.7;
    producto* hash_Productos = new producto[longitudA]; //para que de un valor entero se pasa a int, caso contrario puede dar un float
    for (int z = 0 ; z < longitudA ; z++){
        hash_Productos[z].cod_producto = VACIA;
    }
    for (int i = 0 ; i < n_productos ; i++){
        producto nuevo;
        productos.read((char*)&nuevo, sizeof(producto));
/*
        cout << nuevo.cod_producto << endl;
        cout << nuevo.precio << endl;
        cout << nuevo.nombre_producto << endl;
*/
        hashInsertProducto(hash_Productos, nuevo, longitudA);
    }
    productos.close();
    cout << "Se creo perfectamente Hash Productos 'Check'" << endl;
    return hash_Productos;
}

/*****
* oferta* crear_Hashing_Productos
******
* Función que crea la lista de hashing
******
* Input:
* Esta función no requiere input
******
* Returns:
* oferta, *hash_Ofertas, el arreglo de hashing
*****/
oferta* crear_Hashing_Ofertas(){
    ifstream ofertas;
    ofertas.open("ofertas.dat", ios::binary);
    if(!ofertas.is_open()){
        cerr << "Error al abrir el archivo\n";
        exit(1); 
    }
    int n_ofertas;
    ofertas.read((char*)&n_ofertas, sizeof(int));
    int longitudB = n_ofertas/0.7;
    oferta* hash_Ofertas = new oferta[longitudB];
    for (int z = 0 ; z < longitudB ; z++){
        hash_Ofertas[z].cod_producto = VACIA;
    }
    for (int i = 0 ; i < n_ofertas ; i++){
        oferta nuevo;
        ofertas.read((char*)&nuevo, sizeof(oferta));
/*
        cout << nuevo.cantidad_descuento << endl;
        cout << nuevo.descuento << endl;
        cout << nuevo.cod_producto << endl;
*/
        hashInsertOfertas(hash_Ofertas, nuevo, longitudB);
    }
    ofertas.close();
    cout << "Se creo perfectamente Hash Ofertas 'Check'" << endl;
    return hash_Ofertas;
}