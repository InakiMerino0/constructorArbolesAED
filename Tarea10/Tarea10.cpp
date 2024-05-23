#include <iostream>
#include <iomanip>

using namespace std;

template<typename T>
class Cola {
private:
    // Definicion del nodo interno de la cola
    struct Nodo {
        T dato;        // Dato almacenado en el nodo
        Nodo* siguiente; // Puntero al siguiente nodo en la cola

        // Constructor del Nodo
        Nodo(T dato, Nodo* sig = nullptr) : dato(dato), siguiente(sig) {}
    };

    Nodo* frente; // Puntero al primer nodo de la cola
    Nodo* final;  // Puntero al ultimo nodo de la cola

public:
    // Constructor de la cola
    Cola() : frente(nullptr), final(nullptr) {}

    // Destructor de la cola
    ~Cola() {
        while (frente != nullptr) { // Liberar todos los nodos
            Nodo* temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
    }

    // Metodo para agregar un elemento al final de la cola
    void enqueue(T dato) {
        Nodo* nuevoNodo = new Nodo(dato);
        if (final == nullptr) {
            // Si la cola esta vacia, frente y final apuntan al nuevo nodo
            frente = final = nuevoNodo;
        }
        else {
            // Si no esta vacia, añadir el nuevo nodo al final y actualizar el puntero final
            final->siguiente = nuevoNodo;
            final = nuevoNodo;
        }
    }

    // Metodo para eliminar el elemento al frente de la cola
    T dequeue() {
        if (frente == nullptr) {
            throw std::out_of_range("Intento de dequeue en cola vac�a");
        }
        Nodo* temp = frente;
        T dato = frente->dato;
        frente = frente->siguiente;

        if (frente == nullptr) {
            final = nullptr; // Si la cola esta vacia, ajustar el puntero final
        }

        delete temp; // Liberar el nodo eliminado
        return dato; // Devolver el dato del nodo eliminado
    }

    // Metodo para comprobar si la cola esta vacia
    bool estaVacia() const {
        return frente == nullptr;
    }
};

// Se crea clase Nodo para crear los nodos del arbol 
template<typename T>
class Nodo {
public:
    T dato;
    Nodo* izquierda, * derecha;
    int altura;

    Nodo(T val) : dato(val), izquierda(nullptr), derecha(nullptr), altura(1) {}
};

template<typename T>
class ArbolB {
private:

    Nodo<T>* raiz;

    // Funcion para mostrar los elementos de un arbol en orden
    void inOrden(Nodo<T>* nodo) {
        if (nodo != nullptr) {
            inOrden(nodo->izquierda);
            cout << nodo->dato << " ";
            inOrden(nodo->derecha);
        }
    }
    //funcion para mostrar post-order
    void postOrden(Nodo<T>* nodo) {
        if (nodo != nullptr) {
            postOrden(nodo->izquierda);
            postOrden(nodo->derecha);
            cout << nodo->dato << " ";
        }
    }
    //Funcion para mostrar los elementos pre-order
    void preOrden(Nodo<T>* nodo) {
        if (nodo != nullptr) {
            cout << nodo->dato << " ";
            preOrden(nodo->izquierda);
            preOrden(nodo->derecha);
        }
    }

public:

    ArbolB() : raiz(nullptr) {}

    // Funciones para mostrar los elementos del arbol en orden, post-order y pre-order
    void mostrarInOrden() {
        inOrden(raiz);
        cout << endl;
    }
    void mostrarPostOrder() {
        postOrden(raiz);
        cout << endl;
    }
    void mostrarPreOrder() {
        preOrden(raiz);
        cout << endl;
    }
    
