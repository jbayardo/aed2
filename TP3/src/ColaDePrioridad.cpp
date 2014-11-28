#include "ColaDePrioridad.h"
#include "aed2/Lista.h"
#include <assert.h>

/*
* TODO: escribir tests. verificar que bajar esta bien.
*/

template <typename T>
ColaDePrioridad<T>::Nodo::Nodo(const Nodo &otro) {
    this->izq = new Nodo(otro.izq);
    this->der = new Nodo(otro.der);
    this->dato = otro.dato;
    this->izq->arr = this;
    this->der->arr = this;
}

template<typename T>
ColaDePrioridad<T>::ColaDePrioridad(const ColaDePrioridad<T> &otra) {
    this->cabeza = nullptr;
    this->ultimo = nullptr;
    this->_tamano = 0;

    if (otra.Tamano() > 0) {
        this->cabeza = new Nodo(otra.cabeza);
        this->_tamano = otra._tamano;

        this->ultimo = this->cabeza;
        aed2::Nat camino = this->Tamano();

        while (camino > 1) {
            if (camino % 2 == 0) {
                this->ultimo = this->ultimo->izq;
            } else {
                this->ultimo = this->ultimo->der;
            }

            camino = camino / 2;
        }
    }
}

template <typename T>
ColaDePrioridad<T>::~ColaDePrioridad() {
    if (Tamano() > 0) {
        aed2::Lista<Nodo*> pila;
        pila.AgregarAtras(this->cabeza);
        
        while (!pila.EsVacia()) {
            Nodo *actual = pila.Primero();
            pila.Fin();

            if (actual->izq != nullptr) {
                pila.AgregarAtras(actual->izq);
            }

            if (actual->der != nullptr) {
                pila.AgregarAtras(actual->der);
            }

            delete actual;
        }
    }
}

template <typename T>
typename Iterador ColaDePrioridad<T>::Encolar(const T &dato) {
    Nodo *tmp = new Nodo(dato);

    if (this->Tamano() == 0) {
        this->cabeza = tmp;
    } else if (this->Tamano() == 1) {
        tmp->arr = this->cabeza;
        this->cabeza->izq = tmp;
    } else {
        if (this->ultimo->arr->izq == this->ultimo) {
            tmp->arr = this->ultimo->arr;
            this->ultimo->arr->der = tmp;
        } else {
            Nodo *actual = this->ultimo;

            while (actual->arr != nullptr && actual->arr->izq != actual) {
                actual = actual->arr;
            }

            if (actual->arr != nullptr) {
                actual = actual->arr->der;
            }

            while (actual->izq != nullptr) {
                actual = actual->izq;
            }

            tmp->arr = actual;
            actual->izq = tmp;
        }
    }

    this->ultimo = tmp;
    ++this->_tamano;

    Subir(this->ultimo);
    return Iterador(this, this->ultimo);
}

template <typename T>
const T &ColaDePrioridad<T>::Desencolar() {
    return Eliminar(this->cabeza);
}

template <typename T>
const T &ColaDePrioridad<T>::Desencolar(const ColaDePrioridad<T>::Iterador &i) {
    assert(i.heap == this);

    return Eliminar(i.nodo);
}

template <typename T>
void ColaDePrioridad<T>::Subir(Nodo *node) {
    while (node->arr != nullptr && node->arr->dato < node->dato) {
        T tmp = node->arr->dato;
        node->arr->dato = node->dato;
        node->dato = tmp;
        node = node->arr;
    }
}

template <typename T>
void ColaDePrioridad<T>::Bajar(Nodo *node) {							//Checkear Correccion en el TP
    while ((node->izq != nullptr && node->dato < node->izq->dato) ||
        (node->der != nullptr && node->dato < node->der->dato)) {
        if (node->izq != nullptr) {
            T tmp = node->izq->dato;
            node->izq->dato = node->dato;
            node->dato = tmp;
            node = node->izq;
        } else {
            T tmp = node->der->dato;
            node->der->dato = node->dato;
            node->dato = tmp;
            node = node->der;
        }
    }
}


template <typename T>
const T &ColaDePrioridad<T>::Eliminar(Nodo *node) {
    // Pre: node esta en la estructura
    const T &tmp = node->dato;

    if (this->Tamano() == 1) {
        delete this->cabeza;
        this->ultimo = nullptr;
        this->cabeza = nullptr;
    } else {
        node->dato = this->ultimo->dato;
        Nodo *backup = this->ultimo;

        if (this->ultimo->arr->izq == this->ultimo) {
            Nodo *actual = this->ultimo;

            while (actual->arr != nullptr && actual->arr->der != actual) {
                actual = actual->arr;
            }

            if (actual->arr != nullptr) {
                actual = actual->arr->izq;
            }

            while (actual->der != nullptr) {
                actual = actual->der;
            }

            this->ultimo->arr->izq = nullptr;
            this->ultimo = actual;
        } else {
            this->ultimo = this->ultimo->arr->izq;
            this->ultimo->arr->der = nullptr;
        }

        if (node->dato < node->arr->dato) {
            Bajar(node);
        } else {
            Subir(node);
        }

        delete backup;
    }

    --this->_tamano;

    return tmp;
}

template <typename T>
unsigned int ColaDePrioridad<T>::Tamano() const {
    return this->_tamano;
}
