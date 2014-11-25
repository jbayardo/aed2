//PREGUNTAR: Conj<std::string>::Iterador seria Conj<Estacion>::Iterador idem en ciudad!
#ifndef DICCSTRING_H
#define DICCSTRING_H

#include "../aed2.h"

using namespace aed2;
using namespace std;

template <typename T>
class DiccString
{
    public:
        DiccString();
        DiccString(const DiccString &otra);
        ~DiccString();
        void Definir(const std::string k, const T &v);
        bool Definido(const std::string k) const;
        T Obtener(const std::string k) const;
        Conj<std::string>::Iterador Claves() const;
    private:
		struct trie
        {
            public:
				~trie(){
					delete[] this->significado;
					for (int i = 0; i < 256; i++){
						delete[] this->continuacion[i];
					}
				}
				trie() : continuacion(Arreglo<trie*>(256)), significado(nullptr) {}
                Arreglo<trie*> continuacion;
                T *significado;
        };
        Conj<std::string> claves;
        trie significados;
};

#endif