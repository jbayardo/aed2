#include "../include/DiccString.h"


//class trie{
//public:
//	Arreglo<trie*> continuacion;
//	T* significado;
//};
//Conj<string> claves;
//trie significados;

template <typename T>
DiccString<T>::DiccString(){
	this.significados.continuacion.Arreglo(255);
}

template <typename T>
DiccString<T>::DiccString(const DiccString& otra){
}

template <typename T>
DiccString<T>::~DiccString(){

}

template <typename T>
void DiccString<T>::Definir(const string k, const T& v){

}

template <typename T>
bool DiccString<T>::Definido(const string k) const{
	return true;
}

template <typename T>
T DiccString<T>::Obtener(const string k) const{
	T tmp = new T;
	return tmp;
}

template <typename T>
Conj<string>::Iterador DiccString<T>::Claves() const{
	this.claves.CrearIt();
}