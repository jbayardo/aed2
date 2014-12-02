#ifndef MAPA_H
#define MAPA_H 1

#include "aed2/aed2.h"
#include "Restriccion.h"
#include "DiccString.h"

class Mapa {
public:
	//Crear() res: Mapa
	Mapa();

	//Copiar(in m : Mapa)  res : Mapa
	Mapa(const Mapa &m);
	~Mapa();

	//Agregar(in/out m : Mapa, in e : estacion)
	void Agregar(const Estacion e);

	//Conectar(in/out m : Mapa, in e1 : estacion, in e2 : estacion, in r : restriccion)
	void Conectar(const Estacion e1, const Estacion e2, Restriccion_* r);

	//Estaciones(in m : Mapa)  res : itConj(string)
	Conj<Estacion>::const_Iterador Estaciones() const;

	//Conectadas?(in m : Mapa, in e1 : estacion, in e2 : estacion)  res : bool
	bool Conectadas(const Estacion e1, const Estacion e2) const;

	//idSenda(in m : Mapa, in e1 : estacion, in e2 : estacion) res : nat
	Nat idSenda(const Estacion e1, const Estacion e2) const;

	//Sendas(in m : Mapa)  res : itVectorPointer(restriccion)
	Vector<Restriccion_*>::const_Iterador Sendas() const;


private:
	Vector<Restriccion_*> sendas;
	DiccString<DiccString<Nat>> conexiones;
	Conj<Estacion> estaciones;
};

#endif