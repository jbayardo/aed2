#include "Ciudad.h"

Ciudad::Ciudad(const Mapa *m): mapa(m){
	Conj<aed2::Estacion>::const_Iterador it = mapa->Estaciones();

	while (it.HaySiguiente()){
		robotsEnEstacion.Definir(it.Siguiente(), ColaDePrioridad<robot>());
		it.Avanzar();
	}
}

Ciudad::~Ciudad(){
	for (int i = 0; i < robots.Longitud(); ++i) {
		if (robots[i] != NULL){
			delete robots[i];
		}
	}
	delete this->mapa;
}

void Ciudad::Entrar(ConjRapidoString* ts, const aed2::Estacion &e){
	assert(robotsEnEstacion.Definido(e));

	robot* rob = new robot(ProximoRUR(), 0, ts, e);
	rob->mi_estacion = robotsEnEstacion.Obtener(e).Encolar(*rob);

	Vector<Restriccion_*>::const_Iterador it = this->mapa->Sendas();

	while (it.HaySiguiente()){
		rob->infringe_restriccion.AgregarAtras(!it.Siguiente()->Verifica(ts));
		it.Avanzar();
	}

	this->robots.AgregarAtras(rob);
}

void Ciudad::Mover(const RUR rur, const aed2::Estacion e){
	robot* rob = robots[rur];
	robotsEnEstacion.Obtener(rob->estacion).Desencolar(rob->mi_estacion);

	Nat id_senda = mapa->idSenda(rob->estacion, e);

	if (rob->infringe_restriccion[id_senda]){
		rob->infracciones++;
	}

	rob->estacion = e;
	delete rob->mi_estacion;
	rob->mi_estacion = NULL; // NO BORRAR; Se usa para distinguir robots de cola

	rob->mi_estacion = robotsEnEstacion.Obtener(e).Encolar(*rob);
}


void Ciudad::Inspeccion(const aed2::Estacion e){
	ColaDePrioridad<robot>& cola = robotsEnEstacion.Obtener(e);

	if (cola.Tamano() > 0){
		robot rob = cola.Desencolar();
		delete robots[rob.rur];
		robots[rob.rur] = NULL;
	}

}

RUR Ciudad::ProximoRUR() const{
	return robots.Longitud();
}

const Mapa* Ciudad::iMapa() const{
	return mapa;
}

Ciudad::const_Iterador Ciudad::Robots(){
	return const_Iterador(robots);
}

aed2::Estacion Ciudad::Estacion(const RUR u) const{
	return robots[u]->estacion;
}

Conj<Restriccion>::const_Iterador Ciudad::Tags(const RUR u) const{
	return robots[u]->tags->CrearIt();
}

Nat Ciudad::nInfracciones(const RUR u) const{
	return robots[u]->infracciones;
}