    // Funcion para insertar elementos al array, y luego al arbol
    void insertarArbol() {

        //Ingreso de cantidad de nodos y declaracion de array de nodos
        int cantidadNodos = 0;
        cout << "Ingrese cuantos nodos desea insertar: ";
        cin >> cantidadNodos;

        T* vectorDatos = new T[cantidadNodos];

        for (int i = 0; i < cantidadNodos; i++) {
            cout << "Ingrese nodo " << i + 1 << endl;
            cin >> vectorDatos[i];
        }

        // Declaracion de cola para insertar nodos que aun no tienen hijos
        Cola<Nodo<T>*> nodosInsertar;

        // Insercion de nodos desde el array hacia el arbol
        for (int i = 0; i <= cantidadNodos; i = i+2) {
            
            if (raiz == nullptr) {
                // Si raiz null, arbol vacio, entonces se inserta valor 0 (de vectorDatos) en raiz
                raiz = new Nodo<T>(vectorDatos[i]);

                // Se inserta raiz a la cola de nodos a los que hay que insertar hijos
                nodosInsertar.enqueue(raiz);
			}
            else {

                // Raiz no null, entonces se insertan los hijos al proximo nodo en cola nodosInsertar
                Nodo<T>* temp = nodosInsertar.dequeue();

                // Se insertan los hijos al nodo temp, el izquierdo es el valor i-1 y el derecho es el valor i
                // Aclaracion: izquierdo es i-1 por que se suma 2 a i en cada iteracion, esto para no insertar dos veces la misma posicion de array duplicando nodos
                temp->izquierda = new Nodo<T>(vectorDatos[i - 1]);
                // Verifica si ya se insertaron todos los nodos (ultimo nodo tiene 1 hijo si cantidadNodos es par. Con el if, se evita dar un valor no existente como hijo derecho)
                if (i == cantidadNodos) {
                    break;
                } 
                temp->derecha = new Nodo<T>(vectorDatos[i]);
                
                // Se insertan los hijos del nodo temp a la cola nodosInsertar, para que se les inserten hijos en la siguiente iteracion
                nodosInsertar.enqueue(temp->izquierda);
                nodosInsertar.enqueue(temp->derecha);

            }
        }

        mostrarInOrden();

        // Liberacion de memoria
        delete[] vectorDatos;
    }

    // Funcion para el menu de opciones
    void menuBinarios() {
        int select = 0;
        while (select != 5) {
            cout << "1. Crear un arbol binario e ingresar nodos" << endl;
            cout << "2. Mostrar el arbol binario" << endl;
            cout << "3. Volver al menu principal" << endl;
            cin >> select;

            while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
                cout << "Ingrese una opcion valida: ";
                cin >> select;
            }

            switch (select) {
            case 1:
                insertarArbol();
                break;
            case 2:
                cout << "Arbol in-order:" << endl;
                mostrarInOrden();
                cout << "Arbol post-order" << endl;
                mostrarPostOrder();
                cout << "Arbol pre-order" << endl;
                mostrarPreOrder();
                break;
            case 3:
                return;
            default:
                cout << "Opcion ingresada no valida" << endl;
            }
        }
    }
};

// Definicion de la clase ArbolBB para representar el arbol binario de busqueda
template<typename T>
class ArbolBB {
private:
    Nodo<T>* raiz; // Puntero a la raiz del arbol

    // Funcion privada para destruir el arbol recursivamente
    void destroyTree(Nodo<T>* nodo) {
        if (nodo) {
            destroyTree(nodo->izquierda);
            destroyTree(nodo->derecha);
            delete nodo;
        }
    }

    // Funciones privadas para realizar los recorridos recursivamente
    void preOrderTraversal(Nodo<T>* nodo) {
        if (nodo) {
            cout << nodo->dato << " ";      // Visita el nodo
            preOrderTraversal(nodo->izquierda);  // Recorre el hijo izquierdo
            preOrderTraversal(nodo->derecha); // Recorre el hijo derecho
        }
    }

    void inOrderTraversal(Nodo<T>* nodo) {
        if (nodo) {
            inOrderTraversal(nodo->izquierda);   // Recorre el hijo izquierdo
            cout << nodo->dato << " ";      // Visita el nodo
            inOrderTraversal(nodo->derecha);  // Recorre el hijo derecho
        }
    }

    void postOrderTraversal(Nodo<T>* nodo) {
        if (nodo) {
            postOrderTraversal(nodo->izquierda); // Recorre el hijo izquierdo
            postOrderTraversal(nodo->derecha);// Recorre el hijo derecho
            cout << nodo->dato << " ";      // Visita el nodo
        }
    }

