#include "Ciudad.h"

Ciudad::Ciudad(const Mapa &m){
	Conj<aed2::Estacion>::const_Iterador it = m.Estaciones();

	while (it.HaySiguiente()){
		robotsEnEstacion.Definir(it.Siguiente(), ColaDePrioridad<robot>());
		it.Avanzar();
	}
	mapa = m;
}

Ciudad::~Ciudad(){
	for (int i = 0; i < robots.Longitud(); ++i) {
		delete robots[i];
	}
}

void Ciudad::Entrar(ConjRapidoString* ts, const aed2::Estacion &e){
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


	assert(robotsEnEstacion.Definido(e));

	robot* rob = new robot(ProximoRUR(), 0, ts, e);
	rob->mi_estacion = robotsEnEstacion.Obtener(e).Encolar(*rob);

	Vector<Restriccion_*>::const_Iterador it = this->mapa.Sendas();

	while (it.HaySiguiente()){
		rob->infringe_restriccion.AgregarAtras(!it.Siguiente()->Verifica(ts));
		it.Avanzar();
	}

	this->robots.AgregarAtras(rob);
}

void Ciudad::Mover(const RUR rur, const aed2::Estacion e){
	/*
	iMover(in rur : nat, in e : estacion, in/out c : city)
		var rob : puntero(robot) ← c.robots[rur]

		Borrar(Obtener(c.robotsEnEstacion, rob→estacion), rob→mi_estacion)

		var infringe : nat ← rob→infracciones
		var id_senda : nat ← idSenda(c.mapa, rob→estacion, e)

		if rob→infringe_restriccion[id_senda] then
			infringe++
		end if

		rob→infracciones ← infringe
		rob→estacion ← e
		rob→mi_estacion ← Encolar(obtener(c.robotsEnEstacion,  e), *rob)
	end function
	 */

	robot* rob = robots[rur];
	robotsEnEstacion.Obtener(rob->estacion).Desencolar(rob->mi_estacion);

	Nat id_senda = mapa.idSenda(rob->estacion, e);

	if (rob->infringe_restriccion[id_senda]){
		rob->infracciones++;
	}

	rob->estacion = e;
	delete rob->mi_estacion;
	rob->mi_estacion = NULL;

	rob->mi_estacion = robotsEnEstacion.Obtener(e).Encolar(*rob);
}


void Ciudad::Inspeccion(const aed2::Estacion e){
	/*
	iInspeccion(in e : estacion, in/out c : city)
		var cola : colaPrioridad(robot) ← Obtener(c.robotsEnEstacion, e)

		if tamaño(cola) > 0 then
			var rob : robot ← Desencolar(cola)
			c.robots[rob.rur] ← NULL
		end if
	end function
	 */
	ColaDePrioridad<robot>& cola = robotsEnEstacion.Obtener(e);

	if (cola.Tamano() > 0){
		robot rob = cola.Desencolar();
		delete robots[rob.rur];
		robots[rob.rur] = NULL;
	}

}

RUR Ciudad::ProximoRUR() const{
	return robots.Longitud();
}

Mapa Ciudad::iMapa(){ //referencia constante?
	return mapa;
}

Ciudad::const_Iterador Ciudad::Robots(){
	return const_Iterador(robots);
}

aed2::Estacion Ciudad::Estacion(const RUR u) const{
	return robots[u]->estacion;
}

Conj<Restriccion>::const_Iterador Ciudad::Tags(const RUR u) const{
	return robots[u]->tags->CrearIt();
}

Nat Ciudad::nInfracciones(const RUR u) const{
	return robots[u]->infracciones;
}
