#include "Driver.h"
#include "ArbolSintactico.h"

namespace aed2 {

	Driver::Driver(const Conj<Estacion> &estacionesIniciales) {
		this->mapa = new Mapa();

		Conj<Estacion>::const_Iterador it = estacionesIniciales.CrearIt();
		while(it.HaySiguiente()){
			this->mapa->Agregar(it.Siguiente());
			it.Avanzar();
		}

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
	//Encuentro la senda iesima de una estacion
	Conj<Estacion>::const_Iterador itE = this->mapa->Estaciones();
	Nat x = 0;
	Estacion e2;
	while (x < i){
		if (this->mapa->Conectadas(itE.Siguiente(), e1)){
			x++;
			e2 = itE.Siguiente();
		}
		if (itE.HaySiguiente()) { itE.Avanzar(); }
	}
	
	//Busco el id de esa senda y itero hasta su restriccion
	Nat idS = this->mapa->idSenda(e1, e2);
	Vector<Restriccion_*>::const_Iterador sendas = this->mapa->Sendas();
	for (Nat x = 0; x < idS; x++){
		sendas.Avanzar();
	}
	
	return sendas.Siguiente()->toRestriccion();
}


	void Driver::AgregarSenda(const Estacion &e1, const Estacion &e2, Restriccion r) {
		// TODO
		ArbolSintactico* expr = ArbolSintactico::LeerDeString(r);
		this->mapa->Conectar(e1, e2, ArboltoRestr(expr));
		delete expr;
	}



Nat Driver::CantidadRobotsActivos() const {
 // TODO
	Ciudad::const_Iterador it = this->ciudad->Robots();
	Nat ret = 0;
	while (it.HaySiguiente()){
		ret++;
		it.Avanzar();
	}
	return ret;
}

RUR Driver::IesimoRobotActivo(Nat i) const {
 // TODO
	Ciudad::const_Iterador it = this->ciudad->Robots();
	for (int x = 0; x < i; x++){
		it.Avanzar();
	}
	return it.Siguiente()->rur_();
}

Estacion Driver::EstacionActualIesimoRobotActivo(Nat i) const {
 // TODO
	Ciudad::const_Iterador it = this->ciudad->Robots();
	for (int x = 0; x < i; x++){
		it.Avanzar();
	}
	return this->ciudad->Estacion(it.Siguiente()->rur_());
}

Conj<Caracteristica> Driver::CaracteristicasIesimoRobotActivo(Nat i) const {
 // TODO
    Ciudad::const_Iterador it = this->ciudad->Robots();
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
    Ciudad::const_Iterador it = this->ciudad->Robots();
	for (int x = 0; x < i; x++){
		it.Avanzar();
	}
	return it.Siguiente()->infracciones_();
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
	ConjRapidoString* adapt = new ConjRapidoString();

	while (it.HaySiguiente()){
		adapt->Agregar(it.Siguiente());
		it.Avanzar();
	}	
	if (this->ciudad == NULL){
		this->ciudad = new Ciudad(*this->mapa);
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
	Restriccion_ *Driver::ArboltoRestr(ArbolSintactico *a) {
		if (a->raiz == "|") {
			return Restriccion_::Or(ArboltoRestr(a->izq), ArboltoRestr(a->der));
		}
		else if (a->raiz == "&") {
			return Restriccion_::And(ArboltoRestr(a->izq), ArboltoRestr(a->der));
		}
		else if (a->raiz == "!") {
			return Restriccion_::Not(ArboltoRestr(a->izq));
		}
		else {
			return Restriccion_::Var(a->raiz);
		}
	}

} // namespace aed2

