#include "Ciudad.h"

Ciudad::Ciudad(const Mapa &m){
	Conj<aed2::Estacion>::const_Iterador it = m.Estaciones();

	while (it.HaySiguiente()){
		robotsEnEstacion.Definir(it.Siguiente(), new ColaDePrioridad<robot*>());
		it.Avanzar();
	}
	robotsEnEstacion.Definir(it.Siguiente(), new ColaDePrioridad<robot*>());
	mapa = m;
}

Ciudad::~Ciudad(){
}

void Ciudad::Entrar(const ConjRapidoString &ts, const aed2::Estacion &e){
//	iEntrar(in ts : conjRapidoString, in e : estacion, in/out c : city)
//	var rob : robot = 
//		tags: &ts,
//		infracciones: 0,
//		rur: ProximoRUR(city),
//		infringe_restriccion: Vacia(),
//		estacion: e,
//		mi_estacion: Encolar(obtener(robotsEnEstacion, e), rob)
//
//	var it : ItVectorPointer(Restriccion) = Sendas(c.mapa)
//
//	while HayMas?(it) do
//		AgregarAtras(rob.infringe_restriccion, no Verifica?(ts, *Actual(it)))
//        Avanzar(it)
//	end while
//
//	AgregarAtras(c.robots, &rob)
//end function
	robot* rob = new robot(ProximoRUR(), 0, ts, e);
	rob->mi_estacion = robotsEnEstacion.Obtener(e).Encolar(rob);

	Vector<Restriccion_*>::const_Iterador it = this->mapa.Sendas();

	while (it.HaySiguiente()){
		rob->infringe_restriccion.AgregarAtras(!it.Siguiente()->Verifica(ts));
		it.Avanzar();
	}

	this->robots.AgregarAtras(rob);
}

void Ciudad::Mover(const RUR rur, const aed2::Estacion e){
}

void Ciudad::Inspeccion(const aed2::Estacion e){
}

RUR Ciudad::ProximoRUR() const{
	return robots.Longitud();
}

Mapa Ciudad::iMapa(){ //referencia constante?
	return mapa;
}

Vector<Ciudad::robot*>::const_Iterador Ciudad::Robots() const{
	return robots.CrearIt();
}

aed2::Estacion Ciudad::Estacion(const RUR u) const{
	return robots[u]->estacion;
}

Conj<Restriccion>::const_Iterador Ciudad::Tags(const RUR u) const{
	return robots[u]->tags.CrearIt();
}

Nat Ciudad::nInfracciones(const RUR u) const{
	return robots[u]->infracciones;
}