    // Funci�n privada para insertar un valor en el arbol recursivamente
    Nodo<T>* insertNode(Nodo<T>* nodo, T valor) {
        if (!nodo) {
            nodo = new Nodo<T>(valor); // Crea un nuevo nodo con el valor dado
        }
        else {
            if (valor < nodo->dato) {
                nodo->izquierda = insertNode(nodo->izquierda, valor); // Inserta en el sub�rbol izquierdo
            }
            else {
                nodo->derecha = insertNode(nodo->derecha, valor); // Inserta en el sub�rbol derecho
            }
        }
        return nodo;
    }

public:
    // Constructor que inicializa la raiz del arbol como nula
    ArbolBB() : raiz(nullptr) {}

    // Destructor que destruye el �rbol llamando a la funcion privada destroyTree
    ~ArbolBB() {
        destroyTree(raiz);
    }

    // Funcion publica para insertar un valor en el arbol
    void insert(T value) {
        raiz = insertNode(raiz, value);
    }

    // Funciones publicas para mostrar los recorridos del arbol
    void preOrder() {
        cout << "Pre-order: ";
        preOrderTraversal(raiz);
        cout << endl;
    }

    void inOrder() {
        cout << "In-order: ";
        inOrderTraversal(raiz);
        cout << endl;
    }

    void postOrder() {
        cout << "Post-order: ";
        postOrderTraversal(raiz);
        cout << endl;
    }

    void menuBB()
    {
        int opcion = 0, cantidad = 0;
        while (opcion != 3)
        {
            cout << "Menu de opciones: " << endl;
            cout << "1. Insertar un elemento " << endl;
            cout << "2. Mostrar arbol  " << endl;
            cout << "3. Salir " << endl;
            cout << "Ingrese opcion deseada: ";
            cin >> opcion;
            
            while (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Ingrese un numero: ";
				cin >> opcion;
			}
            //Variables case 1
            int numero;
            switch (opcion) {
                case 1:
                    cout << "Cuantos elementos desea ingresar: ";
                    cin >> cantidad;
                    for (int i = 0; i < cantidad; i++) {
                        cout << "ingresar el valor " << i + 1 << endl;
                        cin >> numero;
                        insert(numero);
                    }
                    break;
                case 2:
                    cout << "Arbol In-Order:  " << endl;
                    inOrder();
                    cout << "Arbol Pre-Order: " << endl;
                    preOrder();
                    cout << "Arbol Post-Order: " << endl;
                    postOrder();
                    break;
                case 3:
                    opcion = 3;
                    break;
                default:
                    cout << "Opcion no valida " << endl;
                    break;
            }            
        }
    }

}
;
// Se crea clase ArbolAVL para crear el arbol AVL
template<typename T>
class ArbolAVL {
private:

    // Se crea un puntero a la raiz del arbol
    Nodo<T>* raiz;

    // Funcion para obtener altura del arbol
    int obtenerAltura(Nodo<T>* nodo) {
        if (nodo == nullptr)
            return 0; // Devuelve 0 si se cumple la condicion del if
        return nodo->altura; // Devuelve la altura del arbol 
    }

