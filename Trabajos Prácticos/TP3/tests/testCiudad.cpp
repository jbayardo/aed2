#include "tests.h"

using namespace aed2;

/**
 * Imprime un elemento a un string, en vez de a una pantalla,
 * a través del operador <<
 */
// template <typename T>
// std::string to_str(const T &t)
// {
//     std::stringstream ss;
//     ss << t;

//     return ss.str();
// }

/**
 * Esta función se puede utilizar para comparar dos colecciones
 * iterables que representen conjuntos, es decir, que no tengan
 * elementos repetidos.
 */
template<typename T, typename S>
bool Comparar(const T &t, const S &s)
{
    typename T::const_Iterador it1 = t.CrearIt();
    typename S::const_Iterador it2 = s.CrearIt();

    // me fijo si tienen el mismo tamanho

    Nat len1 = 0;
    while ( it1.HaySiguiente() ) {
        len1++;
        it1.Avanzar();
    }

    Nat len2 = 0;
    while ( it2.HaySiguiente() ) {
        len2++;
        it2.Avanzar();
    }

    if ( len1 != len2 ) {
        return false;
    }

    it1 = t.CrearIt();
    it2 = s.CrearIt();

    // me fijo que tengan los mismos elementos

    while ( it1.HaySiguiente() ) {
        bool esta = false;
        it2 = s.CrearIt();

        while ( it2.HaySiguiente() ) {
            if ( it1.Siguiente() == it2.Siguiente() ) {
                esta = true;
                break;
            }
            it2.Avanzar();
        }

        if ( !esta ) {
            return false;
        }

        it1.Avanzar();
    }

    return true;
}


// ---------------------------------------------------------------------

/**
 * Ejemplo de caso de test, con llamadas a las rutinas de aserción
 * definidas en mini_test.h
 */
void test_ciudad_simple()
{
    Conj<Estacion> estaciones;
    estaciones.Agregar("Belgrano");
    estaciones.Agregar("Retiro");
    estaciones.Agregar("Martinez");

    Driver caba(estaciones);

    caba.AgregarSenda("Belgrano", "Retiro", "(trenDePasajeros | trenDeCarga) & !trenDeLaAlegria");
    caba.AgregarSenda("Martinez", "Retiro", "trenDeLaAlegria");
    caba.AgregarSenda("Martinez", "Belgrano", "trenDePasajeros");

    Conj<Caracteristica> r1, r2, r3;
    r1.Agregar("trenDePasajeros");
    r2.Agregar("trenDeCarga");
    r3.Agregar("trenDeLaAlegria");

    caba.Entrar(r1, "Belgrano"); // RUR 0
    caba.Entrar(r2, "Retiro");  // RUR 1
    caba.Entrar(r3, "Martinez"); // RUR 2

    assert(caba.CantidadEstaciones() == 3);
    assert(caba.CantidadRobotsActivos() == 3);
    assert(caba.CantidadDeSendasParaEstacion("Belgrano") == 2);

    caba.Mover(0, "Retiro");   // RUR 0: 0 infracciones
    caba.Mover(0, "Martinez"); // RUR 0: 1 infracciones

    caba.Mover(1, "Belgrano"); // RUR 1: 0 infracciones
    caba.Mover(1, "Martinez"); // RUR 1: 1 infracciones

    caba.Mover(2, "Belgrano"); // RUR 2: 1 infracciones
    caba.Mover(2, "Retiro");   // RUR 2: 2 infracciones

    Dicc<RUR, Nat> infraccionesRobots;

    // Chequeo infracciones iterando los robots
    for (Nat i = 0;  i < caba.CantidadRobotsActivos(); ++i) {
        infraccionesRobots.Definir(caba.IesimoRobotActivo(i), caba.CantInfraccionesIesimoRobotActivo(i));
    }

    assert(infraccionesRobots.Significado(0) == 1);
    assert(infraccionesRobots.Significado(1) == 1);
    assert(infraccionesRobots.Significado(2) == 2);

    assert(caba.ElMasInfractor() == 2);

    // Vuela un robot
    caba.Inspeccion("Retiro");
    assert(caba.CantidadRobotsActivos() == 2);

}

