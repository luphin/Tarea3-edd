#include "creacionHash.cpp"

struct Nodo{
    int code;
    int amount;
};

typedef struct Nodo Nodo;

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
        for (int x = 0; x < n_Compras; x++) { //ordena el Array de menor a mayor
            for (int q = 0; q < n_Compras-x-1; q++) {
                if(Memoria[q] > Memoria[q+1]){
                    int tmp = Memoria[q+1];
                    Memoria[q+1] = Memoria[q];
                    Memoria[q] = tmp;
                }
            }
        }
        for(int d = 0; d < n_Compras;d++){
//            cout << Memoria[d] << endl;
        }

        int val_a_pagar = 0;
        int x = 0;
        while(x < n_Compras){  // revisa cuantos valores iguales hay dentro del array https://onlinegdb.com/Bsf9UvJ4k pueden verlo ahi con un ejemplo como funciona.
            int contador = 0;
            int first = Memoria[x];
//            cout << "Patron: " << first << endl;
            for(int y = x; y < n_Compras ; y++){
//                cout << "Valor : "<< Memoria[y] <<endl;
                if(Memoria[y] == first){
                    contador++;
                }
            }
            val_a_pagar =  val_a_pagar + (hashSearchProducto(hash_Productos ,first).precio * contador); //prueba, veamos si se quita
//            cout << contador <<endl;
            x = contador+x;
        }

        cout << "llego aca 4 \n"; //quitar

        cout << hashSearchOferta(hash_Ofertas, 2).cod_producto << endl;
        cout << hashSearchOferta(hash_Ofertas, 2).descuento << endl;
        cout << hashSearchOferta(hash_Ofertas, 2).cantidad_descuento << endl;

        cout << hashSearchOferta(hash_Ofertas, 3).cod_producto << endl;
        cout << hashSearchOferta(hash_Ofertas, 3).descuento << endl;
        cout << hashSearchOferta(hash_Ofertas, 3).cantidad_descuento << endl;

//        int val_a_pagar = 0;
        int descuentototal = 0;
//        int render[tipo_productos];
//        for (int a = 0 ; a < tipo_productos ; a++){ //solo la suma de todos los productos, dado que pueden tener distintos precios
//            //Aqui va el calculo del valor, comprobando por equivalentes, y sumar el precio a val_a_pagar
//            Nodo val_1 = tipo_compras[a];           //almacena el nodo en la posicion a de tip_comrpas
//            int cantidadtotal = 0 ;
//            cout << "Precio:"<<hashSearchProducto(hash_Productos ,val_1.code).precio<<endl; //quitar
//            val_a_pagar =  val_a_pagar + (hashSearchProducto(hash_Productos ,val_1.code).precio);
//            cout << val_a_pagar<< "    " << val_1.amount <<endl; //quitar
//        }
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
        boletas << "numero de clientes : "<< n_Clientes << endl;
        
        boletas << "Valor a pagar cliente " << n_Clientes_1 << ": $" << val_a_pagar << endl;
        
        n_Clientes_1 = n_Clientes + 1;

        if (n_Clientes == n_Clientes_1){
            break;
        } 
    }
    delete[] hash_Productos;
    delete[] hash_Ofertas;
    compras.close();
    boletas.close();
    return 0;
}