    // Funcion para obtener balance del arbol 
    int obtenerBalance(Nodo<T>* nodo) {
        if (nodo == nullptr)
            return 0; // Devuelve 0 si se cumple la condicion del if
        return obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha); // Devuelve la resta entre los dos subarboles derecho e izquierdo
    }

    // Funcion para rotar a la derecha si el arbol esta desequilibrado
    Nodo<T>* rotarDerecha(Nodo<T>* y) {
        // El nodo x toma el valor del hijo izquierdo de y
        Nodo<T>* x = y->izquierda;
        // El nodo T2 toma el valor del hijo derecho de x 
        Nodo<T>* T2 = x->derecha;

        // El hijo derecho de x toma el valor de y
        x->derecha = y;
        // El hijo izquierdo de y toma el valor de T2
        y->izquierda = T2;

        // Se actualiza la altura de los nodos
        y->altura = std::max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
        x->altura = std::max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;

        return x;
    }

    // Funcion para rotar el arbol a la izquierda si esta desblanceado
    Nodo<T>* rotarIzquierda(Nodo<T>* x) {
        // Crea un nuevo nodo cuyo valor es igual al subarbol derecho del arbol x
        Nodo<T>* y = x->derecha;
        // Crea un nuevo nodo T2 cuyo valor es igual al subarbol izquierdo del arbol y
        Nodo<T>* T2 = y->izquierda;

        // Actualiza el subarbol izquierdo del arbol y, y lo iguala al arbol x
        y->izquierda = x;
        // Actualiza el subarbol derecho del arbol x y lo iguala al arbol T2
        x->derecha = T2;

        // Actualiza la altura del arbol x
        x->altura = std::max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
        // Actualiza la altura del arbol y
        y->altura = std::max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;

        //devuelve el arbol y
        return y;
    }

    // Funcion para insertar un nodo en el arbol
    Nodo<T>* insertar(Nodo<T>* nodo, T valor) {
        // Si el arbol esta vacio, se crea el nodo raiz
        if (nodo == nullptr)
            return(new Nodo<T>(valor));


        // Si el valor es menor al valor del nodo, se inserta en el subarbol izquierdo
        if (valor < nodo->dato)
            nodo->izquierda = insertar(nodo->izquierda, valor);

        // Si el valor es mayor al valor del nodo, se inserta en el subarbol derecho
        else if (valor > nodo->dato)
            nodo->derecha = insertar(nodo->derecha, valor);

        // Si el valor es igual al valor del nodo, se retorna el nodo
        else
            return nodo;
        
        // Se actuliza la altura del arbol 
        nodo->altura = 1 + std::max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));


        // Se crea variable que se le asigna el balance del arbol 
        int balance = obtenerBalance(nodo);


        // Si el arbol esta desbalanceado, se realizan las rotaciones correspondientes
        if (balance > 1 && valor < nodo->izquierda->dato)
            return rotarDerecha(nodo);
        if (balance < -1 && valor > nodo->derecha->dato)
            return rotarIzquierda(nodo);
        if (balance > 1 && valor > nodo->izquierda->dato)
            nodo->izquierda = rotarIzquierda(nodo->izquierda);

        if (balance > 1 && valor < nodo->izquierda->dato)
            return rotarDerecha(nodo);
        if (balance < -1 && valor > nodo->derecha->dato)
            return rotarIzquierda(nodo);
        if (balance > 1 && valor > nodo->izquierda->dato) {
            nodo->izquierda = rotarIzquierda(nodo->izquierda);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && valor < nodo->derecha->dato) {
            nodo->derecha = rotarDerecha(nodo->derecha);
            return rotarIzquierda(nodo);
        }
        return nodo;
    }

    // Funcion para mostrar los elementos de un arbol en orden
    void inOrden(Nodo<T>* nodo) {
        if (nodo != nullptr) {
            inOrden(nodo->izquierda);
            std::cout << nodo->dato << " ";
            inOrden(nodo->derecha);
        }
    }

    //funcion para mostrar post-order
    void postOrden(Nodo<T>* nodo) {
        if (nodo != nullptr) {
            postOrden(nodo->izquierda);
            postOrden(nodo->derecha);
            std::cout << nodo->dato << " ";
        }
    }

    //Funcion para mostrar los elementos pre-order
    void preOrden(Nodo<T>* nodo) {
        if (nodo != nullptr) {
            std::cout << nodo->dato << " ";
            preOrden(nodo->izquierda);
            preOrden(nodo->derecha);
        }
    }
public:
    ArbolAVL() : raiz(nullptr) {}

    // Funcion para insertar un nuevo valor al arbol
    void insertar(T valor) {
        raiz = insertar(raiz, valor);
    }

    //funcio para mostrar in-order
    void mostrarInOrden() {
        inOrden(raiz);
        cout << endl;
    }

    // Funcion para mostrar post-order
    void mostrarPostOrden() {
        postOrden(raiz);
        cout << endl;
    }

    // Funcion para mostrar pre-order
    void mostrarPreOrden() {
        preOrden(raiz);
        cout << endl;
    }

    // Funcion menu del arbol AVL
    void menuArbolAVL(){
        int selector = 0, cantidad = 0, dato=0;
        while (selector != 3) {
            cout << "1. insertar datos" << endl;
            cout << "2. mostrar arbol" << endl;
            cout << "3. Para salir" << endl;
            cin >>selector;

			// Manejo de errores select
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
				cout << "Ingrese una opcion valida: ";
				cin >> selector;
			}

            switch(selector){
            case 1:
                {
                    cout << "cuantos nodos desea ingresar" << endl;
                    cin >> cantidad;
                    for (int i = 0; i <= cantidad; i++) {
                        cout << "ingrese un dato" << endl;
                        cin >> dato;
                        insertar(dato);
                    }
                }
                break;
            case 2:
            {
                cout << "Arbol In-Order: " << endl;
                mostrarInOrden();
                cout << "Arbol Post-Order" << endl;
                mostrarPostOrden();
                cout << "Arbol Pre-Order" << endl;
                mostrarPreOrden();
            }
                break;
            case 3:
                {
                selector = 3;
                }
                break;
            }

        }
    }

};

