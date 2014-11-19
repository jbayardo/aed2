#ifndef DICCSTRING_H
#define DICCSTRING_H

#include "../aed2.h"

using namespace aed2;


	template <typename T>
	class DiccString{
	public:
		DiccString();
		DiccString(const DiccString& otra);
		~DiccString();
		void Definir(const string k, const T& v);
		bool Definido(const string k) const;
		T Obtener(const string k) const;
		Conj<string>::Iterador Claves() const;
	private:
		class trie{
		public:
			Arreglo<trie*> continuacion;
			T* significado;
		};
		Conj<string> claves;
		trie significados;
	};

#endif