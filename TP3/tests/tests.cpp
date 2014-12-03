#include "tests.h"

int main(int argc, char *argv[]) {
    RUN_TEST(test_cola_de_prioridad);
    RUN_TEST(test_ciudad);
    RUN_TEST(test_dicc_string);
    RUN_TEST(test_mapa);
    RUN_TEST(test_restriccion);

    return 0;
}
