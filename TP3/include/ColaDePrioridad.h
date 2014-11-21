#ifndef ColaDePrioridad_H
#define ColaDePrioridad_H 1

#include "../aed2/TiposBasicos.h"

template <typename T>
class ColaDePrioridad {
private:
    class Node {
    public:
        Node(const T &dato) : dato(dato), arr(nullptr), izq(nullptr), der(nullptr)
        { };
        Node(const Node &);

        T dato;
        Node *arr;
        Node *izq;
        Node *der;
    };

    const T &Eliminar(Node *);
    void Subir(Node *);
    void Bajar(Node *);

    Node *cabeza;
    Node *ultimo;
    aed2::Nat _tamano;
public:
    class Iterador {
        friend class ColaDePrioridad<T>;
    private:
        Iterador(ColaDePrioridad<T> *heap, Node *nodo) : heap(heap), nodo(nodo) { }

        ColaDePrioridad<T> *heap;
        Node *nodo;
    };

    ColaDePrioridad() : _tamano(0), cabeza(nullptr), ultimo(nullptr) { }
    ColaDePrioridad(const ColaDePrioridad<T> &);
    ~ColaDePrioridad();

    ColaDePrioridad<T>::Iterator Encolar(const T &);
    const T &Desencolar();
    const T &Desencolar(const Iterador &);
    aed2::Nat Tamano() const;
};

#endif
