// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include "mini_test.h"
#include "arturo.h"

#include <iostream>

template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
 }

/*
 * Crea una mesa de int vacia y no agrega elementos
 */
void check_crear_mesa_vacia() {
  Arturo<int> mesa;

  ASSERT_EQ(mesa.esVacia(), true);
  ASSERT_EQ(mesa.tamanio(), 0);
}


/*
 * Crea un Arturo de Arturos.
 */
void check_arturo_de_arturo(){
	Arturo<string> mesa1;
	Arturo<string> mesa2;
	Arturo< Arturo<string> > dobleMesa;

	dobleMesa.sentarArturo(mesa1);
	dobleMesa.incorporarCaballero(mesa2);

	ASSERT(dobleMesa.caballeroActual() == mesa1);
}

void check_tamanio() {
    Arturo<int> test;
    test.sentarArturo(1);
    test.incorporarCaballero(2);
    test.incorporarCaballero(3);
    test.incorporarCaballero(4);
    ASSERT_EQ(test.tamanio(), 4);
}

void check_cambio_turno() {
    Arturo<int> test;
    test.sentarArturo(1);
    test.incorporarCaballero(2);
    test.incorporarCaballero(3);
    test.incorporarCaballero(4);
    ASSERT_EQ(test.caballeroActual(), 1);
    test.proximoCaballero();
    ASSERT_EQ(test.caballeroActual(), 4);
    test.proximoCaballero();
    ASSERT_EQ(test.caballeroActual(), 3);
    test.caballeroAnterior();
    ASSERT_EQ(test.caballeroActual(), 4);
    test.hablaArturo();
    ASSERT_EQ(test.caballeroActual(), 1);
    test.proximoCaballero();
    ASSERT_EQ(test.caballeroActual(), 3);
    test.proximoCaballero();
    ASSERT_EQ(test.caballeroActual(), 2);
}

void check_expulsar() {
    Arturo<int> test;
    test.sentarArturo(1);
    test.incorporarCaballero(4);
    test.incorporarCaballero(3);
    test.incorporarCaballero(2);
    ASSERT_EQ(test.caballeroActual(), 1);
    test.expulsarCaballero(2);
    test.proximoCaballero();
    ASSERT_EQ(test.caballeroActual(), 3);
    test.expulsarCaballero(4);
    test.proximoCaballero();
    ASSERT_EQ(test.caballeroActual(), 1);
    test.caballeroAnterior();
    ASSERT_EQ(test.caballeroActual(), 3);
    test.caballeroAnterior();
    test.expulsarCaballero(3);
    ASSERT_EQ(test.caballeroActual(), 1);
    test.expulsarCaballero(1);
    ASSERT_EQ(test.tamanio(), 0);
}

int main() {
  RUN_TEST(check_crear_mesa_vacia);
  RUN_TEST(check_arturo_de_arturo);
  RUN_TEST(check_tamanio);
  RUN_TEST(check_cambio_turno);
  RUN_TEST(check_expulsar);
  return 0;
}

