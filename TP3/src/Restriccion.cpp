#include "../include/Restriccion.h"

// Restriccion::Restriccion(ArbolSintactico &S)
// {
//     if (S.raiz == "&" or S.raiz == "|") {
//         type = (S.raiz == "&") ? And : Or;
//         value = "";
//         left = new Restriccion(S.izq);
//         right = new Restriccion(S.der);
//     } else if (S.raiz == "!") {
//         type = Not;
//         value = "";
//         left = Restriccion(S.izq);
//         right = nullptr;
//     } else {
//         type = Var;
//         value = S.raiz;
//         left = right = nullptr;
//     }
// }

Restriccion::Restriccion(Op t, std::string v, Restriccion *l, Restriccion *r) :
    type(t), value(v), left(l), right(r) {}


Restriccion *Restriccion::And(Restriccion *left, Restriccion *right)
{
    return new Restriccion(Op::AND, "", left, right);
}

Restriccion *Restriccion::Or(Restriccion *left, Restriccion *right)
{
    return new Restriccion(Op::OR, "", left, right);
}

Restriccion *Restriccion::Not(Restriccion *left)
{
    return new Restriccion(Op::NOT, "", left, nullptr);
}

Restriccion *Restriccion::Var(std::string v)
{
    return new Restriccion(Op::VAR, v, nullptr, nullptr);
}

bool Restriccion::Verifica(ConjRapidoString &tags)
{
    switch (type) {
        case Op::AND:
            return left->Verifica(tags) and right->Verifica(tags);
        case Op::OR:
            return left->Verifica(tags) or right->Verifica(tags);
        case Op::NOT:
            return not left->Verifica(tags);
        case Op::VAR:
            return tags.pertenece(value);
    }
}

Restriccion::~Restriccion()
{
    if (type == Op::AND or type == Op::OR) {
        delete left;
        delete right;
    } else if (type == Op::NOT) {
        delete left;
    }
}