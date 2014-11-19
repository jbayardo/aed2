#ifndef RESTRICCION_H
#define RESTRICCION_H 1

#include <string>

class Restriccion
{
    public:
        static Restriccion *And(Restriccion *left, Restriccion *right);
        static Restriccion *Or(Restriccion *left, Restriccion *right);
        static Restriccion *Not(Restriccion *left);
        static Restriccion *Var(string v);
        ~Restriccion();

        bool Verifica(ConjRapidoString tags);

    private:
        Restriccion(Op t, string v,
                    Restriccion *l,
                    Restriccion *r) : value(v), type(t), left(l), right(r) {};

        enum Op {And, Or, Not, Var};

        string value;
        Op type;
        Restriccion *left;
        Restriccion *right;
};

#endif