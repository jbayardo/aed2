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

static Restriccion *Restriccion::And(Restriccion *left, Restriccion *right)
{
    return new Restriccion(And, "", left, right);
}

static Restriccion *Restriccion::Or(Restriccion *left, Restriccion *right)
{
    return new Restriccion(Or, "", left, right);
}

static Restriccion *Restriccion::Not(Restriccion *left)
{
    return new Restriccion(Not, "", left, nullptr);
}

static Restriccion *Restriccion::Var(string v)
{
    return new Restriccion(Var, v, nullptr, nullptr);
}

bool Restriccion::Verifica(ConjRapidoString &tags)
{
    switch (type) {
        case Op::And:
            return left->Verifica(tags) and right->Verifica(tags);
        case Op::Or:
            return left->Verifica(tags) or right->Verifica(tags);
        case Op::Not:
            return not left->Verifica(tags);
        case Op::Var:
            return tags.pertenece(value);
    }
}

Restriccion::~Restriccion()
{
    if (type == Op::And or type == Op::Or) {
        delete left;
        delete right;
    } else if (type == Op::Not) {
        delete left;
    }
}