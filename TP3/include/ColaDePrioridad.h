#ifndef ColaDePrioridad_H
#define ColaDePrioridad_H 1

#include "aed2/aed2.h"

template <typename T>
class ColaDePrioridad {
public:
    class Nodo {
        friend class ColaDePrioridad<T>;
    public:
        Nodo(const Nodo*);
        Nodo(const T &dato) : dato(dato), arr(NULL), izq(NULL), der(NULL)
        { };

        T dato;
        Nodo *arr;
        Nodo *izq;
        Nodo *der;
    };

    class Iterador {
        friend class ColaDePrioridad<T>;
    private:
        Iterador(ColaDePrioridad<T> *heap, Nodo *nodo) : heap(heap), nodo(nodo) { }

        ColaDePrioridad<T> *heap;
        Nodo *nodo;
    };

    ColaDePrioridad() : _tamano(0), cabeza(NULL), ultimo(NULL) { }
    ColaDePrioridad(const ColaDePrioridad<T> &);
    ~ColaDePrioridad();

    Iterador* Encolar(const T &);
    const T &Desencolar();
    const T &Desencolar(const Iterador &);
    aed2::Nat Tamano() const;
private:
    const T &Eliminar(Nodo *);
    void Subir(Nodo *);
    void Bajar(Nodo *);

    Nodo *cabeza;
    Nodo *ultimo;
    aed2::Nat _tamano;
};


///////////////////////////////////////////


template <typename T>
ColaDePrioridad<T>::Nodo::Nodo(const Nodo* otro)
{
    arr = NULL;
    izq = new Nodo(otro->izq);
    der = new Nodo(otro->der);
    dato = otro->dato;
    izq->arr = this;
    der->arr = this;
}

template<typename T>
ColaDePrioridad<T>::ColaDePrioridad(const ColaDePrioridad<T> &otra) {
    this->cabeza = NULL;
    this->ultimo = NULL;
    this->_tamano = 0;

    if (otra.Tamano() > 0) {
        this->cabeza = new Nodo(otra.cabeza);
        this->_tamano = otra._tamano;

        this->ultimo = this->cabeza;
        aed2::Nat camino = this->Tamano();

        while (camino > 1) {
            if (camino % 2 == 0) {
                this->ultimo = this->ultimo->izq;
            }
            else {
                this->ultimo = this->ultimo->der;
            }

            camino = camino / 2;
        }
    }
}

template <typename T>
ColaDePrioridad<T>::~ColaDePrioridad() {
    if (Tamano() > 0) {
        aed2::Lista<Nodo *> pila;
        pila.AgregarAtras(this->cabeza);

        while (!pila.EsVacia()) {
            Nodo *actual = pila.Primero();
            pila.Fin();

            if (actual->izq != NULL) {
                pila.AgregarAtras(actual->izq);
            }

            if (actual->der != NULL) {
                pila.AgregarAtras(actual->der);
            }

            delete actual;
        }
    }
}

template <typename T>
typename ColaDePrioridad<T>::Iterador* ColaDePrioridad<T>::Encolar(const T &dato) {
    Nodo *tmp = new Nodo(dato);

    if (this->Tamano() == 0) {
        this->cabeza = tmp;
    }
    else if (this->Tamano() == 1) {
        tmp->arr = this->cabeza;
        this->cabeza->izq = tmp;
    }
    else {
        if (this->ultimo->arr->izq == this->ultimo) {
            tmp->arr = this->ultimo->arr;
            this->ultimo->arr->der = tmp;
        }
        else {
            Nodo *actual = this->ultimo;

            while (actual->arr != NULL && actual->arr->izq != actual) {
                actual = actual->arr;
            }

            if (actual->arr != NULL) {
                actual = actual->arr->der;
            }

            while (actual->izq != NULL) {
                actual = actual->izq;
            }

            tmp->arr = actual;
            actual->izq = tmp;
        }
    }

    this->ultimo = tmp;
    ++this->_tamano;

    Subir(this->ultimo);
    return new Iterador(this, this->ultimo);
}

template <typename T>
const T &ColaDePrioridad<T>::Desencolar() {
    return Eliminar(this->cabeza);
}

template <typename T>
const T &ColaDePrioridad<T>::Desencolar(const Iterador &i) {
    assert(i.heap == this);

    return Eliminar(i.nodo);
}

template <typename T>
void ColaDePrioridad<T>::Subir(Nodo *node) {
    while (node->arr != NULL && node->arr->dato < node->dato) {
        T tmp = node->arr->dato;
        node->arr->dato = node->dato;
        node->dato = tmp;
        node = node->arr;
    }
}

#define max(a, b) (a >= b)? a:b
#define min(a, b) (a <= b)? a:b

template <typename T>
void ColaDePrioridad<T>::Bajar(Nodo *node) {
    while (node->izq != NULL && node->der != NULL &&
        node->dato < max(node->izq->dato, node->der->dato)) {
        if (node->izq->dato >= node->der>dato) {
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

    while (node->izq != NULL && node->izq->dato > node->dato) {
        T tmp = node->izq->dato;
        node->izq->dato = node->dato;
        node->dato = tmp;
        node = node->izq;
    }

    while (node->der != NULL && node->der->dato > node->dato) {
        T tmp = node->der->dato;
        node->der->dato = node->dato;
        node->dato = tmp;
        node = node->der;
    }
}

template <typename T>
const T &ColaDePrioridad<T>::Eliminar(Nodo *node) {
    // Pre: node esta en la estructura
    const T &tmp = node->dato;

    if (this->Tamano() == 1) {
        delete this->cabeza;
        this->ultimo = NULL;
        this->cabeza = NULL;
    } else {
        node->dato = this->ultimo->dato;
        Nodo *backup = this->ultimo;

        if (this->ultimo->arr->izq == this->ultimo) {
            Nodo *actual = this->ultimo;

            while (actual->arr != NULL && actual->arr->der != actual) {
                actual = actual->arr;
            }

            if (actual->arr != NULL) {
                actual = actual->arr->izq;
            }

            while (actual->der != NULL) {
                actual = actual->der;
            }

            this->ultimo->arr->izq = NULL;
            this->ultimo = actual;
        }
        else {
            this->ultimo = this->ultimo->arr->izq;
            this->ultimo->arr->der = NULL;
        }

        if (node->dato < node->arr->dato) {
            Bajar(node);
        }
        else {
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

#endif
