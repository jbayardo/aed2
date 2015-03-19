#include "tests.h"
#include "MiniTest.h"

int main(int argc, char *argv[])
{
    RUN_TEST(test_cola_de_prioridad);
    RUN_TEST(test_mapa);
    RUN_TEST(test_restriccion);

    RUN_TEST(test_ciudad_simple);
    RUN_TEST(test_ciudad_con_movimientos);
    RUN_TEST(test_ciudad_cantidad_estaciones);
    RUN_TEST(test_ciudad_cantidad_de_robots_activos);

    RUN_TEST(test_definir_obtener);
    RUN_TEST(test_definir_obtener_string);
    RUN_TEST(test_definir_obtener_dicc_string);


    return 0;
}
