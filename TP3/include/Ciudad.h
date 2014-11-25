#ifndef CIUDAD_H
#define CIUDAD_H

#include "../aed2.h"
#include "../include/DiccString.h"
#include "../include/Tipos.h"

using namespace aed2;
using namespace std;

class Ciudad
{
public:

	Ciudad(const Mapa &m);
	~Ciudad();
	void Entrar(const conjRapidoString &ts, const Estacion &e);
	void Mover(const RUR rur, const Estacion e);
	void Inspeccion(const Estacion e);
	Nat ProximoRUR();
	Mapa Mapa();
	VectorPointer::ItVectorPointer<robot> Robots();
	Estacion Estacion(const RUR u);
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
		DiccString<bool> *tags;
		Estacion estacion;
		Vector<bool> infringe_restriccion;
		itCola<robot> mi_estacion;

	};
	VectorPointer<robot> robots;
	Mapa mapa;
	DiccString<ColaDePrioridad<robot>> robotsEnEstacion;
};

#endif