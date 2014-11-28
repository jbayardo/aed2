#ifndef DICCSTRING_H
#define DICCSTRING_H 1

#include "aed2/aed2.h"

template <typename T>
class DiccString {
    public:
        DiccString() : claves(Conj<std::string>()), significados(Nodo()) {};
        DiccString(const DiccString &otra);
        void Definir(const std::string k, const T &v);
        bool Definido(const std::string k) const;
        T Obtener(const std::string k) const;
        Conj<std::string>::Iterador Claves() const;
    private:
		struct Nodo {
            public:
				~Nodo() {
					delete[] this->significado;

					for (int i = 0; i < 256; i++) {
						delete this->continuacion[i];
					}
				}

				Nodo() : continuacion(Arreglo<Nodo*>(256)), significado(nullptr) {}
                Arreglo<Nodo*> continuacion;
                T *significado;
        };

        Conj<std::string> claves;
        Nodo significados;
};

#endif