void test_ciudad_con_movimientos()
{
    Conj<Estacion> estaciones;
    estaciones.Agregar("Belgrano");
    estaciones.Agregar("Retiro");
    estaciones.Agregar("Martinez");

    Driver caba(estaciones);

    caba.AgregarSenda("Belgrano", "Retiro", "(trenDePasajeros | trenDeCarga) & !trenDeLaAlegria");
    caba.AgregarSenda("Martinez", "Retiro", "trenDeLaAlegria");
    caba.AgregarSenda("Martinez", "Belgrano", "trenDePasajeros");

    Conj<Caracteristica> r1, r2, r3;
    r1.Agregar("trenDePasajeros");
    r2.Agregar("trenDeCarga");
    r3.Agregar("trenDeLaAlegria");

    caba.Entrar(r1, "Belgrano"); // RUR 0
    caba.Entrar(r2, "Retiro");  // RUR 1
    caba.Entrar(r3, "Martinez"); // RUR 2
    assert(caba.IesimoRobotActivo(2) == 2);
    assert(caba.IesimaEstacion(2) == "Martinez");
    assert(caba.CantidadDeSendasParaEstacion("Martinez") == 2);
    assert(caba.CantidadDeSendasParaEstacion("Belgrano") == 2);
    assert(caba.IesimaEstacionDeSenda("Martinez", 1) == "Retiro");
    assert(caba.IesimaEstacionDeSenda("Retiro", 2) == "Martinez");
    assert(caba.IesimaRestriccionDeSenda("Belgrano", 1) == "((trenDePasajeros) | (trenDeCarga)) & (!(trenDeLaAlegria))");


    caba.Mover(1, "Belgrano");
    caba.Mover(2, "Belgrano");
    assert(caba.ElMasInfractor() == 2);
    assert(caba.EstacionActualIesimoRobotActivo(2) == "Belgrano");
    assert(caba.EstacionActualIesimoRobotActivo(1) == "Belgrano");
}

void test_ciudad_cantidad_estaciones()
{
    Conj<Estacion> estaciones;

    Driver *caba = new Driver(estaciones);
    assert(caba->CantidadEstaciones() == 0);
    delete(caba);

    estaciones.Agregar("Belgrano");
    estaciones.Agregar("Retiro");
    estaciones.Agregar("Martinez");

    caba = new Driver(estaciones);
    assert(caba->CantidadEstaciones() == 3);
    delete(caba);

    estaciones.Agregar("Urquiza");
    estaciones.Agregar("Devoto");

    caba = new Driver(estaciones);
    assert(caba->CantidadEstaciones() == 5);
    delete(caba);
}

void test_ciudad_cantidad_de_robots_activos()
{
    Conj<Estacion> estaciones;
    estaciones.Agregar("Belgrano");
    estaciones.Agregar("Retiro");
    estaciones.Agregar("Martinez");

    Driver *caba = new Driver(estaciones);
    assert(caba->CantidadRobotsActivos() == 0);

    caba->AgregarSenda("Belgrano", "Retiro", "(trenDePasajeros | trenDeCarga) & !trenDeLaAlegria");
    caba->AgregarSenda("Martinez", "Retiro", "trenDeLaAlegria");
    caba->AgregarSenda("Martinez", "Belgrano", "trenDePasajeros");

    Conj<Caracteristica> r1, r2, r3;
    r1.Agregar("trenDePasajeros");
    r2.Agregar("trenDeCarga");
    r3.Agregar("trenDeLaAlegria");

    caba->Entrar(r1, "Belgrano"); // RUR 0
    caba->Entrar(r2, "Retiro");  // RUR 1
    assert(caba->CantidadRobotsActivos() == 2);

    caba->Entrar(r3, "Martinez"); // RUR 2
    assert(caba->CantidadRobotsActivos() == 3);

    delete(caba);
}
