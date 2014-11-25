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

void Ciudad::Entrar(const conjRapidoString &ts, const Estacion &e){
}

void Ciudad::Mover(const RUR rur, const Estacion e){
}

void Ciudad::Inspeccion(const Estacion e){
}

Nat Ciudad::ProximoRUR(){ 
	return 8; 
}

Mapa Ciudad::Mapa(){
}

VectorPointer::ItVectorPointer<robot> Ciudad::Robots(){
}

Estacion Ciudad::Estacion(const RUR u){
}

Conj<Restriccion>::Iterador Ciudad::Tags(const RUR u){
}

Nat Ciudad::nInfracciones(const RUR u){
}
