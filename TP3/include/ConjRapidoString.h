#ifndef CONJRAPIDSTRING_H
#define CONJRAPIDSTRING_H 1

#include "Tipos.h"
#include "DiccString.h"

class ConjRapidoString
{
    public:
        ConjRapidoString();
        void Agregar(std::string s);
        bool Pertenece(std::string s);
        Conj<std::string>::Iterador CrearIt();
        ~ConjRapidoString();

    private:
        DiccString<bool> *values;

};

#endif