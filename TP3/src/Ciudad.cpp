#include "../include/Ciudad.h"

Ciudad::Ciudad(const Mapa &m){
	DiccString<ColaDePrioridad<robot>> robots_en_estacion;
	Conj<string>::Iterador it = m.estaciones.CrearIt();

	while (it.HaySiguiente()){
		ColaDePrioridad<robot>* aux = new ColaDePrioridad<robot>;
		robots_en_estacion.Definir(it.Siguiente(), *aux);
		it.Avanzar();
	}
	// Definir(robots_en_estacion, *it, Crear()) SAY WAAAAAAAAAAAAAAAAAAAAAAAAT
	this->robotsEnEstacion = robots_en_estacion;
	// this->mapa = Mapa(m);
}

Ciudad::~Ciudad(){
}

void Ciudad::Entrar(const ConjRapidoString &ts, const Estacion &e){
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
	Nat i = 0;
	robot* aux = new robot(this->ProximoRUR(), i, &ts, e);
	aux->mi_estacion = this->robotsEnEstacion.Obtener(e).Encolar(*aux);
	VectorPointer<Restriccion>::Iterador it = this->Mapa.Sendas;

	while (it.HayMas()){
		aux->infringe_restriccion.AgregarAtras(!it.Actual()->Verifica(ts));
		it.Avanzar();
	}

	this->robots.AgregarAtras(&aux);
}

void Ciudad::Mover(const RUR rur, const Estacion e){
}

void Ciudad::Inspeccion(const Estacion e){
}

RUR Ciudad::ProximoRUR(){ 
}

Mapa Ciudad::Mapa(){
}

VectorPointer<robot>::ItVectorPointer Ciudad::Robots(){
}

Estacion Ciudad::iEstacion(const RUR u){
}

Conj<Restriccion>::Iterador Ciudad::Tags(const RUR u){
}

Nat Ciudad::nInfracciones(const RUR u){
}
