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

/*******************************************************************************
                            TESTS DE LA CATEDRA
 ******************************************************************************/

/*
 * Crea una mesa de int vacia y no agrega elementos
 */
void check_crear_mesa_vacia() {
  Arturo<int> mesa;

  ASSERT_EQ(mesa.esVacia(), true);

  ASSERT_EQ(mesa.tamanio(), 0);
}

void check_agregar_a_arturo(){
        Arturo<int> mesa;
        ASSERT(!mesa.arturoPresente());

        int arturo = 10;

        mesa.sentarArturo(arturo);

        ASSERT(mesa.arturoPresente());
        ASSERT_EQ(mesa.caballeroActual(), 10);
        ASSERT(!mesa.esVacia());
        ASSERT_EQ(mesa.tamanio(), 1);
}

void check_agregar_dos_caballeros(){
        Arturo<int> mesa;
        int arturo = 10, cab1 = 1, cab2 = 2;

        mesa.sentarArturo(arturo);

        mesa.incorporarCaballero(cab1);
        ASSERT_EQ(mesa.tamanio(), 2);


        mesa.incorporarCaballero(cab2);
        ASSERT_EQ(mesa.tamanio(), 3);

}

void check_mostrar_arturo(){
        Arturo<int> mesa;

        ASSERT_EQ(to_s(mesa), "[]");


        int arturo = 10, cab1 = 1, cab2 = 2;

        mesa.sentarArturo(arturo);
        ASSERT_EQ(to_s(mesa), "[ARTURO(10)]");

        mesa.incorporarCaballero(cab1);
        ASSERT_EQ(to_s(mesa), "[ARTURO(10),1]");

        mesa.incorporarCaballero(cab2);
        ASSERT_EQ(to_s(mesa), "[ARTURO(10),2,1]");

}

void check_agregar_y_sacar_caballeros(){
        Arturo<int> mesa;
        int arturo = 10, cab1 = 1, cab2 = 2;

        mesa.sentarArturo(arturo);

        mesa.incorporarCaballero(cab1);
        ASSERT_EQ(mesa.tamanio(), 2);
        ASSERT_EQ(to_s(mesa), "[ARTURO(10),1]");

        mesa.incorporarCaballero(cab2);
        ASSERT_EQ(mesa.tamanio(), 3);
        ASSERT_EQ(to_s(mesa), "[ARTURO(10),2,1]");

        mesa.expulsarCaballero(cab2);
        ASSERT_EQ(mesa.tamanio(), 2);
        ASSERT_EQ(to_s(mesa), "[ARTURO(10),1]");
}

void check_copiar_y_comparar(){
        Arturo<int> mesa;
        int arturo = 10, cab1 = 1, cab2 = 2;
        mesa.sentarArturo(arturo);
        mesa.incorporarCaballero(cab1);
        mesa.incorporarCaballero(cab2);
        Arturo<int> mesa2(mesa);
        ASSERT_EQ(mesa.tamanio(), mesa2.tamanio());
        ASSERT_EQ(to_s(mesa), "[ARTURO(10),2,1]");
        ASSERT_EQ(to_s(mesa2), "[ARTURO(10),2,1]");
        ASSERT(mesa==mesa2);

        mesa.expulsarCaballero(2);
        ASSERT(!(mesa==mesa2));
        ASSERT_EQ(to_s(mesa), "[ARTURO(10),1]");
        ASSERT_EQ(to_s(mesa2), "[ARTURO(10),2,1]");
        mesa.expulsarCaballero(1);
        mesa.expulsarCaballero(10);

        ASSERT(!(mesa==mesa2));
        ASSERT_EQ(to_s(mesa), "[]");
        ASSERT_EQ(to_s(mesa2), "[ARTURO(10),2,1]");
}

