#include "ColaDePrioridad.h"
#include "MiniTest.h"

template <typename T, size_t N>
void test_es_max_heap(T[N] arr) {
    ColaDePrioridad<T> cola = ColaDePrioridad<T>();
    T max = arr[0];

    for (size_t i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }

        cola.Encolar(arr[i]);
    }

    ASSERT_EQ(cola.Desencolar(), max);
}

template <typename T, size_t N>
void test_desencolar_ordenado(T[N] arr) {
    ColaDePrioridad<T> cola = ColaDePrioridad<T>();

    for (int i = 0; i < N-1; i++) {
        assert(arr[i] < arr[i+1]);
        cola.Encolar(arr[i]);
        ASSERT_EQ(cola.Tamano(), i + 1);
    }

    cola.Encolar(arr[N-1]);

    ASSERT_EQ(cola.Tamano(), N);

    for (int i = N-1; i >= 0; i--) {
        ASSERT_EQ(cola.Desencolar(), arr[i]);
    }

    ASSERT_EQ(cola.Tamano(), 0);
}

template <typename T, size_t N>
void test_encolar_desencolar(T[N] arr) {
    ColaDePrioridad<T> cola = ColaDePrioridad<T>();

    for (int i = 0; i < N; i++) {
        ASSERT_EQ(cola.Tamano(), 0);
        ColaDePrioridad<T>::Iterador *it = cola.Encolar(arr[i]);
        ASSERT_EQ(cola.Tamano(), 1);
        ASSERT_EQ(cola.Desencolar(it), arr[i]);
        ASSERT_EQ(cola.Tamano(), 0);
    }
}
