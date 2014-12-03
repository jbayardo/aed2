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




	ColaDePrioridad<int>* cola = new ColaDePrioridad<int>();

	int random_200[] = { 85, 115, 108, 55, 179, 170, 118, 70, 1, 96, 25, 156, 172, 192, 131, 197, 59, 69, 90, 19, 181, 128, 35, 64, 175, 147, 14, 157, 21, 139, 9, 165, 113, 187, 50, 153, 110, 168, 129, 196, 140, 159, 45, 66, 13, 141, 44, 158, 87, 176, 48, 146, 54, 184, 94, 86, 7, 133, 80, 29, 166, 144, 116, 31, 40, 177, 132, 0, 195, 167, 93, 76, 123, 151, 109, 199, 28, 105, 95, 51, 32, 149, 98, 198, 53, 134, 111, 84, 79, 89, 126, 16, 122, 154, 83, 162, 142, 183, 65, 136, 178, 190, 106, 119, 33, 148, 155, 169, 160, 77, 68, 104, 23, 194, 188, 41, 92, 5, 99, 72, 58, 52, 61, 67, 42, 20, 161, 57, 101, 117, 17, 71, 164, 125, 36, 56, 38, 78, 49, 137, 102, 150, 103, 8, 6, 43, 124, 22, 189, 174, 30, 121, 173, 193, 100, 171, 81, 127, 18, 74, 180, 152, 12, 26, 11, 27, 114, 182, 73, 120, 34, 75, 185, 107, 39, 97, 143, 88, 186, 15, 82, 138, 4, 130, 91, 112, 2, 46, 145, 191, 135, 60, 10, 24, 37, 47, 63, 3, 163, 62 };
	int sorted_200[200];


	for (int j = 0; j < 200; ++j) {
		ColaDePrioridad<int>::Iterador* it = cola->Encolar(random_200[j]);
		delete it;
	}
	std::cout << "Encole todo" << std::endl;


	for (int k = 0; cola->Tamano(); k++) {
		sorted_200[k] = cola->Desencolar();
	}

	std::cout << "Desencole todo" << std::endl;

	ASSERT_EQ(cola->Tamano(), 0);

	for (int l = 0; l < 200; l++) {
		ASSERT_EQ(sorted_200[l], 199 - l);
	}

	std::cout << "La cola funca, falta ver memoria" << std::endl;

	delete cola;



	std::cout << "Test terminado" << std::endl;

	Mapa* mapatest = new Mapa();
	mapatest->Agregar("Belgrano");//
	mapatest->Agregar("Palermo");//
	mapatest->Agregar("Recoleta");//
	mapatest->Agregar("Almagro");
	mapatest->Agregar("Microcentro");
	mapatest->Agregar("Retiro");//
	mapatest->Agregar("Constitucion");//

	ArbolSintactico* expr = ArbolSintactico::LeerDeString("negros & !autocheto & (bondi | taxi | subte | auto)");
	mapatest->Conectar("Retiro", "Constitucion", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Retiro", "Constitucion"));
	ASSERT(mapatest->Conectadas("Constitucion", "Retiro"));
	delete expr;

	expr = ArbolSintactico::LeerDeString("!negros & !bondi & (autocheto | auto)");
	mapatest->Conectar("Recoleta", "Palermo", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Recoleta", "Palermo"));
	ASSERT(mapatest->Conectadas("Palermo" ,"Recoleta"));
	delete expr;

	expr = ArbolSintactico::LeerDeString("bondi | auto | autocheto | taxi");
	mapatest->Conectar("Palermo", "Belgrano", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Belgrano", "Palermo"));
	ASSERT(mapatest->Conectadas("Palermo", "Belgrano"));
	delete expr;

	expr = ArbolSintactico::LeerDeString("auto | !auto");
	mapatest->Conectar("Microcentro", "Almagro", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Microcentro", "Almagro"));
	ASSERT(mapatest->Conectadas("Almagro", "Microcentro"));
	delete expr;

	expr = ArbolSintactico::LeerDeString("auto | !auto");
	mapatest->Conectar("Palermo", "Almagro", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Palermo", "Almagro"));
	ASSERT(mapatest->Conectadas("Almagro", "Palermo"));
	delete expr;

	expr = ArbolSintactico::LeerDeString("bondi | subte");
	mapatest->Conectar("Microcentro", "Retiro", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Retiro", "Microcentro"));
	ASSERT(mapatest->Conectadas("Microcentro", "Retiro"));
	delete expr;

	expr = ArbolSintactico::LeerDeString("bondi | subte");
	mapatest->Conectar("Microcentro", "Constitucion", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Constitucion", "Microcentro"));
	ASSERT(mapatest->Conectadas("Microcentro", "Constitucion"));
	delete expr;
	
	delete mapatest;

    return 0;
}
