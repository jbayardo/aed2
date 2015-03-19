cmake_minimum_required(VERSION 2.8.4)
project(TP3)

INCLUDE_DIRECTORIES(include)
set(CMAKE_CXX_FLAGS "-g ")
set(SOURCE_FILES
	tests/tests.cpp
    tests/testCiudad.cpp
    tests/testColaDePrioridad.cpp
    tests/testDiccString.cpp
    tests/testMapa.cpp
    tests/testRestriccion.cpp
	src/ArbolSintactico.cpp
	src/Driver.cpp
	src/Restriccion.cpp
	src/ConjRapidoString.cpp
	src/Mapa.cpp
	src/Ciudad.cpp)
add_executable(TP3 ${SOURCE_FILES})
