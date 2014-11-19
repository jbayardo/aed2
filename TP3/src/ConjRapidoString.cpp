#include "../include/ConjRapidoString.h"

ConjRapidoString::ConjRapidoString()
{
    values = new DiccString<bool>();
}

void ConjRapidoString::Agregar(std::string s)
{
    values->Definir(s, true);
}

bool ConjRapidoString::Pertenece(std::string s)
{
    return values->Definido(s);
}

Conj<std::string>::Iterador ConjRapidoString::CrearIt()
{
    return values->Claves();
}


ConjRapidoString::~ConjRapidoString()
{
    delete values;
}
