#include "funciones_Hashings.cpp"

struct Nodo{
    int code;
    int amount;
};

typedef struct Nodo Nodo;

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
        hashInsertProducto(hash_Productos, nuevo, longitudA);
    }
    productos.close();
    cout << "Se creo perfectamente Hash Productos 'Check'" << endl;
    return hash_Productos;
}

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
    oferta* hash_Ofertas = new oferta[longitudB]; //para que de un valor entero se pasa a int
    for (int z = 0 ; z < longitudB ; z++){
        hash_Ofertas[z].cod_producto = VACIA;
    }
    for (int i = 0 ; i < n_ofertas ; i++){
        oferta nuevo;
        ofertas.read((char*)&nuevo, sizeof(oferta));
        hashInsertOfertas(hash_Ofertas, nuevo, longitudB);
    }
    ofertas.close();
    cout << "Se creo perfectamente Hash Ofertas 'Check'" << endl;
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
    int n_Clientes_1 = 1;
    compras >> n_Clientes; //obtiene numero de clientes
    for (int i = 0 ; i < n_Clientes ; i++){
        int n_Compras;
        int *Memoria;
//        int *Memory;
        compras >> n_Compras; //cantidad de compras
        Memoria = new int[n_Compras];
//        Memory = new int[n_Compras];
        for (int j = 0 ; j < n_Compras ; j++){
            compras >> Memoria[j];          
        }
        cout << "llego aca 1 \n"; //quitar
        for (int x = 0; x < n_Compras; x++) {
            for (int q = 0; q < n_Compras-x-1; q++) {
                if(Memoria[q] > Memoria[q+1]){
                    int tmp = Memoria[q+1];
                    Memoria[q+1] = Memoria[q];
                    Memoria[q] = tmp;
                }
            }
        }
        for(int d = 0; d < n_Compras;d++){
            cout << Memoria[d] << endl;
        }
        cout << "llego aca 2 \n"; //quitar
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
        cout << "llego aca 3 \n"; //quitar
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
            cout << "Inicia:"<<endl;
            cout << tipo_compras[contador].amount << endl;
            cout << "Termina:" << endl;
        }
        cout << "llego aca 4 \n"; //quitar
        int val_a_pagar = 0;
        int descuentototal = 0;
        int render[tipo_productos];
        for (int a = 0 ; a < tipo_productos ; a++){ //solo la suma de todos los productos, dado que pueden tener distintos precios
            //Aqui va el calculo del valor, comprobando por equivalentes, y sumar el precio a val_a_pagar
            Nodo val_1 = tipo_compras[a];           //almacena el nodo en la posicion a de tip_comrpas
            int cantidadtotal = 0 ;
            val_a_pagar =  val_a_pagar + (hashSearchProducto(hash_Productos ,val_1.code).precio);
            cout << val_a_pagar<< "    " << val_1.amount <<endl;
        }
        /*
        for (int a = 0 ; a < tipo_productos ; a++){  //calculamos el descuento, dado que pueden tener los mismos descuentos un producto con otro, de esta forma no se revisa 2 veces el mismo porducto
            
            Nodo val_2 = tipo_compras[a]; //almacena el nodo en la posicion a de tipo_comrpas
            int cantidadtotal = 0 ;
            cantidadtotal = cantidadtotal + val_2.amount; //variable para almacenar la cantidad de productos totales, al fin y al cabo tiene el mismo valor de descuento con los equivalentes

            oferta flash = hashInsertOfertas(hash_Ofertas, val_2.code) //almacena el struck ofecta, para asi tenerlo a mano 
            for(int w = 0; w < 10; w++){ //iteramos dentro de los productos que son equivalentes
                if(flash.productos_equivalentes[w] == -1){  //si es igual a -1 se termina porque los demas van a ser -1 igualemnete
                    descuentototal = descuentototal + (int(cantidatotal % flash.cantidad_descuento) * flash.descuento); //se calcula el descuento total de los equivalentes antes de forzar el cierre del for
                    break;
                }
                for (int t= 0; t < tipo_productos; t++){  //para iterar dentro de tipo_compras y asi descontar de una los productos que son equivalentes
                    if(flash.productos_equivalentes[w] == tipo_compras[t].code){ 
                        cantidadtotal = cantidadtotal + tipo_compras[t].amount; //suma el valor de los productos que se encuentren
                        for(contador = t; contador < tipo_productos; contador++){  //eleminar el struck de tipo_compras, asi se aplica el descuento de una
			                strcpy(tipo_compras[contador], tipo_compras[contador + 1]);	// NO ESTOY SEGURO SI FUNCIONA, borra el struck del array tipo_compras
		                }
                    }
                }
            }
            
        }
        */
        val_a_pagar = val_a_pagar - descuentototal; //calcula el total, valor total - descuento
        boletas << "numero de clientes"<< n_Clientes << endl;
        
        boletas << "Valor a pagar cliente " << n_Clientes_1 << ": $" << val_a_pagar << endl;
        
        n_Clientes_1 = n_Clientes + 1;

        if (n_Clientes == n_Clientes_1){
            break;
        } 
    }
    compras.close();
    boletas.close();
    return 0;
}

