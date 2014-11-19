#ifndef RESTRICCION_H
#define RESTRICCION_H 1

#include "Tipos.h"
#include "ConjRapidoString.h"

class Restriccion
{
    private:
        enum Op {AND, OR, NOT, VAR};
        std::string value;
        Op type;
        Restriccion *left, *right;

        Restriccion(Op t, std::string v, Restriccion *l, Restriccion *r);

    public:    	
        static Restriccion *And(Restriccion *left, Restriccion *right);
        static Restriccion *Or(Restriccion *left, Restriccion *right);
        static Restriccion *Not(Restriccion *left);
        static Restriccion *Var(std::string v);
        
        bool Verifica(ConjRapidoString& tags);
        
        ~Restriccion();


};

#endif