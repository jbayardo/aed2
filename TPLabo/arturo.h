#ifndef ARTURO_H_
#define ARTURO_H_

#include <iostream>
#include <cassert>
using namespace std;

/*
 * IMPORTANTE!
 * Se puede asumir que el tipo T tiene constructor por copia y operator == y operator <<
 * No se puede asumir que el tipo T tenga operator =
 */
template<typename T>
class Arturo {

  public:

	/*
	 * Crea una mesa redonda nueva sin caballeros.
	 */
	Arturo();

	/*
	 * Una vez copiados, ambos Arturos deben ser independientes,
	 * es decir, cuando se borre uno no debe borrar la otra.
	 */
	Arturo(const Arturo<T>&);

	/*
	 * Acordarse de liberar toda la memoria!
	 */
	~Arturo();

	/*
	* Arturo se sienta siempre primero.
	*
	* PRE: La mesa esta vacía.
	* POST: Arturo está hablando y es el único en la mesa.
	*/
	void sentarArturo(const T& a);

	/*
	 * Agrega un nuevo caballero a la mesa. El nuevo caballero se sentará
	 * a la derecha de Arturo. No se pueden agregar caballeros repetidos.
	 *
	 * PRE: Arturo esta sentado en la mesa y el nuevo caballero c no está sentado aún
	 * POST: El caballero c se sienta a la derecha de Arturo.
	 */
	void incorporarCaballero(const T& c);

	/*
	 * Elimina de la mesa al caballero pasado por parámetro. En caso de borrar al
	 * caballeroActual, pasará a ser el actual que esté sentado a su derecha.
	 * Si se expulsa al caballero interrumpido por Arturo, Arturo sigue hablando
	 * como si nunca hubiera interrumpido, es decir, el próximo es el de la
	 * derecha de Arturo y el anterior es el de la izquierda de Arturo.
	 *
	 * IMPORTANTE: Sólo se puede borrar a Arturo, si es el único sentado en la mesa.
	 *
     * PRE: c puede ser Arturo sólo si la mesa tiene tamaño 1
     * POST: El caballero c no está más sentado en la mesa.
	 */
	void expulsarCaballero(const T& c);

    /*
	 * Devuelve al caballero que está hablando en este momento.
	 *
	 * PRE: Hay caballeros sentados en la mesa.
	 */
	const T& caballeroActual() const;

	/*
	 * Cambia el turno del caballero actual, al de su derecha. Si Arturo
	 * interrumpió, el turno pasa al de la derecha del interrumpido.
	 * El resultado no tiene interrumpido.
	 *
	 * PRE: Hay caballeros sentados en la mesa.
	 */
	void proximoCaballero();

	/*
	 * Cambia el turno del caballero actual, al de su izquierda. Si Arturo
	 * interrumpió, el turno pasa al de la izquierda del interrumpido.
	 * Esta función puede ser llamada varias veces seguidas.
	 * El resultado no tiene interrumpido.
	 *
	 * PRE: Hay caballeros sentados en la mesa.
	 */
	void caballeroAnterior();

	/*
	* Arturo puede elegir que es su turno de hablar en cualquier momento e
	* interrumpir al que está hablando. Arturo termina de hablar por interrupción
	* cuando se pasa al proximoCaballero() o al caballeroAnterior().
	*
	* PRE: Si Arturo está hablando, no se puede interumpir a sí mismo.
	*/
	void hablaArturo();

    /*
	 * Indica si Arturo está sentado en la mesa.
	 */
	bool arturoPresente() const;

	/*
	* Arturo quiere separar un conflicto y por lo tanto cambia su posición y
	* se sienta a la derecha del caballero pasado como parámetro.
	* Tanto como el que está hablando como el interrumpido siguen siendo los mismos.
	* Ejemplos:
	*  cambiarDeLugar(c1) de la mesa: [Arturo(c0), c1, c2] deja la mesa: [Arturo(c0), c2, c1]
	*  cambiarDeLugar(c1) de la mesa: [c1, c2, Arturo(c0)] deja la mesa: [c1, Arturo(c0), c2]
	*  cambiarDeLugar(c2) de la mesa: [c1, c2, Arturo(c0), c3] deja la mesa: [c1, c2, Arturo(c0), c3]
	*
	* PRE: La mesa tiene al menos tamaño 3
	* POST: Arturo está sentado a la derecha de c
	*/
	void cambioDeLugar(const T& c);

	/*
	 * Dice si la mesa tiene o no caballeros sentados.
	 */
	bool esVacia() const;

	/*
	 * Devuelve la cantidad de caballeros en la mesa.
	 */
	int tamanio() const;

