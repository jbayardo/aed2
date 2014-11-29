#include "Restriccion.h"

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
//         right = NULL;
//     } else {
//         type = Var;
//         value = S.raiz;
//         left = right = NULL;
//     }
// }

Restriccion_::Restriccion_(Op t, std::string v, Restriccion_ *l, Restriccion_ *r) :
    type(t), value(v), left(l), right(r) {}


Restriccion_ *Restriccion_::And(Restriccion_ *left, Restriccion_ *right)
{
    return new Restriccion_(AND, "", left, right);
}

Restriccion_ *Restriccion_::Or(Restriccion_ *left, Restriccion_ *right)
{
    return new Restriccion_(OR, "", left, right);
}

Restriccion_ *Restriccion_::Not(Restriccion_ *left)
{
    return new Restriccion_(NOT, "", left, NULL);
}

Restriccion_ *Restriccion_::Var(std::string v)
{
    return new Restriccion_(VAR, v, NULL, NULL);
}

bool Restriccion_::Verifica(const ConjRapidoString &tags)
{
    switch (type) {
        case AND:
            return left->Verifica(tags) && right->Verifica(tags);
        case OR:
            return left->Verifica(tags) || right->Verifica(tags);
        case NOT:
            return !left->Verifica(tags);
        case VAR:
            return tags.Pertenece(value);
    }
}

Restriccion_::~Restriccion_()
{
    if (type == AND || type == OR) {
        delete left;
        delete right;
    } else if (type == NOT) {
        delete left;
    }
}

Restriccion_::Restriccion_(const Restriccion_ &r)
{
    switch (r.type) {
        case AND:
            And(new Restriccion_(*r.left), new Restriccion_(*r.right));
            break;
        case OR:
            Or(new Restriccion_(*r.left), new Restriccion_(*r.right));
            break;
        case NOT:
            Not(new Restriccion_(*r.left));
            break;
        case VAR:
            Var(r.value);
            break;
    }
}