void check_caballeroActual(){
        Arturo<string> mesa;
        string arturo = "Arturo", cab1 = "Beto", cab2 = "Cleto", cab3 = "Dante";
        mesa.sentarArturo(arturo);
        mesa.incorporarCaballero(cab3);
        mesa.incorporarCaballero(cab2);
        mesa.incorporarCaballero(cab1);
        ASSERT_EQ(mesa.tamanio(), 4);

        ASSERT_EQ(to_s(mesa), "[ARTURO(Arturo),Beto,Cleto,Dante]");
        ASSERT_EQ(mesa.caballeroActual(), "Arturo");
        mesa.proximoCaballero();
        ASSERT_EQ(to_s(mesa), "[Beto,Cleto,Dante,ARTURO(Arturo)]");
        ASSERT_EQ(mesa.caballeroActual(), "Beto");
        mesa.proximoCaballero();
        ASSERT_EQ(to_s(mesa), "[Cleto,Dante,ARTURO(Arturo),Beto]");
        ASSERT_EQ(mesa.caballeroActual(), "Cleto");
        mesa.proximoCaballero();
        ASSERT_EQ(to_s(mesa), "[Dante,ARTURO(Arturo),Beto,Cleto]");
        ASSERT_EQ(mesa.caballeroActual(), "Dante");
        mesa.proximoCaballero();
        ASSERT_EQ(to_s(mesa), "[ARTURO(Arturo),Beto,Cleto,Dante]");
        ASSERT_EQ(mesa.caballeroActual(), "Arturo");

        mesa.caballeroAnterior();
        ASSERT_EQ(to_s(mesa), "[Dante,ARTURO(Arturo),Beto,Cleto]");
        ASSERT_EQ(mesa.caballeroActual(), "Dante");
        mesa.caballeroAnterior();
        ASSERT_EQ(to_s(mesa), "[Cleto,Dante,ARTURO(Arturo),Beto]");
        ASSERT_EQ(mesa.caballeroActual(), "Cleto");
        mesa.caballeroAnterior();
        ASSERT_EQ(to_s(mesa), "[Beto,Cleto,Dante,ARTURO(Arturo)]");
        ASSERT_EQ(mesa.caballeroActual(), "Beto");
        mesa.caballeroAnterior();
        ASSERT_EQ(to_s(mesa), "[ARTURO(Arturo),Beto,Cleto,Dante]");
        ASSERT_EQ(mesa.caballeroActual(), "Arturo");
}

void check_hablaArturo(){
        Arturo<string> mesa;
        string arturo = "Arturo", cab1 = "Beto", cab2 = "Cleto", cab3 = "Dante";
        mesa.sentarArturo(arturo);
        mesa.incorporarCaballero(cab3);
        mesa.incorporarCaballero(cab2);
        mesa.incorporarCaballero(cab1);

        mesa.proximoCaballero();
        mesa.proximoCaballero();
        ASSERT_EQ(mesa.caballeroActual(), "Cleto");
        ASSERT_EQ(to_s(mesa), "[Cleto,Dante,ARTURO(Arturo),Beto]");
        mesa.hablaArturo();
        ASSERT_EQ(mesa.caballeroActual(), "Arturo");
        ASSERT_EQ(to_s(mesa), "[ARTURO(Arturo),Beto,*Cleto,Dante]");
        mesa.proximoCaballero();
        ASSERT_EQ(mesa.caballeroActual(), "Dante");
        ASSERT_EQ(to_s(mesa), "[Dante,ARTURO(Arturo),Beto,Cleto]");
        mesa.hablaArturo();
        ASSERT_EQ(mesa.caballeroActual(), "Arturo");
        ASSERT_EQ(to_s(mesa), "[ARTURO(Arturo),Beto,Cleto,*Dante]");
        mesa.caballeroAnterior();
        ASSERT_EQ(mesa.caballeroActual(), "Cleto");
        ASSERT_EQ(to_s(mesa), "[Cleto,Dante,ARTURO(Arturo),Beto]");
        mesa.hablaArturo();
        ASSERT_EQ(mesa.caballeroActual(), "Arturo");
        ASSERT_EQ(to_s(mesa), "[ARTURO(Arturo),Beto,*Cleto,Dante]");
        mesa.expulsarCaballero("Cleto");
        ASSERT_EQ(mesa.caballeroActual(), "Arturo");
        ASSERT_EQ(to_s(mesa), "[ARTURO(Arturo),Beto,Dante]");
        ASSERT_EQ(mesa.tamanio(), 3);
        mesa.proximoCaballero();
        ASSERT_EQ(mesa.caballeroActual(), "Beto");
        ASSERT_EQ(to_s(mesa), "[Beto,Dante,ARTURO(Arturo)]");
        mesa.proximoCaballero();
        ASSERT_EQ(mesa.caballeroActual(), "Dante");
        ASSERT_EQ(to_s(mesa), "[Dante,ARTURO(Arturo),Beto]");
}

