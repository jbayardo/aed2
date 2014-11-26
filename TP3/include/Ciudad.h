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
		ConjRapidoString *tags;
		Estacion estacion;
		Vector<bool> infringe_restriccion;
		ColaDePrioridad<robot>::Iterador mi_estacion;
		robot(const RUR rur,
			const Nat infracciones,
			ConjRapidoString *tags,
			const Estacion estacion)
				: rur(rur),
				infracciones(infracciones),	
				estacion(estacion),
				tags(tags),
				mi_estacion(ColaDePrioridad<robot>::Iterador(NULL, NULL) ){};	//Tengo un Problema aca que no se como inicializar 
																				//el iterador este, el problema es que se es un iterador a
																				//una cola de prioridad que la tengo que encontrar usando
																				//la ciudad, nose como accederla desde aca, no esta.
																				//Otra opcion seria hacer un iterador nulo pero tampoco se
																				//como hacerlo al menos que haga una cola vacia y despues pedirle el iterador

	};
	Vector<robot*> robots;
	Mapa mapa;
	DiccString<ColaDePrioridad<robot>> robotsEnEstacion;

public:
	Ciudad(const Mapa &m);
	~Ciudad();
	void Entrar(const ConjRapidoString &ts, const Estacion &e);
	void Mover(const RUR rur, const Estacion e);
	void Inspeccion(const Estacion e);
	RUR ProximoRUR();
	Mapa Mapa();
	Vector<robot*>::const_Iterador Robots();
	Estacion iEstacion(const RUR u);				// Le puse la i porque sino hay que aclarar aed2::Estacion para el tipo Estacion string
	Conj<Restriccion>::Iterador Tags(const RUR u);  //ATENCION!: Ver bien si es Restriccion o std::string
	Nat nInfracciones(const RUR u);

};

#endif