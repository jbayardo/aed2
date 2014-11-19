#include "../include/ConjRapidoString.h"

ConjRapidoString::ConjRapidoString()
{
    values = new DiccString<bool>();
}

void ConjRapidoString::Agregar(string s)
{
    values->Definir(s, true);
}

bool ConjRapidoString::Pertenece(string s)
{
    return values->Definido(s);
}

ConjRapidoString::~ConjRapidoString()
{
    delete values;
}
