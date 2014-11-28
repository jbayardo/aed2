#ifndef CIUDAD_H
#define CIUDAD_H 1

#include "aed2/aed2.h"
#include "Tipos.h"
#include "DiccString.h"
#include "ColaDePrioridad.h"
#include "ConjRapidoString.h"
#include "Restriccion.h"
#include "Mapa.h"


class Ciudad
{
private:
	/*Ciudad se representa con city,
	donde city es: tupla(
						robots           : VectorPointer(robot),
						mapa             : Mapa,
						robotsEnEstacion : DiccString(colaPrioridad(robot)))
	donde robot es: tupla(
						rur                  : nat,
						infracciones         : nat,
						tags                 : Puntero(conjRapidoString),
						estacion             : string,
						infringe_restriccion : Vector(Bool),
						mi_estacion          : itCola(robot)
	)*/

	struct robot
	{
	public:
		RUR rur;
		Nat infracciones;
		const ConjRapidoString &tags;
		aed2::Estacion estacion;
		Vector<bool> infringe_restriccion;
		ColaDePrioridad<robot>::Iterador *mi_estacion;
		robot(const RUR rur,
			const Nat infracciones,
			const ConjRapidoString &tags,
			const aed2::Estacion estacion)
				: rur(rur),
				infracciones(infracciones),	
				estacion(estacion),
				tags(tags),
				mi_estacion(NULL){};
	};
	Vector<robot*> robots;
	Mapa mapa;
	DiccString<ColaDePrioridad<robot>> robotsEnEstacion;

public:
	Ciudad(const Mapa &m);
	~Ciudad();
	void Entrar(const ConjRapidoString &ts, const aed2::Estacion &e);
	void Mover(const RUR rur, const aed2::Estacion e);
	void Inspeccion(const aed2::Estacion e);
	RUR ProximoRUR() const;
	Mapa iMapa();
	Vector<robot*>::const_Iterador Robots() const;
	aed2::Estacion Estacion(const RUR u) const;
	Conj<Restriccion_>::Iterador Tags(const RUR u) const;  //ATENCION!: Ver bien si es Restriccion o std::string
	Nat nInfracciones(const RUR u) const;

};

#endif