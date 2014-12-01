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

public:
	struct robot
	{
	friend class Ciudad;
	public:
		~robot(){
			delete mi_estacion;
		}

		robot& operator=(const robot& other){
			rur = other.rur;
			infracciones = other.infracciones;
			estacion = other.estacion;
			tags = other.tags;
			mi_estacion = other.mi_estacion;

			return *this;
		}


		bool operator>=(const robot& rhs) const{
			return !(rhs < *this);
		}

		bool operator<=(const robot& rhs) const{
			return !(*this < rhs);
		}

		bool operator==(const robot& rhs) const{
			return rur == rhs.rur;
		}

		bool operator>(const robot& rhs) const{
			return rhs < *this;
		}

		bool operator<(const robot& rhs) const{
			if (infracciones < rhs.infracciones){
				return true;
			}
			else if (infracciones == rhs.infracciones){
				return rur > rhs.rur;
			}
		}

	private:
		RUR rur;
		Nat infracciones;
		ConjRapidoString &tags;
		aed2::Estacion estacion;
		Vector<bool> infringe_restriccion;
		ColaDePrioridad<robot>::Iterador* mi_estacion;

		robot(const RUR rur,
				const Nat infracciones, ConjRapidoString &tags,
				const aed2::Estacion estacion)
				: rur(rur),
				  infracciones(infracciones),
				  estacion(estacion),
				  tags(tags),
				  mi_estacion(NULL){};
	} ;

	Ciudad(const Mapa &m);
	~Ciudad();
	void Entrar(ConjRapidoString &ts, const aed2::Estacion &e);
	void Mover(const RUR rur, const aed2::Estacion e);
	void Inspeccion(const aed2::Estacion e);
	RUR ProximoRUR() const;
	Mapa iMapa();
	Vector<robot*>::const_Iterador Robots() const;
	aed2::Estacion Estacion(const RUR u) const;
	Conj<Restriccion>::const_Iterador Tags(const RUR u) const;
	Nat nInfracciones(const RUR u) const;

private:
	Vector<robot*> robots;
	Mapa mapa;
	DiccString<ColaDePrioridad<robot> > robotsEnEstacion;

};

#endif