void check_cambioDeLugar(){
        Arturo<string> mesa;
        string arturo = "Arturo", cab1 = "Beto", cab2 = "Cleto", cab3 = "Dante";
        mesa.sentarArturo(arturo);
        mesa.incorporarCaballero(cab3);
        mesa.incorporarCaballero(cab2);
        mesa.incorporarCaballero(cab1);

        mesa.proximoCaballero();
        mesa.proximoCaballero();
        ASSERT_EQ(mesa.caballeroActual(), "Cleto");
        ASSERT_EQ(to_s(mesa), "[Cleto,Dante,ARTURO(Arturo),Beto]");
        mesa.cambioDeLugar("Cleto");
        ASSERT_EQ(mesa.caballeroActual(), "Cleto");
        ASSERT_EQ(to_s(mesa), "[Cleto,ARTURO(Arturo),Dante,Beto]");
        mesa.proximoCaballero();
        ASSERT_EQ(mesa.caballeroActual(), "Arturo");
        ASSERT_EQ(to_s(mesa), "[ARTURO(Arturo),Dante,Beto,Cleto]");
        mesa.proximoCaballero();
        ASSERT_EQ(mesa.caballeroActual(), "Dante");
        ASSERT_EQ(to_s(mesa), "[Dante,Beto,Cleto,ARTURO(Arturo)]");
        mesa.hablaArturo();
        ASSERT_EQ(mesa.caballeroActual(), "Arturo");
        ASSERT_EQ(to_s(mesa), "[ARTURO(Arturo),*Dante,Beto,Cleto]");
        mesa.proximoCaballero();
        ASSERT_EQ(mesa.caballeroActual(), "Beto");
        ASSERT_EQ(to_s(mesa), "[Beto,Cleto,ARTURO(Arturo),Dante]");
}


void check_expulsar_no_saca_a_arturo(){

        Arturo<string> mesa;
        string arturo = "Arturo", cab1 = "Beto", cab2 = "Cleto", cab3 = "Dante";
        mesa.sentarArturo(arturo);
        mesa.incorporarCaballero(cab3);
        mesa.incorporarCaballero(cab2);
        mesa.incorporarCaballero(cab1);


        Arturo<string> mesa2(mesa);

        mesa.expulsarCaballero(arturo);

        ASSERT(mesa2 == mesa);
}


void check_arturo_de_arturo(){
        Arturo<string> mesa1;
        string arturo1 = "Arturo1", cab1 = "Beto", cab2 = "Cleto", cab3 = "Dante", cab4 = "Jeremías";
        mesa1.sentarArturo(arturo1);
        mesa1.incorporarCaballero(cab3);
        mesa1.incorporarCaballero(cab2);
        mesa1.incorporarCaballero(cab1);

        Arturo<string> mesa2;
        string arturo2 = "Arturo2";
        mesa2.sentarArturo(arturo2);
        mesa2.incorporarCaballero(cab4);

        Arturo< Arturo<string> > dobleMesa;

        dobleMesa.sentarArturo(mesa2);
        dobleMesa.incorporarCaballero(mesa1);

        ASSERT(dobleMesa.caballeroActual() == mesa2);

        ASSERT_EQ(to_s(dobleMesa), "[ARTURO([ARTURO(Arturo2),Jeremías]),[ARTURO(Arturo1),Beto,Cleto,Dante]]");
}


