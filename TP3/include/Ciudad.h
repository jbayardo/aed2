#ifndef CIUDAD_H
#define CIUDAD_H

#include "../aed2.h"
#include "../include/DiccString.h"
#include "../include/Tipos.h"
#include "../include/ColaDePrioridad.h"
#include "../include/ConjRapidoString.h"

using namespace aed2;
using namespace std;

class Ciudad
{
public:

	Ciudad(const Mapa &m);
	~Ciudad();
	void Entrar(const ConjRapidoString &ts, const Estacion &e);
	void Mover(const RUR rur, const Estacion e);
	void Inspeccion(const Estacion e);
	RUR ProximoRUR();
	Mapa Mapa();
	VectorPointer::ItVectorPointer<robot> Robots();
	Estacion iEstacion(const RUR u);				// Le puse la i porque sino hay que aclarar aed2::Estacion para el tipo Estacion string
	Conj<Restriccion>::Iterador Tags(const RUR u);  //ATENCION!: Ver bien si es Restriccion o std::string
	Nat nInfracciones(const RUR u);


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
		ConjRapidoString* tags;
		Estacion estacion;
		Vector<bool> infringe_restriccion;
		Cola<robot>::itCola mi_estacion;
		robot(const RUR rur,
			const Nat infracciones,
			const ConjRapidoString *tags,
			const Estacion estacion)
				: rur(rur),
				infracciones(infracciones),	
				estacion(estacion),
				tags(tags) {};

	};
	VectorPointer<robot> robots;
	Mapa mapa;
	DiccString<ColaDePrioridad<robot>> robotsEnEstacion;
};

#endif