#include "ColaDePrioridad.h"
#include "aed2/TiposBasicos.h"
#include "tests.h"

template <typename T>
void test_es_max_heap(T arr[], aed2::Nat N)
{
    ColaDePrioridad<T> cola = ColaDePrioridad<T>();
    T max = arr[0];

    for (aed2::Nat i = 0; i < N; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        delete cola.Encolar(arr[i]);
    }

    assert(cola.Desencolar() == max);
}

template <typename T>
void test_desencolar_ordenado(T arr[], aed2::Nat N)
{
    ColaDePrioridad<T> cola = ColaDePrioridad<T>();

    for (aed2::Nat i = 0; i < N; i++) {
        delete cola.Encolar(arr[i]);
        assert(cola.Tamano() == i + 1);
    }

    assert(cola.Tamano() == N);
    T *ordenada = new T[N];


    for (int i = 0; i < N; ++i) {
        ordenada[i] = cola.Desencolar();
    }


    for (aed2::Nat i = 0; i < N - 1; i++) {
        assert(ordenada[i] >= ordenada[i + 1]);
    }

    assert(cola.Tamano() == 0);
    delete[] ordenada;
}

template <typename T>
void test_encolar_desencolar(T arr[], aed2::Nat N)
{
    ColaDePrioridad<T> cola = ColaDePrioridad<T>();
    typename ColaDePrioridad<T>::Iterador *it;

    for (aed2::Nat i = 0; i < N; i++) {
        assert(cola.Tamano() == 0);
        it = cola.Encolar(arr[i]);
        assert(cola.Tamano() == 1);
        assert(cola.Desencolar(it) == arr[i]);
        delete it;
        assert(cola.Tamano() == 0);
    }
}

void test_cola_de_prioridad()
{
    int arr[] = {47, 282, 282, 49, 343, 290, 28, 213, 83, 155, 89, 388, 409, 250,
                 203, 361, 43, 334, 5, 244, 347, 13, 219, 24, 0, 400, 367, 324, 288, 365,
                 239, 225, 112, 263, 208, 180, 365, 406, 202, 163, 134, 147, 141, 5, 92,
                 364, 18, 350, 27, 369, 317, 416, 436, 17, 250, 416, 64, 437, 128, 379, 324,
                 448, 126, 395, 50, 287, 50, 223, 327, 13, 21, 424, 89, 271, 25, 260, 254,
                 146, 323, 318, 111, 196, 313, 51, 231, 175, 438, 394, 368, 222, 154, 279,
                 329, 418, 349, 276, 78, 369, 75, 164, 104, 429, 225, 351, 65, 101, 157, 59,
                 448, 434, 308, 358, 26, 403, 237, 261, 10, 51, 425, 323, 297, 420, 49, 407,
                 288, 174, 338, 93, 406, 304, 230, 79, 251, 381, 397, 67, 283, 289, 3, 442,
                 310, 145, 67, 319, 389, 216, 377, 347, 408, 117, 431, 207, 225, 270, 104,
                 212, 166, 132, 4, 131, 351, 35, 301, 188, 80, 0, 387, 96, 287, 92, 116, 23,
                 138, 6, 153, 10, 316, 233, 142, 41, 118, 47, 205, 265, 206, 274, 399, 433,
                 190, 28, 339, 95, 39, 259, 85, 249, 100, 350, 70
                };
    test_es_max_heap(arr, 199);
    test_desencolar_ordenado(arr, 199);
    test_encolar_desencolar(arr, 199);
}
