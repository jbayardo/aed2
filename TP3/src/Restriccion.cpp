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

Restriccion_::Restriccion_(Op t, std::string v, Restriccion_ *l, Restriccion_ *r) :
    type(t), value(v), left(l), right(r) {}


Restriccion_ *Restriccion_::And(Restriccion_ *left, Restriccion_ *right)
{
    return new Restriccion_(Op::AND, "", left, right);
}

Restriccion_ *Restriccion_::Or(Restriccion_ *left, Restriccion_ *right)
{
    return new Restriccion_(Op::OR, "", left, right);
}

Restriccion_ *Restriccion_::Not(Restriccion_ *left)
{
    return new Restriccion_(Op::NOT, "", left, nullptr);
}

Restriccion_ *Restriccion_::Var(std::string v)
{
    return new Restriccion_(Op::VAR, v, nullptr, nullptr);
}

bool Restriccion_::Verifica(const ConjRapidoString &tags)
{
    switch (type) {
        case Op::AND:
            return left->Verifica(tags) && right->Verifica(tags);
        case Op::OR:
            return left->Verifica(tags) || right->Verifica(tags);
        case Op::NOT:
            return !left->Verifica(tags);
        case Op::VAR:
            return tags.Pertenece(value);
    }
}

Restriccion_::~Restriccion_()
{
    if (type == Op::AND || type == Op::OR) {
        delete left;
        delete right;
    } else if (type == Op::NOT) {
        delete left;
    }
}

Restriccion_::Restriccion_(const Restriccion_ &r)
{
    switch (r.type) {
        case Op::AND:
            And(new Restriccion_(*r.left), new Restriccion_(*r.right));
            break;
        case Op::OR:
            Or(new Restriccion_(*r.left), new Restriccion_(*r.right));
            break;
        case Op::NOT:
            Not(new Restriccion_(*r.left));
            break;
        case Op::VAR:
            Var(r.value);
            break;
    }
}