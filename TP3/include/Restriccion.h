#ifndef RESTRICCION_H
#define RESTRICCION_H 1

#include "Tipos.h"
#include "ConjRapidoString.h"

class Restriccion_
{
    private:
        enum Op {AND, OR, NOT, VAR};
        std::string value;
        Op type;
        Restriccion_ *left, *right;

        Restriccion_(Op t, std::string v, Restriccion_ *l, Restriccion_ *r);

    public:
        static Restriccion_ *And(Restriccion_ *left, Restriccion_ *right);
        static Restriccion_ *Or(Restriccion_ *left, Restriccion_ *right);
        static Restriccion_ *Not(Restriccion_ *left);
        static Restriccion_ *Var(std::string v);

        bool Verifica(const ConjRapidoString &tags);
        Restriccion toRestriccion();
        Restriccion_(const Restriccion_& r);
        ~Restriccion_();


};

#endif
