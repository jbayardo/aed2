#include "Driver.h"
#include "ArbolSintactico.h"

namespace aed2 {

Driver::Driver(const Conj<Estacion> &estacionesIniciales) {
    this->mapa = new Mapa();
    this->ciudad = NULL;
}

Driver::~Driver() {
    if (this->mapa != NULL) {
        delete this->mapa;
    }

    if (this->ciudad != NULL) {
        delete this->ciudad;
    }
}

Nat Driver::CantidadEstaciones() const {
    Conj<Estacion>::const_Iterador it = this->mapa->Estaciones();
    Nat output = 0;

    while (it.HaySiguiente()) {
        output++;
        it.Avanzar();
    }

    return output;
}

Estacion Driver::IesimaEstacion(Nat i) const {
    Conj<Estacion>::const_Iterador it = this->mapa->Estaciones();
    Nat j = 0;

    while (it.HaySiguiente() && j < i) {
        j++;
        it.Avanzar();
    }

    return it.Siguiente();
}


Nat Driver::CantidadDeSendasParaEstacion(const Estacion &e) const {
    Conj<Estacion>::const_Iterador it = this->mapa->Estaciones();
    Nat output = 0;

    while (it.HaySiguiente()) {
        if (this->mapa->Conectadas(e, it.Siguiente())) {
            ++output;
        }

        it.Avanzar();
    }

    return output;
}

Estacion Driver::IesimaEstacionDeSenda(const Estacion &e, Nat i) const {
    Conj<Estacion>::const_Iterador it = this->mapa->Estaciones();
    Nat j = 0;

    while (it.HaySiguiente() && j < i) {
        ++j;
        it.Avanzar();
    }

    return it.Siguiente();
}

Restriccion Driver::IesimaRestriccionDeSenda(const Estacion &e1, Nat i) const {
 // TODO
}

void Driver::AgregarSenda(const Estacion &e1, const Estacion &e2, Restriccion r) {
    // TODO
    // Ejemplo uso ArbolSintactico:
    ArbolSintactico* expr = ArbolSintactico::LeerDeString(r);
    std::cout << expr->aString() << std::endl;

    delete expr;
}

Nat Driver::CantidadRobotsActivos() const {
 // TODO
}

RUR Driver::IesimoRobotActivo(Nat i) const {
 // TODO
}

Estacion Driver::EstacionActualIesimoRobotActivo(Nat i) const {
 // TODO
}

Conj<Caracteristica> Driver::CaracteristicasIesimoRobotActivo(Nat i) const {
 // TODO
	Vector<Ciudad::robot*>::const_Iterador it = this->ciudad->Robots();
	for (int x = 0; x < i; x++){
		it.Avanzar();
	}

	Conj<Caracteristica>::const_Iterador cars = it.Siguiente()->tags_().CrearIt();
	Conj<Caracteristica> ret;

	while (cars.HaySiguiente()){
		ret.Agregar(cars.Siguiente());
		cars.Avanzar();
	}

	return ret;
}

Nat Driver::CantInfraccionesIesimoRobotActivo(Nat i) const {
 // TODO
	Vector<Ciudad::robot*>::const_Iterador it = this->ciudad->Robots();
	for (int x = 0; x < i; x++){
		it.Avanzar();
	}
	return it.Siguiente()->infracciones_();
}

RUR Driver::ElMasInfractor() const {
 // TODO
	Vector<Ciudad::robot*>::const_Iterador it = this->ciudad->Robots();
	Nat imax = 0;
	Ciudad::robot *rmax = it.Siguiente();
	while (it.HaySiguiente()){
		if (it.Siguiente()->infracciones_() >= imax){
			imax = it.Siguiente()->infracciones_();
			rmax = it.Siguiente();
		}
		it.Avanzar();
	}
	return rmax->rur_();
}

void Driver::Entrar(const Conj<Caracteristica> &cs, const Estacion &estacionInicial) {
 // TODO
	Conj<Caracteristica>::const_Iterador it = cs.CrearIt();
	ConjRapidoString adapt;

	while (it.HaySiguiente){
		adapt.Agregar(it.Siguiente);
		it.Avanzar();
	}	
	this->ciudad->Entrar(adapt, estacionInicial);
}

void Driver::Mover(RUR robot, const Estacion &destino) {
 // TODO
	this->ciudad->Mover(robot, destino);
}

void Driver::Inspeccion(const Estacion &e) {
	this->ciudad->Inspeccion(e);
    // TODO
}

} // namespace aed2

