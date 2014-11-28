#ifndef CONJRAPIDSTRING_H
#define CONJRAPIDSTRING_H 1

#include "aed2/aed2.h"
#include "DiccString.h"

class ConjRapidoString
{
    public:
        ConjRapidoString();
        void Agregar(std::string s);
        bool Pertenece(std::string s) const;
        Conj<std::string>::Iterador CrearIt();
        ~ConjRapidoString();

    private:
        DiccString<bool> *values;

};

#endif