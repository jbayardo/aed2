#ifndef ColaDePrioridad_H
#define ColaDePrioridad_H 1

#include "aed2/aed2.h"

template <typename T>
class ColaDePrioridad {
public:
    class Nodo {
        friend class ColaDePrioridad<T>;
    public:
        Nodo(const T &dato) : dato(dato), arr(nullptr), izq(nullptr), der(nullptr)
        { };
        Nodo(const Nodo &);

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

    ColaDePrioridad() : _tamano(0), cabeza(nullptr), ultimo(nullptr) { }
    ColaDePrioridad(const ColaDePrioridad<T> &);
    ~ColaDePrioridad();

    ColaDePrioridad<T>::Iterador Encolar(const T &);
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

#endif
