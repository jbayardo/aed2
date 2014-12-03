#ifndef DICCSTRING_H
#define DICCSTRING_H 1

#include "aed2/aed2.h"

template <typename T>
class DiccString {
    public:
        DiccString() {};
        DiccString(const DiccString &otra);
        ~DiccString(){};
        void Definir(const std::string k, T const &v);
        bool Definido(const std::string k) const;
        T& Obtener(const std::string k) const;
        Conj<std::string>::const_Iterador Claves() const;

    private:
		struct Nodo {
            public:
				~Nodo() {
					for (int i = 0; i < 256; i++) {
                        if (this->continuacion[i] != NULL){                           
						  delete this->continuacion[i];
                          this->continuacion[i] = NULL;
                        }
					}
                    if (significado != NULL){
                        delete significado;
                        significado = NULL;
                    }
				}

				Nodo(){
                    for (int i = 0; i < 256; ++i){
                        continuacion[i] = NULL;
                    }           
                    significado = NULL;
                }
                Nodo* continuacion[256];
                T *significado;
        };

        Conj<std::string> claves;
        Nodo significados;
};

template <typename T>
DiccString<T>::DiccString(const DiccString &otra) {
    Conj<std::string>::const_Iterador clv;
    clv = otra.Claves();

    while (clv.HaySiguiente()) {
        this->Definir(clv.Siguiente(), otra.Obtener(clv.Siguiente()));
        clv.Avanzar();
    }
}

template <typename T>
void DiccString<T>::Definir(const std::string k, T const &v) {
    int i = 0;
    Nodo *t = &(this->significados);
    bool nuevo = false;

    while (k.length() > i){
        if (t->continuacion[k[i]] == NULL) {
            t->continuacion[k[i]] = new Nodo();
            nuevo = true;
        }

        t = t->continuacion[k[i]];
        i++;
    }

    if (t->significado != NULL){
        delete t->significado;
    }

    t->significado = new T(v);

    if (nuevo) {
        this->claves.AgregarRapido(k);
    }
}

template <typename T>
bool DiccString<T>::Definido(const std::string k) const {
    int i = 0;
    const Nodo * t = &(this->significados);

    while ((i < k.length()) && t->continuacion[k[i]] != NULL) {
        t = t->continuacion[k[i]];
        i++;
    }

    return (t->significado != NULL && i == k.length());
}

template <typename T>
T& DiccString<T>::Obtener(const std::string k) const {
    int i = 0;
    const Nodo *t = &(this->significados);

    while (i < k.length()) {
        t = t->continuacion[k[i]];
        i++;
    }

    return *(t->significado);
}

template <typename T>
Conj<std::string>::const_Iterador DiccString<T>::Claves() const {
    return this->claves.CrearIt();
}

#endif