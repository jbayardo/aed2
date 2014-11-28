#include "ConjRapidoString.h"

void ConjRapidoString::Agregar(std::string s)
{
    values.Definir(s, true);
}

bool ConjRapidoString::Pertenece(std::string s) const
{
    return values.Definido(s);
}

Conj<std::string>::Iterador ConjRapidoString::CrearIt()
{
    return values.Claves();
}
