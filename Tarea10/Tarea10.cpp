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
            throw out_of_range("Intento de dequeue en cola vac�a");
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
        for (int i = 0; i <= cantidadNodos; i = i + 2) {

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
                cout << "El arbol final es: " << endl;
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
                cout << "Ingrese una opcion valida" << endl;
                system("pause");
                system("cls");
                break;
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
    void mostrarPreOrden() {
        preOrderTraversal(raiz);
        cout << endl;
    }

    void mostrarInOrden() {
        inOrderTraversal(raiz);
        cout << endl;
    }

    void mostrarPostOrden() {
        postOrderTraversal(raiz);
        cout << endl;
    }

    void menuBB()
    {
        int opcion = 0, cantidad = 0;
        while (opcion != 3)
        {
            cout << "1. Crear un arbol e ingresar nodos" << endl;
            cout << "2. Mostrar el arbol" << endl;
            cout << "3. Volver al menu principal" << endl;
            cin >> opcion;

            while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ingrese una opcion valida: ";
                cin >> opcion;
            }
            //Variables case 1
            int numero;
            switch (opcion) {
            case 1:
                cout << "Ingrese cuantos nodos desea insertar: ";
                cin >> cantidad;
                for (int i = 0; i < cantidad; i++) {
                    cout << "Ingrese nodo " << i + 1 << endl;
                    cin >> numero;
                    insert(numero);
                }
                break;
            case 2:
                cout << "El arbol final es: " << endl;
                cout << "Arbol in-order:" << endl;
                mostrarInOrden();
                cout << "Arbol post-order:" << endl;
                mostrarPostOrden();
                cout << "Arbol pre-order:" << endl;
                mostrarPreOrden();
                break;
            case 3:
                opcion = 3;
                break;
            default:
                cout << "Ingrese una opcion valida" << endl;
                system("pause");
                system("cls");
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
        y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
        x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;

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
        x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
        // Actualiza la altura del arbol y
        y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;

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
        nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));


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
    void menuArbolAVL() {
        int selector = 0, cantidad = 0, dato = 0;
        while (selector != 3) {
            cout << "1. Crear un arbol e ingresar nodos" << endl;
            cout << "2. Mostrar el arbol" << endl;
            cout << "3. Volver al menu principal" << endl;
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
                cout << "Ingrese cuantos nodos desea insertar: " << endl;
                cin >> cantidad;
                for (int i = 0; i < cantidad; i++) {
                    cout << "Ingrese nodo " << i + 1 << endl;
                    cin >> dato;
                    insertar(dato);
                }
            }
            break;
            case 2:
            {
                cout << "El arbol final es: " << endl;
                cout << "Arbol in-order:" << endl;
                mostrarInOrden();
                cout << "Arbol post-order:" << endl;
                mostrarPostOrden();
                cout << "Arbol pre-order:" << endl;
                mostrarPreOrden();
            }
            break;
            case 3:
            {
                selector = 3;
            }
            break;
            default:
                cout << "Ingrese una opcion valida: " << endl;
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

    // Funcion para hacer rotacion izquierda
    void rotacionIzquierda(NodoRN<T>* x) {
        // Se crea un nuevo nodo y se lo iguala al nodo que esta a la derecha de x
        NodoRN<T>* y = x->derecha;
        //Le asigna al nodo a la derecha de x el valor del nodo a la izquierda de y
        x->derecha = y->izquierda;
        //Si el nodo que esta a la izquierda de y es nulo, le asigana al padre del nodo izqueirdo de y el valor de x
        if (y->izquierda != nullptr) y->izquierda->padre = x;
        // Le asigna al padre de y el valor del padre de x        
        y->padre = x->padre;
        //Si el padre de x es nulo le asigna al puntero raiz el valor de y
        if (x->padre == nullptr) raiz = y;
        // Si el padre de x no es nulo pero x es igual al padre a la izquerda de x, le asigna al padre a la izquierda de x el valor de y
        else if (x == x->padre->izquierda) x->padre->izquierda = y;
        // si no se cumplen las condiciones anteriores, le da el valor de y al padre a la drecha de x
        else x->padre->derecha = y;
        // Iguala el puntero izquierda de y a x
        y->izquierda = x;
        // Iguala el padre de x a y
        x->padre = y;
    }
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

// Funcion para hacer rotacion derecha
template <typename T>
void ArbolRojoNegro<T>::rotacionDerecha(NodoRN<T>* y) {
    // Crea el al nodo x y le da el valor del hijo izquierdo de y
    NodoRN<T>* x = y->izquierda;
    // Modifica el valor del hijo izquierdo de y con elvalor del hijo derecho de x
    y->izquierda = x->derecha;
    // Si el hijo derecho de x existe, elpadre del hijo derecho de x toma el valor de y
    if (x->derecha != nullptr) x->derecha->padre = y;
    // El padre de x toma el valor del padre de y
    x->padre = y->padre;
    // Si el padre de y existe, la raiz toma el valor de x
    if (y->padre == nullptr) raiz = x;
    // Si no si y es igual al padre el hijo derecho de y entonces el hijo derecho del padre de y toma el valor de x
    else if (y == y->padre->derecha) y->padre->derecha = x;
    // Sino el hijo izquierdo del padre de y toma el  valor de x
    else y->padre->izquierda = x;
    // El hijo derecho de x toma el valor de y
    x->derecha = y;
    // El padre de y toma el valor de x
    y->padre = x;
}

// Funcion para arreglar insercion
template <typename T>
void ArbolRojoNegro<T>::arreglarInsercion(NodoRN<T>* z) {
    // Mientras z padre existe y el color de z padre es rojo 
    while (z->padre && z->padre->color == ROJO) {
        // SI z padre es igual al abuelo izquierdo de z 
        if (z->padre == z->padre->padre->izquierda) {
            // Se asigna un y que es el abuelo derecho de z
            NodoRN<T>* y = z->padre->padre->derecha;
            // Si y existe y su color es rojo 
            if (y && y->color == ROJO) {
                // Se asigna como negro al color del padre de z
                z->padre->color = NEGRO;
                // Se asigna como negro al color de y 
                y->color = NEGRO;
                // Se asigna como rojo al color del aabuelo de z
                z->padre->padre->color = ROJO;
                // El abuelo de z pasa a ser z
                z = z->padre->padre;
            }
            else {
                // Si z es igual al su padre derecho 
                if (z == z->padre->derecha) {
                    // Se asigna a z a su padre 
                    z = z->padre;
                    // Se produe rotacion izquierda
                    rotacionIzquierda(z);
                }
                // Se asigna como negro al color del padre de z
                z->padre->color = NEGRO;
                // Se asigna como negro al color del abuelo de z
                z->padre->padre->color = ROJO;
                // Se produce rotacion derecha 
                rotacionDerecha(z->padre->padre);
            }
        }
        else {
            // y es igual al abuelo de izquierdo de z 
            NodoRN<T>* y = z->padre->padre->izquierda;
            // si y existe y el color de y es rojo
            if (y && y->color == ROJO) {
                // Se le asigna como color negro al padre de z o
                z->padre->color = NEGRO;
                // Se le asigna como negro al color de y
                y->color = NEGRO;
                // Se le asigno como rojo al color del abuelo de z
                z->padre->padre->color = ROJO;
                // Se le asigna a z como el abuelo de z
                z = z->padre->padre;
            }
            else {
                // Si z es igual a su padre de izquierda
                if (z == z->padre->izquierda) {
                    // z es igual a su padre 
                    z = z->padre;
                    // Se produce rotacion derecha 
                    rotacionDerecha(z);
                }
                // Se le asigna como negro al color del padre de z 
                z->padre->color = NEGRO;
                // Se le asigna como rojo al color del abuelo de z
                z->padre->padre->color = ROJO;
                // Se produce rotacion izquierda
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

    // Recorre el arbol hasta llegar al final
    while (x != nullptr) {
        // Almacena x en y, para luego reasignar el nodo padre 
        y = x;
        // Verifica en que posicion debe insertarse el nodo segunr el tamano de clave, luego lo isnerta
        if (z->clave < x->clave) x = x->izquierda;
        else x = x->derecha;
    }
    // z padre es igual a y
    // se da a z->padre el valor de y, que contiene el valor anterior de x, es decir, el padre de z
    z->padre = y;
    // Si arbol vacio, entonces z raiz
    if (y == nullptr) raiz = z;
    // Si no esta vacio, se verifica la clave de z para insertarlo correctamente en y
    else if (z->clave < y->clave) y->izquierda = z;
    else y->derecha = z;

    z->color = ROJO;
    arreglarInsercion(z);
}

// Funcion para encontrar el valor de mas nivel de un nodo
template <typename T>
NodoRN<T>* ArbolRojoNegro<T>::minValorNodo(NodoRN<T>* nodo) {
    //Mientras el hijo izquierdo no sea nulo el nodo va a tomar el valor de su hijo
    while (nodo->izquierda != nullptr) nodo = nodo->izquierda;
    //cuando el hijo izquierdo del nodo ya sea nulo retorna el nodo
    return nodo;
}

// Funcion para transplantar nodos 
template <typename T>
void ArbolRojoNegro<T>::transplantar(NodoRN<T>* u, NodoRN<T>* v) {
    // Si el padre de u es nullo, raiz es igual a v
    if (u->padre == nullptr) raiz = v;
    // Si u es igual a u padre izquierda, u padre izquierda es igual a v
    else if (u == u->padre->izquierda) u->padre->izquierda = v;
    // else, u padre derecha ees igual a v
    else u->padre->derecha = v;
    // Si v es nulo, v padre y igual a u padre 
    if (v != nullptr) v->padre = u->padre;
}

// Funcion para hacer recorrido inOrder// Funcion para mostrar los valorres 
template <typename T>
void ArbolRojoNegro<T>::inOrden() const {
    inOrden(raiz);
    cout << endl;
}

// Funcion para imprimir los elementos in-order 
template <typename T>
void ArbolRojoNegro<T>::inOrden(NodoRN<T>* nodo) const {
    // Si nodo es distinto de nulo
    if (nodo != nullptr) {
        // Funcion in-order nodo izquierdo
        inOrden(nodo->izquierda);
        cout << nodo->clave << " ";
        // Funcion in-order nodo derecha
        inOrden(nodo->derecha);
    }
}

// Funcion para imprimir los elementos 
template <typename T>
void ArbolRojoNegro<T>::imprimir() const {
    if (raiz) imprimirHelper(raiz, "", true);
}

template <typename T>
void ArbolRojoNegro<T>::imprimirHelper(NodoRN<T>* nodo, string indent, bool ultimo) const {
    // Si nodo es distinto de nulo    // Si ultimo es true, muestra R---- y concatena dos espacios a indent
    if (nodo != nullptr) {
        cout << indent;

        if (ultimo) {
            cout << "R----";
            indent += "   ";
        }
        // Si no se cumple la condicion anterior muestra L---- y le concatena | y dos espacios a indent
        else {
            cout << "L----";
            indent += "|  ";
        }
        // Creacion de una variable string que es iguala al color de nodo, el cual es rojo, si "\033[31mROJO\033[0m" : "NEGRO"
        string sColor = (nodo->color == ROJO) ? "\033[31mROJO\033[0m" : "NEGRO";  // \033[31m para rojo, \033[0m para resetear
        // muestra el dato sumado al color almacenado en la variable sColor
        cout << nodo->clave << "(" << sColor << ")" << std::endl;
        // Se llama recursivamente tomando como parametros el valor a la izquierda de nodo, ident y ultimo 
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
                cout << "1. Crear un arbol e ingresar nodos" << endl;
                cout << "2. Mostrar el arbol" << endl;
                cout << "3. Volver al menu principal" << endl;
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
                    cout << "Ingrese cuantos nodos desea insertar: " << endl;
                    cin >> cantidad;
                    for (int i = 0; i < cantidad; i++) {
                        cout << "Ingrese nodo " << i + 1 << endl;
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
                    break;
                default:
                    cout << "Ingrese una opcion valida" << endl;
                    system("pause");
                    system("cls");
                    break;
                }
            }

            break;
        case 5:
            return 0;
        default:
            cout << "Ingrese una opcion valida" << endl;
            break;
        }

        system("pause");
        system("cls");
    }
    return 0;
}