	/*
	 * Devuelve true si las mesas son iguales.
	 * Dos mesas son iguales cuando todos sus caballeros son iguales,
	 * están sentados en las mismas posiciones, y además tanto Arturo,
	 * como el que está hablando, como el interrumpido (si hubiera) son iguales.
	 */
	bool operator==(const Arturo<T>&) const;

	/*
	 * Debe mostrar la mesa por el ostream os (y retornar el mismo).
	 * Mesa vacia: []
	 * Mesa con caballero c0 como Arturo: [ARTURO(c0)]
	 * Mesa con 2 caballeros (Arturo está hablando): [ARTURO(c0), c1]
	 * Mesa con 3 caballeros (Arturo está hablando): [ARTURO(c0), c1, c2]
	 * Mesa con 3 caballeros (c1 está hablando): [c1, c2, ARTURO(c0)]
	 * Mesa con 3 caballeros (c1 fue interrumpido): [ARTURO(c0),*c1,c2]
	 */
	ostream& mostrarArturo(ostream& os) const;


  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	Arturo<T>& operator=(const Arturo<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {
		T dato;
		struct Nodo *next;
		struct Nodo *prev;
		Nodo (const T &init) : dato(init) {
			next = this;
			prev = this;
		}
	};

	Nodo *arturo;
	Nodo *talking;
	Nodo *interrupt;
	unsigned long len;
};

template<class T>
ostream& operator<<(ostream& out, const Arturo<T>& a) {
	return a.mostrarArturo(out);
}

template <typename T>
Arturo<T>::Arturo() {
	this->arturo = NULL;
	this->talking = NULL;
	this->interrupt = NULL;
	this->len = 0;
}

template <typename T>
Arturo<T>::Arturo(const Arturo<T> &other) {
	this->arturo = NULL;
	this->talking = NULL;
	this->interrupt = NULL;
	this->len = 0;

	if (other.len > 0) {
		this->sentarArturo(other.arturo->dato);

		int i = 1;
		Nodo *cur = other.arturo->next;

		while (i < other.tamanio()) {
			this->incorporarCaballero(cur->dato);

			if (other.talking == cur) {
				this->talking = this->arturo->next;
			}

			if (other.interrupt == cur) {
				this->interrupt = this->arturo->next;
			}

			i++;
			cur = cur->next;
		}
	}
}

template <typename T>
Arturo<T>::~Arturo() {
	if (this->len > 1) {
		Nodo *cur = this->arturo->next;

		while (cur != this->arturo) {
			Nodo *tmp = cur->next;
			delete(cur);
			cur = tmp;
		}
	}

	if (this->len > 0) {
		delete(this->arturo);
	}
}

template <typename T>
void Arturo<T>::sentarArturo(const T& a) {
	assert(!this->arturoPresente());

	Nodo *nuevo = new Nodo(a);
	this->arturo = nuevo;
	this->talking = nuevo;
	this->interrupt = NULL;
	this->len = 1;
}

template <typename T>
void Arturo<T>::incorporarCaballero(const T& a) {
	assert(this->arturoPresente());

	Nodo *nuevo = new Nodo(a);
	nuevo->prev = this->arturo;
	nuevo->next = this->arturo->next;
	this->arturo->next->prev = nuevo;
	this->arturo->next = nuevo;

	this->len++;
}

template <typename T>
void Arturo<T>::expulsarCaballero(const T& c) {
	assert(!this->esVacia());
	assert((this->arturo->dato == c && this->len == 1) || (this->arturo->dato != c && this->len > 1));

	if (this->arturo->dato == c && this->len == 1) {
		delete(this->arturo);
		this->talking = NULL;
		this->interrupt = NULL;
		this->arturo = NULL;
		this->len--;
	} else {
		Nodo *cur = this->arturo->next;

		while (cur != this->arturo && cur->dato != c) {
			cur = cur->next;
		}

		if (cur->dato == c) {
			if (cur == this->interrupt) {
				this->interrupt = NULL;
			}

			if (cur == this->talking) {
				this->talking = cur->next;
			}

			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			delete(cur);
			this->len--;
		}
	}
}

template <typename T>
const T& Arturo<T>::caballeroActual() const {
	assert(!this->esVacia());
	return this->talking->dato;
}

template <typename T>
void Arturo<T>::proximoCaballero() {
	assert(!this->esVacia());

	if (this->interrupt == NULL) {
		this->talking = this->talking->next;
	} else {
		this->talking = this->interrupt->next;
		this->interrupt = NULL;
	}
}

template <typename T>
void Arturo<T>::caballeroAnterior() {
	assert(!this->esVacia());

	if (this->interrupt == NULL) {
		this->talking = this->talking->prev;
	} else {
		this->talking = this->interrupt->prev;
		this->interrupt = NULL;
	}
}

/*
* Arturo puede elegir que es su turno de hablar en cualquier momento e
* interrumpir al que está hablando. Arturo termina de hablar por interrupción
* cuando se pasa al proximoCaballero() o al caballeroAnterior().
*
* PRE: Si Arturo está hablando, no se puede interumpir a sí mismo.
*/
template <typename T>
void Arturo<T>::hablaArturo() {
	assert(this->talking != this->arturo);

	this->interrupt = this->talking;
	this->talking = this->arturo;
}

/*
 * Indica si Arturo está sentado en la mesa.
 */
template <typename T>
bool Arturo<T>::arturoPresente() const {
	return this->len > 0;
}

/*
* Arturo quiere separar un conflicto y por lo tanto cambia su posición y
* se sienta a la derecha del caballero pasado como parámetro.
* Tanto como el que está hablando como el interrumpido siguen siendo los mismos.
* Ejemplos:
*  cambiarDeLugar(c1) de la mesa: [Arturo(c0), c1, c2] deja la mesa: [Arturo(c0), c2, c1]
*  cambiarDeLugar(c1) de la mesa: [c1, c2, Arturo(c0)] deja la mesa: [c1, Arturo(c0), c2]
*  cambiarDeLugar(c2) de la mesa: [c1, c2, Arturo(c0), c3] deja la mesa: [c1, c2, Arturo(c0), c3]
*
* PRE: La mesa tiene al menos tamaño 3
* POST: Arturo está sentado a la derecha de c
*/
template <typename T>
void Arturo<T>::cambioDeLugar(const T& c) {
	assert(this->len >= 3);
	assert(this->arturo->dato != c);

	Nodo *cur = this->talking;

	while (cur->dato != c) {
		cur = cur->next;
	}

	Nodo *tmp = cur->prev;

	cur->prev->next = this->arturo;
	cur->prev = this->arturo;
	this->arturo->prev->next = this->arturo->next;
	this->arturo->next->prev = this->arturo->prev;
	this->arturo->next = cur;
	this->arturo->prev = tmp;
}

/*
 * Dice si la mesa tiene o no caballeros sentados.
 */
template <typename T>
bool Arturo<T>::esVacia() const {
	return this->len == 0;
}

/*
 * Devuelve la cantidad de caballeros en la mesa.
 */
template <typename T>
int Arturo<T>::tamanio() const {
	return this->len;
}

/*
 * Devuelve true si las mesas son iguales.
 * Dos mesas son iguales cuando todos sus caballeros son iguales,
 * están sentados en las mismas posiciones, y además tanto Arturo,
 * como el que está hablando, como el interrumpido (si hubiera) son iguales.
 */
template <typename T>
bool Arturo<T>::operator==(const Arturo<T> &other) const {
	Nodo *fst = this->arturo;
	Nodo *snd = other.arturo;
	bool output = this->len == other.tamanio();

	output &= this->talking == other.talking;
	output &= this->interrupt == other.interrupt;

	while (fst != NULL && snd != NULL && output) {
		output = fst->dato == snd->dato;
		fst = fst->next;
		snd = snd->next;
	}

	return output;
}

/*
 * Debe mostrar la mesa por el ostream os (y retornar el mismo).
 * Mesa vacia: []
 * Mesa con caballero c0 como Arturo: [ARTURO(c0)]
 * Mesa con 2 caballeros (Arturo está hablando): [ARTURO(c0), c1]
 * Mesa con 3 caballeros (Arturo está hablando): [ARTURO(c0), c1, c2]
 * Mesa con 3 caballeros (c1 está hablando): [c1, c2, ARTURO(c0)]
 * Mesa con 3 caballeros (c1 fue interrumpido): [ARTURO(c0),*c1,c2]
 */
template <typename T>
ostream& Arturo<T>::mostrarArturo(ostream& os) const {
	os << "[";

	if (this->len > 0) {
		int i = this->len;
		Nodo *cur = this->talking;

		while (i > 0) {
			if (cur == this->interrupt) {
				os << "*" << cur->dato;
			} else if (cur == this->arturo) {
				os << "ARTURO(" << cur->dato << ")";
			} else {
				os << cur->dato;
			}

			if (cur->next != this->talking) {
				os << ", ";
			}

			cur = cur->next;
			i--;
		}
	}

	os << "]";
	return os;
}

#endif //ARTURO_H_
