#ifndef RESTRICCION_H
#define RESTRICCION_H 1

#include <string>

class Restriccion{
public:
    Restriccion(ArbolSintactico& S);
    Restriccion(Restriccion& r);
    ~Restriccion();

    bool Verifica(ConjRapidoString tags);

private:

    enum Op{And, Or, Not, Var};

    String value;
    Op type;
    Restriccion* right;
    Restriccion* left;

};

#endif