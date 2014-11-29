#include "Mapa.h"

Mapa::Mapa() { }

Mapa::~Mapa() { }

Mapa::Mapa(const Mapa &m) : sendas(m.sendas), conexiones(m.conexiones), estaciones(m.estaciones) { }

void Mapa::Agregar(const Estacion e){
	this->estaciones.Agregar(e);
}

void Mapa::Conectar(const Estacion e1, const Estacion e2, Restriccion_ &r) {   //Fijarse si r se copia o no, si se pone constante no se puede agregar atras
	Nat i = this->sendas.Longitud();
	this->sendas.AgregarAtras(&r);

	if (!this->conexiones.Definido(e1)) {
		DiccString<Nat> aux = DiccString<Nat>();
		this->conexiones.Definir(e1, aux);
	}

	if (!this->conexiones.Definido(e2)) {
		DiccString<Nat> aux = DiccString<Nat>();
		this->conexiones.Definir(e2, aux);
	}

	this->conexiones.Obtener(e1).Definir(e2, i);
	this->conexiones.Obtener(e2).Definir(e1, i);
}

Conj<Estacion>::const_Iterador Mapa::Estaciones() const {
	return this->estaciones.CrearIt();
}

bool Mapa::Conectadas(const Estacion e1, const Estacion e2) const {
	return this->conexiones.Definido(e1) && this->conexiones.Obtener(e1).Definido(e2);
}

Nat Mapa::idSenda(const Estacion e1, const Estacion e2) const {
	return this->conexiones.Obtener(e1).Obtener(e2);
}

Vector<Restriccion_*>::const_Iterador Mapa::Sendas() const {
	return this->sendas.CrearIt();
}