enum Color { ROJO, NEGRO };

// Se crea clase NodoRN para ARN
template <typename T>
class NodoRN {
public:
	T clave;
	Color color;
	NodoRN* izquierda;
	NodoRN* derecha;
	NodoRN* padre;

	NodoRN(T clave) : clave(clave), color(ROJO), izquierda(nullptr), derecha(nullptr), padre(nullptr) {}
};

template <typename T>
class ArbolRojoNegro {
private:
	NodoRN<T>* raiz;

	void rotacionIzquierda(NodoRN<T>* x);
	void rotacionDerecha(NodoRN<T>* y);
	void arreglarInsercion(NodoRN<T>* z);
	void arreglarBorrado(NodoRN<T>* x);
	void transplantar(NodoRN<T>* u, NodoRN<T>* v);
	NodoRN<T>* minValorNodo(NodoRN<T>* nodo);
	void imprimirHelper(NodoRN<T>* nodo, std::string indent, bool ultimo) const;

public:
	ArbolRojoNegro() : raiz(nullptr) {}
	void insertar(const T& clave);
	void borrar(const T& clave);
	void inOrden() const;
	void inOrden(NodoRN<T>* nodo) const;
	void imprimir() const;
    void menuARN() const;
};

// Funcion para hacer rotacion izquierda
template <typename T>
void ArbolRojoNegro<T>::rotacionIzquierda(NodoRN<T>* x) {
	NodoRN<T>* y = x->derecha;
	x->derecha = y->izquierda;
	if (y->izquierda != nullptr) y->izquierda->padre = x;
	y->padre = x->padre;
	if (x->padre == nullptr) raiz = y;
	else if (x == x->padre->izquierda) x->padre->izquierda = y;
	else x->padre->derecha = y;
	y->izquierda = x;
	x->padre = y;
}

// Funcion para hacer rotacion derecha
template <typename T>
void ArbolRojoNegro<T>::rotacionDerecha(NodoRN<T>* y) {
	NodoRN<T>* x = y->izquierda;
	y->izquierda = x->derecha;
	if (x->derecha != nullptr) x->derecha->padre = y;
	x->padre = y->padre;
	if (y->padre == nullptr) raiz = x;
	else if (y == y->padre->derecha) y->padre->derecha = x;
	else y->padre->izquierda = x;
	x->derecha = y;
	y->padre = x;
}

// Funcion para arreglar insercion
template <typename T>
void ArbolRojoNegro<T>::arreglarInsercion(NodoRN<T>* z) {
	while (z->padre && z->padre->color == ROJO) {
		if (z->padre == z->padre->padre->izquierda) {
			NodoRN<T>* y = z->padre->padre->derecha;
			if (y && y->color == ROJO) {
				z->padre->color = NEGRO;
				y->color = NEGRO;
				z->padre->padre->color = ROJO;
				z = z->padre->padre;
			}
			else {
				if (z == z->padre->derecha) {
					z = z->padre;
					rotacionIzquierda(z);
				}
				z->padre->color = NEGRO;
				z->padre->padre->color = ROJO;
				rotacionDerecha(z->padre->padre);
			}
		}
		else {
			NodoRN<T>* y = z->padre->padre->izquierda;
			if (y && y->color == ROJO) {
				z->padre->color = NEGRO;
				y->color = NEGRO;
				z->padre->padre->color = ROJO;
				z = z->padre->padre;
			}
			else {
				if (z == z->padre->izquierda) {
					z = z->padre;
					rotacionDerecha(z);
				}
				z->padre->color = NEGRO;
				z->padre->padre->color = ROJO;
				rotacionIzquierda(z->padre->padre);
			}
		}
	}
	raiz->color = NEGRO;
}

