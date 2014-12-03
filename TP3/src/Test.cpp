#include "aed2/aed2.h"
#include "Driver.h"
#include "MiniTest.h"

#include "DiccString.h"

#include <string>
#include <iostream>

using namespace aed2;

/**
 * Imprime un elemento a un string, en vez de a una pantalla,
 * a través del operador <<
 */
template <typename T>
std::string to_str(const T &t)
{
    std::stringstream ss;
    ss << t;

    return ss.str();
}

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

    ASSERT_EQ(caba.CantidadEstaciones(), 3);
    ASSERT_EQ(caba.CantidadRobotsActivos(), 3);
    ASSERT_EQ(caba.CantidadDeSendasParaEstacion("Belgrano"), 2);

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

    ASSERT_EQ(infraccionesRobots.Significado(0), 1);
    ASSERT_EQ(infraccionesRobots.Significado(1), 1);
    ASSERT_EQ(infraccionesRobots.Significado(2), 2);

    ASSERT_EQ(caba.ElMasInfractor(), 2);

    // Vuela un robot
    caba.Inspeccion("Retiro");
    ASSERT_EQ(caba.CantidadRobotsActivos(), 2);

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
    ASSERT_EQ(caba.CantidadEstaciones(), 3);
    ASSERT_EQ(caba.CantidadRobotsActivos(), 3);
    ASSERT_EQ(caba.IesimoRobotActivo(2), 2);
    ASSERT_EQ(caba.IesimaEstacion(2), "Martinez");
    ASSERT_EQ(caba.CantidadDeSendasParaEstacion("Martinez"), 2);
    ASSERT_EQ(caba.CantidadDeSendasParaEstacion("Belgrano"), 2);    
    ASSERT_EQ(caba.IesimaEstacionDeSenda("Martinez", 1), "Retiro");
    ASSERT_EQ(caba.IesimaEstacionDeSenda("Retiro", 2), "Martinez");
    ASSERT_EQ(caba.IesimaRestriccionDeSenda("Belgrano", 1), "trenDePasajeros || trenDeCarga && !trenDeLaAlegria");


    caba.Mover(1, "Belgrano");
    caba.Mover(2, "Belgrano");
    ASSERT_EQ(caba.ElMasInfractor(), 2);
    ASSERT_EQ(caba.EstacionActualIesimoRobotActivo(2), "Belgrano");    
    ASSERT_EQ(caba.EstacionActualIesimoRobotActivo(1), "Belgrano");
}

int main(int argc, char **argv)
{
   RUN_TEST(test_ciudad_simple);
   RUN_TEST(test_ciudad_con_movimientos);

    /******************************************************************
     * TODO: escribir casos de test exhaustivos para todas            *
     * las funcionalidades del módulo.                                *
     * La interacción con el TAD Ciudad se debe hacer exclusivamente  *
     * a través de la interfaz del driver.                            *
     ******************************************************************/
	const std::string word_list[] = { "about", "after", "again", "air", "all", "along", "also", "an", "and", "another", "any", "are", "around", "as", "at", "away", "back", "be", "because", "been", "before", "below", "between", "both", "but", "by", "came", "can", "come", "could", "day", "did", "different", "do", "does", "do't", "down", "each", "end", "even", "every", "few", "find", "first", "for", "found", "from", "get", "give", "go", "good", "great", "had", "has", "have", "he", "help", "her", "here", "him", "his", "home", "house", "how", "I", "if", "in", "into", "is", "it", "its", "just", "know", "large", "last", "left", "like", "line", "little", "long", "look", "made", "make", "man", "many", "may", "me", "men", "might", "more", "most", "Mr.", "must", "my", "name", "never", "new", "next", "no", "not", "now", "number", "of", "off", "old", "on", "one", "only", "or", "other", "our", "out", "over", "own", "part", "people", "place", "put", "read", "right", "said", "same", "saw", "say", "see", "she", "should", "show", "small", "so", "some", "something", "sound", "still", "such", "take", "tell", "than", "that", "the", "them", "then", "there", "these", "they", "thing", "think", "this", "those", "thought", "three", "through", "time", "to", "together", "too", "two", "under", "up", "us", "use", "very", "want", "water", "way", "we", "well", "went", "were", "what", "when", "where", "which", "while", "who", "why", "will", "with", "word", "work", "world", "would", "write", "year", "you", "your", "was", };

    DiccString<int>* dictest = new DiccString<int>();
    for (int i = 0; i < 187; ++i) {
        dictest->Definir(word_list[i], i);
        ASSERT(dictest->Definido(word_list[i]));
        ASSERT_EQ(dictest->Obtener(word_list[i]), i);
    }
    delete dictest;

    DiccString<std::string>* dic_test_string = new DiccString<std::string>();
    for (int i = 0; i < 187; ++i) {
        dic_test_string->Definir(word_list[i], word_list[i]);
        ASSERT(dic_test_string->Definido(word_list[i]));
        ASSERT_EQ(dic_test_string->Obtener(word_list[i]), word_list[i]);
    }
    delete dic_test_string;

    DiccString<DiccString<int> >* compuesto = new DiccString<DiccString<int> >();

    for (int i = 0; i < 187; ++i){
        compuesto->Definir(word_list[i], DiccString<int>());
        compuesto->Obtener(word_list[i]).Definir(word_list[i], i);

        ASSERT_EQ(compuesto->Obtener(word_list[i]).Obtener(word_list[i]), i);
    }
    delete compuesto;
    std::cout << "El dicc string funca, falta ver memoria" << std::endl;
    std::cout << "Test terminado" << std::endl;

    return 0;
}
