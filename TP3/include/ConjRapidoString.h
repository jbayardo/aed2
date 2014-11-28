#ifndef CONJ_RAPIDO_STRING_H
#define CONJ_RAPIDO_STRING_H 1

#include "aed2/aed2.h"
#include "DiccString.h"

class ConjRapidoString
{
    public:
        void Agregar(std::string s);
        bool Pertenece(std::string s) const;
        Conj<std::string>::Iterador CrearIt();
    private:
        DiccString<bool> values;

};

#endif