// Funcion para hacer insertar
template <typename T>
void ArbolRojoNegro<T>::insertar(const T& clave) {
	NodoRN<T>* z = new NodoRN<T>(clave);
	NodoRN<T>* y = nullptr;
	NodoRN<T>* x = raiz;

	while (x != nullptr) {
		y = x;
		if (z->clave < x->clave) x = x->izquierda;
		else x = x->derecha;
	}

	z->padre = y;
	if (y == nullptr) raiz = z;
	else if (z->clave < y->clave) y->izquierda = z;
	else y->derecha = z;

	z->color = ROJO;
	arreglarInsercion(z);
}

template <typename T>
NodoRN<T>* ArbolRojoNegro<T>::minValorNodo(NodoRN<T>* nodo) {
	while (nodo->izquierda != nullptr) nodo = nodo->izquierda;
	return nodo;
}

template <typename T>
void ArbolRojoNegro<T>::transplantar(NodoRN<T>* u, NodoRN<T>* v) {
	if (u->padre == nullptr) raiz = v;
	else if (u == u->padre->izquierda) u->padre->izquierda = v;
	else u->padre->derecha = v;
	if (v != nullptr) v->padre = u->padre;
}

template <typename T>
void ArbolRojoNegro<T>::arreglarBorrado(NodoRN<T>* x) {
	while (x != raiz && (!x || x->color == NEGRO)) {
		if (x == x->padre->izquierda) {
			NodoRN<T>* w = x->padre->derecha;
			if (w->color == ROJO) {
				w->color = NEGRO;
				x->padre->color = ROJO;
				rotacionIzquierda(x->padre);
				w = x->padre->derecha;
			}
			if ((!w->izquierda || w->izquierda->color == NEGRO) &&
				(!w->derecha || w->derecha->color == NEGRO)) {
				w->color = ROJO;
				x = x->padre;
			}
			else {
				if (!w->derecha || w->derecha->color == NEGRO) {
					if (w->izquierda) w->izquierda->color = NEGRO;
					w->color = ROJO;
					rotacionDerecha(w);
					w = x->padre->derecha;
				}
				w->color = x->padre->color;
				x->padre->color = NEGRO;
				if (w->derecha) w->derecha->color = NEGRO;
				rotacionIzquierda(x->padre);
				x = raiz;
			}
		}
		else {
			NodoRN<T>* w = x->padre->izquierda;
			if (w->color == ROJO) {
				w->color = NEGRO;
				x->padre->color = ROJO;
				rotacionDerecha(x->padre);
				w = x->padre->izquierda;
			}
			if ((!w->derecha || w->derecha->color == NEGRO) &&
				(!w->izquierda || w->izquierda->color == NEGRO)) {
				w->color = ROJO;
				x = x->padre;
			}
			else {
				if (!w->izquierda || w->izquierda->color == NEGRO) {
					if (w->derecha) w->derecha->color = NEGRO;
					w->color = ROJO;
					rotacionIzquierda(w);
					w = x->padre->izquierda;
				}
				w->color = x->padre->color;
				x->padre->color = NEGRO;
				if (w->izquierda) w->izquierda->color = NEGRO;
				rotacionDerecha(x->padre);
				x = raiz;
			}
		}
	}
	if (x) x->color = NEGRO;
}

template <typename T>
void ArbolRojoNegro<T>::borrar(const T& clave) {
	NodoRN<T>* z = raiz;
	while (z != nullptr && z->clave != clave) {
		if (clave < z->clave) z = z->izquierda;
		else z = z->derecha;
	}

	if (z == nullptr) return;

	NodoRN<T>* y = z;
	NodoRN<T>* x = nullptr;
	Color yOriginalColor = y->color;

	if (z->izquierda == nullptr) {
		x = z->derecha;
		transplantar(z, z->derecha);
	}
	else if (z->derecha == nullptr) {
		x = z->izquierda;
		transplantar(z, z->izquierda);
	}
	else {
		y = minValorNodo(z->derecha);
		yOriginalColor = y->color;
		x = y->derecha;
		if (y->padre != z) {
			transplantar(y, y->derecha);
			y->derecha = z->derecha;
			y->derecha->padre = y;
		}
		transplantar(z, y);
		y->izquierda = z->izquierda;
		y->izquierda->padre = y;
		y->color = z->color;
	}

	delete z;

	if (yOriginalColor == NEGRO) arreglarBorrado(x);
}

