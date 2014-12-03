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

	class const_Iterador;
	friend class const_Iterador;
	struct robot
	{
	friend class Ciudad;
	public:
		~robot(){
			if (mi_estacion != NULL){
				delete mi_estacion;
			}
		}

		robot(){};

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

		RUR rur_() const{
			return rur;
		}

		Nat infracciones_() const{
			return infracciones;
		}

		const ConjRapidoString& tags_() const{
			return *tags;
		}

	private:
		RUR rur;
		Nat infracciones;
		ConjRapidoString* tags;
		aed2::Estacion estacion;
		Vector<bool> infringe_restriccion;
		ColaDePrioridad<robot>::Iterador* mi_estacion;

		robot(const RUR rur,
				const Nat infracciones,
				ConjRapidoString* tags,
				const aed2::Estacion estacion)
				: rur(rur),
				  infracciones(infracciones),
				  estacion(estacion),
				  tags(tags),
				  mi_estacion(NULL){};
	} ;

	Ciudad(const Mapa *m);
	~Ciudad();
	void Entrar(ConjRapidoString* ts, const aed2::Estacion &e);
	void Mover(const RUR rur, const aed2::Estacion e);
	void Inspeccion(const aed2::Estacion e);
	RUR ProximoRUR() const;
	const Mapa* iMapa() const;
	Ciudad::const_Iterador Robots();
	aed2::Estacion Estacion(const RUR u) const;
	Conj<Restriccion>::const_Iterador Tags(const RUR u) const;
	Nat nInfracciones(const RUR u) const;

	class const_Iterador
	{
	public:

		const_Iterador(const const_Iterador& o): actual(o.actual), len(o.len), vec(o.vec) {};

		const_Iterador& operator = (const const_Iterador& otra){
			this->actual = otra.actual;
			this->len = otra.len;
			this->vec = otra.vec;
		}

		bool HaySiguiente()const{
			Nat next = actual;

			while (next < len && vec[next] == NULL){
				next++;
			}

			return next < len;
		}

		const robot* Siguiente()const{
			return vec[actual];
		}

		void Avanzar(){
			Nat next = actual + 1;

			while (next < len && vec[next] == NULL){
				next++;
			}
			actual = next;
		}

	private:
		Nat actual;
		Nat len;
		Vector<robot*>& vec;

		const_Iterador(Vector<robot*>& r):vec(r){
			actual = 0;
			len = r.Longitud();
		};

		friend class Ciudad;
	};

private:
	Vector<robot*> robots;
	const Mapa* mapa;
	DiccString<ColaDePrioridad<robot> > robotsEnEstacion;

};

#endif
