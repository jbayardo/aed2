#ifndef CONJRAPIDSTRING_H
#define CONJRAPIDSTRING_H 1

#include "Tipos.h"
#include "DiccString.h"

class ConjRapidoString
{
    public:
        ConjRapidoString();
        void Agregar(string s);
        bool Pertenece(string s);
        ~ConjRapidoString();

    private:
        DiccString<bool> *values;

};

#endif