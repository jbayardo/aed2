// PREGUNTAR: STRING QUE ES? Puedo usar string o son histericas?

#include "DiccString.h"

template <typename T>
DiccString<T>::DiccString(const DiccString &otra) {
	Conj<std::string>::Iterador clv;
	clv = otra.Claves();

	while (clv.HaySiguiente()) {
		this->Definir(clv.Siguiente(), otra.Obtener(clv.Siguiente()));
		clv.Avanzar();
	}
}

template <typename T>
void DiccString<T>::Definir(const std::string k, const T &v) {
	int i = 0;
	Nodo *t = &(this->significados);
	bool nuevo = false;

	while (k.length() > i){
		if (t->continuacion[(int)k[i]] == nullptr) {
			Nodo * tr = new Nodo();
			t->continuacion[(int)k[i]] = tr;
			nuevo = true;
		}

		t = t->continuacion[(int)k[i]];
		i++;
	}

	t->significado = &v;

	if (nuevo) {
		this->claves.AgregarRapido(k);
	}
}

template <typename T>
bool DiccString<T>::Definido(const std::string k) const {
	int i = 0;
	Nodo * t = &(this->significados);

	while ((i < k.length()) && (t->continuacion[(int)k[i]] != nullptr)) {
		t = t->continuacion[(int)k[i]];
		i++;
	}

	return (t->significado != nullptr && i == k.length());
}

template <typename T>
T DiccString<T>::Obtener(const std::string k) const {
	int i = 0;
	Nodo *t = &(this->significados);

	while (i < k.length()) {
		t = t->continuacion[(int)k[i]];
		i++;
	}

	return *(t->significado);
}

template <typename T>
Conj<std::string>::Iterador DiccString<T>::Claves() const {
	return this->claves.CrearIt();
}