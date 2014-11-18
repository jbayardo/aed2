#include <WebKit/WebKit.h>
#include "Restriccion.h"

Restriccion::Restriccion(ArbolSintactico* S) {
    if (S->raiz == "&" or S->raiz == "|"){
        type = (S->raiz == "&")? And : Or;
        value = "";
        left = Restriccion(S->izq);
        right = Restriccion(S->der);
    }
    else if (S->raiz == "!"){
        type = Not;
        value = "";
        left = Restriccion(S->izq);
        right = nullptr;
    }
    else{
        type = Var;
        value = S->raiz;
        left = right = nullptr;
    }
}

bool Restriccion::Verifica(ConjRapidoString& tags){
    switch(type){
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

Restriccion::~Restriccion(){
    if (type == And or type == Or){
        delete left;
        delete right;
    }
    else if (type == Not){
        delete left;
    }
}