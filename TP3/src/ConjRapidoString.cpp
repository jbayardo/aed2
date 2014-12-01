#include "ConjRapidoString.h"

void ConjRapidoString::Agregar(std::string s)
{
    values.Definir(s, new bool(true));
}

bool ConjRapidoString::Pertenece(std::string s) const
{
    return values.Definido(s);
}

Conj<std::string>::const_Iterador ConjRapidoString::CrearIt()
{
    return values.Claves();
}
