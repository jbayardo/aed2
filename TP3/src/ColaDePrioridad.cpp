#include "../include/ColaDePrioridad.h"
#include <assert.h>

/*
* TODO: copy constructor. verificar que el algoritmo de borrado esta bien. escribir tests. verificar que bajar esta bien.
*/

template <typename T>
ColaDePrioridad<T>::~ColaDePrioridad() {
    // Usar una lista como stack para borrar.
}

template <typename T>
typename ColaDePrioridad<T>::Iterador ColaDePrioridad<T>::Encolar(const T &dato) {
    Node *tmp = new ColaDePrioridad<T>::Node(dato);

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
            Node *cur = this->ultimo;

            while (cur->arr != nullptr && cur->arr->izq != cur) {
                cur = cur->arr;
            }

            if (cur->arr != nullptr) {
                cur = cur->arr->der;
            }

            while (cur->izq != nullptr) {
                cur = cur->izq;
            }

            tmp->arr = cur;
            cur->izq = tmp;
        }
    }

    this->ultimo = tmp;
    ++this->_tamano;

    Subir(this->ultimo);
    return ColaDePrioridad<T>::Iterador(this, this->ultimo);
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
void ColaDePrioridad<T>::Subir(ColaDePrioridad<T>::Node *node) {
    while (node->arr != nullptr && node->arr->dato < node->dato) {
        T tmp = node->arr->dato;
        node->arr->dato = node->dato;
        node->dato = tmp;
        node = node->arr;
    }
}

template <typename T>
void ColaDePrioridad<T>::Bajar(ColaDePrioridad<T>::Node *node) {
    while ((node->izq != nullptr && node->dato < node->izq->dato) ||
        (node->der != nullptr && node->der->dato < node->dato)) {
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
const T &ColaDePrioridad<T>::Eliminar(ColaDePrioridad<T>::Node *node) {
    // Pre: node esta en la estructura
    const T &tmp = node->dato;

    if (this->Tamano() == 1) {
        delete this->cabeza;
        this->ultimo = nullptr;
        this->cabeza = nullptr;
    } else {
        node->dato = this->ultimo->dato;
        Node *tmp = this->ultimo;

        if (this->ultimo->arr->izq == this->ultimo) {
            Node *cur = this->ultimo;

            while (cur->arr != nullptr && cur->arr->der != cur) {
                cur = cur->arr;
            }

            if (cur->arr != nullptr) {
                cur = cur->arr->izq;
            }

            while (cur->der != nullptr) {
                cur = cur->der;
            }

            this->ultimo->arr->izq = nullptr;
            this->ultimo = cur;
        } else {
            this->ultimo = this->ultimo->arr->izq;
            this->ultimo->arr->der = nullptr;
        }

        if (node->dato < node->arr->dato) {
            Bajar(node);
        } else {
            Subir(node);
        }

        delete tmp;
    }

    --this->_tamano;

    return tmp;
}

template <typename T>
unsigned int ColaDePrioridad<T>::Tamano() const {
    return this->_tamano;
}