template <typename T>
void ArbolRojoNegro<T>::inOrden() const {
	inOrden(raiz);
	cout << endl;
}

template <typename T>
void ArbolRojoNegro<T>::inOrden(NodoRN<T>* nodo) const {
	if (nodo != nullptr) {
		inOrden(nodo->izquierda);
		cout << nodo->clave << " ";
		inOrden(nodo->derecha);
	}
}

template <typename T>
void ArbolRojoNegro<T>::imprimir() const {
	if (raiz) imprimirHelper(raiz, "", true);
}

template <typename T>
void ArbolRojoNegro<T>::imprimirHelper(NodoRN<T>* nodo, std::string indent, bool ultimo) const {
	if (nodo != nullptr) {
		cout << indent;
		if (ultimo) {
			cout << "R----";
			indent += "   ";
		}
		else {
			cout << "L----";
			indent += "|  ";
		}

		string sColor = (nodo->color == ROJO) ? "\033[31mROJO\033[0m" : "NEGRO";  // \033[31m para rojo, \033[0m para resetear
		cout << nodo->clave << "(" << sColor << ")" << std::endl;
		imprimirHelper(nodo->izquierda, indent, false);
		imprimirHelper(nodo->derecha, indent, true);
	}
}

int main() {
    ArbolAVL<int> arbolVL;
    ArbolBB<int> arbolBB;
    ArbolB<int> arbolB;
    ArbolRojoNegro<int> arbolRN;
    //ArbolARN<int> arbolRN;

    // Variables para menu ARN
    int selector = 0, cantidad = 0, dato = 0;
    
    // Menu de opciones 
    int select = 0;
    while (select != 5) {
        cout << "Ingrese: " << endl;
        cout << "1. Para utilizar arboles binarios" << endl;
        cout << "2. Para utilizar arboles binarios de busqueda" << endl;
        cout << "3. Para utilizar arboles AVL" << endl;
        cout << "4. Para utilizar arboles ARN" << endl;
        cout << "5. Salir " << endl;
        cin >> select;

        // Manejo de errores select
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
            cout << "Ingrese una opcion valida: ";
            cin >> select;
        }

        switch (select) {
        case 1:
            arbolB.menuBinarios();
            break;
        case 2:
            arbolBB.menuBB();
            break;
        case 3:
            arbolVL.menuArbolAVL();
            break;
        case 4:
            // Menu de arbol ARN
            while (selector != 3) {
                cout << "1. Crear arbol e insertar nodos" << endl;
                cout << "2. Mostrar arbol" << endl;
                cout << "3. Eliminar un nodo" << endl;
                cout << "4. Salir al menu principal" << endl;
                cin >> selector;

                // Manejo de errores select
                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
                    cout << "Ingrese una opcion valida: ";
                    cin >> selector;
                }

                switch (selector) {
                case 1:
                {
                    cout << "Cuantos nodos desea ingresar" << endl;
                    cin >> cantidad;
                    for (int i = 0; i < cantidad; i++) {
                        cout << "ingrese un dato" << endl;
                        cin >> dato;
                        arbolRN.insertar(dato);
                    }
                }
                break;
                case 2:
                {
                    cout << "El arbol final es: " << endl;
                    arbolRN.imprimir();
                    cout << endl << "In-Order: " << endl;
                    arbolRN.inOrden();
                }
                break;
                case 3: 
					cout << "Ingrese el nodo que desea eliminar (solo se pueden eliminar las hojas): ";
					cin >> dato;
					arbolRN.borrar(dato);
                break;
                case 4:
                    return 0;
                default:
                    cout << "Opcion no valida" << endl;
					break;
                }
            }

            break;
        case 5:
            return 0;
        default:
            cout << "Opcion incorrecta" << endl;
            break;
        }

        system("pause");
        system("cls");
    }
    return 0;
}