void check_interrumpidos_distintos_dan_mesas_distintas(){
        Arturo<string> mesa1;
        string arturo = "Arturo", cab1 = "Beto", cab2 = "Cleto", cab3 = "Dante";
        mesa1.sentarArturo(arturo);
        mesa1.incorporarCaballero(cab3);
        mesa1.incorporarCaballero(cab2);
        mesa1.incorporarCaballero(cab1);
        mesa1.proximoCaballero();
        ASSERT_EQ(to_s(mesa1), "[Beto,Cleto,Dante,ARTURO(Arturo)]");

        Arturo<string> mesa2;
        mesa2.sentarArturo(arturo);
        mesa2.incorporarCaballero(cab3);
        mesa2.incorporarCaballero(cab2);
        mesa2.incorporarCaballero(cab1);
        mesa2.proximoCaballero();
        mesa2.proximoCaballero();
        ASSERT_EQ(to_s(mesa2), "[Cleto,Dante,ARTURO(Arturo),Beto]");

        mesa1.hablaArturo();
        ASSERT_EQ(to_s(mesa1), "[ARTURO(Arturo),*Beto,Cleto,Dante]");
        mesa2.hablaArturo();
        ASSERT_EQ(to_s(mesa2), "[ARTURO(Arturo),Beto,*Cleto,Dante]");

        ASSERT(!(mesa1 == mesa2));
}


void check_arturos_distintos_son_mesas_distintas(){
        Arturo<string> mesa1;
        string arturo1 = "Arturo1", cab1 = "Beto", cab2 = "Cleto", cab3 = "Dante";
        mesa1.sentarArturo(arturo1);
        mesa1.incorporarCaballero(cab3);
        mesa1.incorporarCaballero(cab2);
        mesa1.incorporarCaballero(cab1);

        Arturo<string> mesa2;
        string arturo2 = "Arturo2";
        mesa2.sentarArturo(arturo2);
        mesa2.incorporarCaballero(cab3);
        mesa2.incorporarCaballero(cab2);
        mesa2.incorporarCaballero(cab1);

        ASSERT_EQ(to_s(mesa1), "[ARTURO(Arturo1),Beto,Cleto,Dante]");
        ASSERT_EQ(to_s(mesa2), "[ARTURO(Arturo2),Beto,Cleto,Dante]");
        ASSERT(!(mesa1 == mesa2));
}


void check_dar_una_vuelta_es_la_misma_mesa(){
        Arturo<string> mesa1;
        string arturo = "Arturo", cab1 = "Beto", cab2 = "Cleto", cab3 = "Dante";
        mesa1.sentarArturo(arturo);
        mesa1.incorporarCaballero(cab3);
        mesa1.incorporarCaballero(cab2);
        mesa1.incorporarCaballero(cab1);
        ASSERT_EQ(to_s(mesa1), "[ARTURO(Arturo),Beto,Cleto,Dante]");

        Arturo<string> mesa2;
        mesa2.sentarArturo(arturo);
        mesa2.incorporarCaballero(cab3);
        mesa2.incorporarCaballero(cab2);
        mesa2.incorporarCaballero(cab1);
        ASSERT_EQ(to_s(mesa2), "[ARTURO(Arturo),Beto,Cleto,Dante]");

        ASSERT(mesa1 == mesa2);

        mesa1.proximoCaballero();
        mesa1.proximoCaballero();
        mesa1.proximoCaballero();
        mesa1.proximoCaballero();
        ASSERT_EQ(to_s(mesa1), "[ARTURO(Arturo),Beto,Cleto,Dante]");

        ASSERT(mesa1 == mesa2);
}

int main() {
        RUN_TEST(check_crear_mesa_vacia);
        RUN_TEST(check_agregar_a_arturo);
        RUN_TEST(check_agregar_dos_caballeros);
        RUN_TEST(check_mostrar_arturo);
        RUN_TEST(check_agregar_y_sacar_caballeros);
        RUN_TEST(check_copiar_y_comparar);
        RUN_TEST(check_caballeroActual);
        RUN_TEST(check_hablaArturo);
        RUN_TEST(check_cambioDeLugar);
        RUN_TEST(check_expulsar_no_saca_a_arturo);
        RUN_TEST(check_arturo_de_arturo);
        RUN_TEST(check_interrumpidos_distintos_dan_mesas_distintas);
        RUN_TEST(check_arturos_distintos_son_mesas_distintas);
        RUN_TEST(check_dar_una_vuelta_es_la_misma_mesa);

        RUN_TEST(check_cambio_turno);
        RUN_TEST(check_expulsar);
        return 0;
}
