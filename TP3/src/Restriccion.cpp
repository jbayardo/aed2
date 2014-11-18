#include "../include/Restriccion.h"

Restriccion::Restriccion(ArbolSintactico &S)
{
    if (S.raiz == "&" or S.raiz == "|") {
        type = (S.raiz == "&") ? And : Or;
        value = "";
        left = new Restriccion(S.izq);
        right = new Restriccion(S.der);
    }
    else if (S.raiz == "!") {
        type = Not;
        value = "";
        left = Restriccion(S.izq);
        right = nullptr;
    }
    else {
        type = Var;
        value = S.raiz;
        left = right = nullptr;
    }
}

Restriccion::Restriccion(Restriccion &r)
{
    type = r.type;
    value = r.value;
    if (r.left != nullptr) {
        left = Restriccion(r.left);
    }
    if (r.right != nullptr) {
        right = Restriccion(r.right);
    }
}


bool Restriccion::Verifica(ConjRapidoString &tags)
{
    switch (type) {
        case And:
            return left->Verifica(tags) and right->Verifica(tags);
        case Or:
            return left->Verifica(tags) or right->Verifica(tags);
        case Not:
            return not left->Verifica(tags);
        case Var:
            return tags.pertenece(value);
    }
}

Restriccion::~Restriccion()
{
    if (type == And or type == Or) {
        delete left;
        delete right;
    }
    else if (type == Not) {
        delete left;
    }
}