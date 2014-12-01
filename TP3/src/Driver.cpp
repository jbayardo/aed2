#include <fcgimisc.h>
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
}

Nat Driver::CantInfraccionesIesimoRobotActivo(Nat i) const {
 // TODO
}

RUR Driver::ElMasInfractor() const {
 // TODO
	Ciudad::const_Iterador r = this->ciudad->Robots();
    RUR max = -1;
    Nat inf = 0;
    while (r.HaySiguiente()){
        if (r.Siguiente()->infracciones_() > inf){
            max = r.Siguiente()->rur_();
        }
        r.Avanzar();
    }
    return max;
}

void Driver::Entrar(const Conj<Caracteristica> &cs, const Estacion &estacionInicial) {
 // TODO
	Conj<Caracteristica>::const_Iterador it = cs.CrearIt();
	ConjRapidoString adapt;

	while (it.HaySiguiente()){
		adapt.Agregar(it.Siguiente());
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

