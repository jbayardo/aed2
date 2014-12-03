#include "Mapa.h"
#include "MiniTest.h"

void test_agregar() {
    Mapa mapa = Mapa();

    mapa.Agregar("CABA");
    mapa.Agregar("MDQ");
    mapa.Agregar("ESTA");

    mapa.Conectar("CABA", "ESTA");
    mapa.Conectar("ESTA", "MDQ");
    mapa.Conectar("MDQ, CABA");

    ASSERT(mapa.Conectadas("CABA", "ESTA"));
    ASSERT(mapa.Conectadas("ESTA", "MDQ"));
    ASSERT(mapa.Conectadas("MDQ", "CABA"));

    ASSERT(mapa.Conectadas("ESTA", "CABA"));
    ASSERT(mapa.Conectadas("MDQ", "ESTA"));
    ASSERT(mapa.Conectadas("CABA", "MDQ"));

    mapa.Agregar("LA");
    mapa.Conectar("LA", "CABA");
    ASSERT(mapa.Conectadas("LA", "CABA"));
    ASSERT(!mapa.Conectadas("LA", "ESTA"));
}
