// PREGUNTAR: STRING QUE ES? Puedo usar string o son histericas?

#include "../include/DiccString.h"

template <typename T>
DiccString<T>::DiccString(){}

template <typename T>
DiccString<T>::DiccString(const DiccString& otra){
	Conj<string>::Iterador clv;
	clv = otra.Claves();
	while clv.HaySiguiente(){
		this->Definir(clv.Siguiente(), otra.Obtener(clv.Siguiente()));
		clv.Avanzar();
	}
}

template <typename T>
DiccString<T>::~DiccString(){}

template <typename T>
void DiccString<T>::Definir(const string k, const T& v){
	int i = 0;
	trie* t = &(this->significados);
	bool nuevo = false;
	while (k.length() > i){
		if (t->continuacion[(int)k[i]] == nullptr) {
			trie* tr = new trie;
			t->continuacion[(int)k[i]] = tr;
			nuevo = true;
		}
		t = t->continuacion[(int)k[i]];
		i++;
	}
	t->significado = &v;
	if nuevo{
		this->claves.AgregarRapido(k);
	}
}

template <typename T>
bool DiccString<T>::Definido(const string k) const{
	int i = 0;
	trie* t = &(this->significados);
	while ((i < k.length()) && (t->continuacion[(int)k[i]] != nullptr)){
		t = t->continuacion[(int)k[i]];
		i++;
	}
	return (t->significado != nullptr && i == k.length());
}

template <typename T>
T DiccString<T>::Obtener(const string k) const{
	int i = 0;
	trie* t = &(this->significados);
	while (i < k.length()){
		t = t->continuacion[(int)k[i]];
		i++;
	}
	return *(t->significado)
}

template <typename T>
Conj<string>::Iterador DiccString<T>::Claves() const{
	this.claves.CrearIt();
}