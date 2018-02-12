#ifndef CBUFFER_H 
#define CBUFFER_H

#include <algorithm>
#include <iostream>
#include <ostream>
#include <cstddef> // ptrdiff_t
#include <iterator> // categorie degli iterator
#include <cassert>

/**
	Classe che implementa un buffer circolare di elementi di tipo T.
	Il buffer ha una capacità fissa, decisa a costruzione. L'inserimento
	accoda gli elementi finché il buffer non è pieno. Una volta
	riempito, i nuovi dati vengono scritti partendo dall'inizio del
	buffer e sovrascrivendo i vecchi.
	
	@brief Buffer circolare
	
	@param T tipo del dato
*/
template <typename T>
class cbuffer {

	// Definzione del tipo corrispondente a _size
	typedef unsigned int size_type;
	
	/**
		Struttura di supporto interna che implementa un nodo della lista.

		@brief Nodo della lista
	*/
	struct nodo {
		T value; ///< Dato inserito nella lista 
		nodo *next; ///< puntatore al nodo successivo della lista

		/**
			Costruttore di default
		*/
		nodo() : next(0) {}

		/**
			Costruttore secondario che inizializza il nodo
			
			@param v valore del dato
			@param n puntatore al nodo successivo
		*/
		nodo(const T &v, nodo *n=0) 
			: value(v), next(n) {}

	};

	nodo *_head; ///< puntatore alla testa della lista
 
	size_type _size; ///< capacità della lista

public:
	
	/**
		Costruttore di default
	*/
	cbuffer() : _head(0), _size(5) {}
	
	/**
		@brief Costruttore secondario

		Costruttore secondario. Permette di istanziare un cbuffer
		con una data dimensione.

		@param v dimensione del cbuffer da istanziare 
	*/
	cbuffer(size_type v) : _head(0), _size(v) {}
	
	/**
		@brief Costruttore secondario
		
		Costruttore secondario che costruisce un cbuffer a partire da una
		sequenza generica di dati identificata da due iteratori.

		@param size capacità del cbuffer
		@param begin iteratore di inizio della sequenza
		@param end iteratore di fine della sequenza

		@throw eccezione di allocazione di memoria
	*/
	template <typename IterT>
	cbuffer(size_type size, IterT begin, IterT end) : _head(0), _size(size) {
		try {		
			for(; begin!=end; ++begin) {
				insert(static_cast<T>(*begin));		
			}
		}
		catch(...) {
			clear();
			throw;
		}
	}
	
	/**
		@brief Costruttore di copia

		Operatore di assegnamento. Permette la copia tra cbuffer.
		
		@param other buffer da copiare
		@throw eccezione di allocazione di memoria
	*/
	cbuffer(const cbuffer &other) 
		: _head(0), _size(0) {
		
		_size = other._size;
		const nodo *tmp = other._head;	
		try {
			while (tmp!=0) {
				insert(tmp->value);
				tmp = tmp->next;
			}
		}
		catch(...) {
			clear();
			throw;
		}		
	}  

	/**
		@brief Operatore di assegnamento
		
		Operatore di assegnamento. Permette la copia tra cbuffer.
		
		@param other buffer da copiare
		@return reference a this

		@throw eccezione di allocazione di memoria
	*/
	cbuffer& operator=(const cbuffer &other) {
		if (this != &other) {
			cbuffer tmp(other);
			std::swap(tmp._head, _head);
			std::swap(tmp._size, _size);
		}
		return *this;
	}
	
	/**
		Distruttore
	*/
	~cbuffer() {
		clear();
	}
	
	/**
		@brief Clear

		Clear. Rimuove la memoria allocata da cbuffer.
	*/
	void clear() {
		nodo *tmp = _head;

		while (tmp!=0) {
			nodo *n = tmp->next;
			delete tmp;
			tmp = n;
		}	
		_head = 0;
	}
	
	/**
		@brief Inserimento
		
		Inserimento. Inserisce un elemento nel buffer circolare. Se la
		quantità di elementi inseriti è uguale a _size allora la testa viene 
		cancellata e sostituita con l'elemento successivo, mentre value viene
		aggiunto alla coda.

		@param value valore da inserire

		@throw eccezione di allocazione di memoria
	*/
	void insert(const T &value) {
		nodo *n = new nodo(value);

		if (_head == 0) {
			_head = n;
			return;
		}

		nodo *current = _head, *prev=_head;

		int s = 1;
		while (current!=0) {
			prev = current;
			current = current->next;
			s++;	
		} 
		
		if(s>_size) {
			nodo *tmp = _head->next;
			delete _head;
			_head = tmp;
		}		

		n->next = current;
		prev->next = n;		

	}
	
	/**
		Rimuove testa cbuffer
		
		@throw eccezione di allocazione di memoria
	*/
	void del_head() {
		nodo *tmp = _head->next;
		delete _head;
		_head = tmp;
	}
	
	/**
		Ritorna capacità del cbuffer

		@return capacità del cbuffer
	*/
	size_type get_size() const {
		return _size;
	}
	
	/**
		Ritorna il numero di elementi del cbuffer

		@return Ritorna il numero di elementi del cbuffer
	*/
	size_type get_items() const {
		int s = 0;
		nodo *current = _head;
		while (current!=0) {
			current = current->next;
			s++;				
		}
		return s;
	}		
	
	/**
		@brief Accesso ai dati in lettura/scrittura
		
		Accesso ai dati in lettura/scrittura (stile C++ con operatore)

		@pre E' necessario che index < get_items()
		
		@param index Indice della cella dell'array da scrivere
		
		@return Il valore della cella index-esima
	*/
	T &operator[](size_type index) {
		assert(index < get_items() );
		
		nodo *current = _head;
		
		int s = 0;
		while (current!=0 && s<index) {
			current = current->next;
			s++;	
		} 
		return current->value;
	}

	/**
		@brief Accesso ai dati in lettura

		Accesso ai dati in lettura (stile C++ con operatore)

		@pre E' necessario che index < size
		
		@param index Indice della cella dell'array da leggere
		
		@return Il valore della cella index-esima
	*/
	const T &operator[](size_type index) const {
		assert(index < get_items());
		
		nodo *current = _head;
		
		int s = 0;
		while (current!=0 && s<index) {
			current = current->next;
			s++;	
		} 
		return current->value;
	}

	class const_iterator; // forward declaration

	/**
		Iteratore di cbuffer
	*/
	class iterator {
		nodo *ptr;

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef T*                        pointer;
		typedef T&                        reference;
	
		iterator() : ptr(0) {
		}
		
		iterator(const iterator &other) 
			: ptr(other.ptr) {
		}

		iterator& operator=(const iterator &other) {
			ptr = other.ptr;
			return *this;
		}
	
		~iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return ptr->value;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &(ptr->value);
		}

		// Operatore di iterazione post-incremento
		iterator operator++(int) {
			iterator tmp(*this);
			ptr = ptr->next;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		iterator& operator++() {
			ptr = ptr->next;
			return *this;
		}

		// Uguaglianza
		bool operator==(const iterator &other) const {
			return ptr == other.ptr;
		}

		// Diversità
		bool operator!=(const iterator &other) const {
			return ptr != other.ptr;
		}
		
		// Solo se serve anche const_iterator aggiungere le seguenti definizioni
		friend class const_iterator;
		
		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return ptr == other.ptr;
		}

		// Diversità
		bool operator!=(const const_iterator &other) const {
			return ptr != other.ptr;
		}

	private:
		//Dati membro

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class cbuffer;

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		iterator(nodo *p) : ptr(p) { 
		}
		
	}; // classe iterator

	// Ritorna l'iteratore all'inizio della sequenza dati
	iterator begin() {
		return iterator(_head);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	iterator end() {
		return iterator(0);
	}


	class const_iterator {
		const nodo *n;	

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
		const_iterator() : n(0) {
		}
		
		const_iterator(const const_iterator &other) 
			: n(other.n) {
		}

		const_iterator& operator=(const const_iterator &other) {
			n = other.n;
			return *this;
		}
		
		~const_iterator() {
			n = 0;
		}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return n->value;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &(n->value);
		}
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			n = n->next;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
			n = n->next;
			return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return n == other.n;
		}
		
		// Diversità
		bool operator!=(const const_iterator &other) const {
			return n != other.n; 
		}
		
		// Solo se serve anche iterator aggiungere le seguenti definizioni
		friend class iterator;
		
		// Uguaglianza
		bool operator==(const iterator &other) const {
			return n == other.ptr;
		}
		
		// Diversità
		bool operator!=(const iterator &other) const {
			return n != other.ptr;
		}
	
		// Assegnamento di un iterator ad un const_iterator
		const_iterator& operator=(const iterator &other) {
			n = other.ptr;
			return *this;
		}

	private:
		//Dati membro

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class cbuffer; 

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const nodo *nn) : n(nn) { 
		}	
		
	}; // classe const_iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(_head);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(0);
	}

}; // cbuffer

/**
	@brief Stream
	
	Ridefinizione dell'operatore di stream per la stampa di cbuffer

	@param os oggetto stream di output
	@param ol cbuffer da stampare

	@return reference allo stream di output
*/
template <typename T>
std::ostream &operator<<(std::ostream &os, 
	const cbuffer<T> &ol) {
	
	typename cbuffer<T>::const_iterator i, ie;

	for(i = ol.begin(), ie = ol.end(); i!=ie; ++i)
		os << *i << std::endl;
	
	return os;
}

/**
	Funtore per il confronto tra interi 
*/
struct isDec {
	bool operator()(int a) const {
		return a>9;
	}
	
};

/**
	Funtore per valutare se grandezza di a è 4
*/
struct is_long_four {
	bool operator()(std::string a) const {
		if(a.size() == 4) {return true;}
		return false;
	}
	
};

/**
	struct punto
*/
struct point {
	int x; ///< coordinata x del punto
	int y; ///< coordinata y del punto
};

/**
	Funtore per il confronto di coordinate di un punto. 
	Ritorna true se p.x > p.y.
*/
struct is_x_greater_y {
	bool operator()(const point &p) const {
		return (p.x>p.y);
	} 
};


/**
	@brief Valuta il predicato P su tutti gli elementi del buffer cb
	
	Funzione globale che dati un cbuffer cb generico e un predicato unario 
	generico P, per ogni elemento cb[i] contenuto nel cbuffer, stampa a console:
	"[i]: true" quando P(cb[i]) è vero			oppure
	"[i]: false" quando P(cb[i]) è falso.
	
	@param T tipo di dato
	@param Predicate funtore di valutazione cb[i]
	@param P predicato unario
	@param cb cbuffer	
*/
template <typename T, typename Predicate>
void evaluate_if(const cbuffer<T> &cb, const Predicate P) {

	for (int i = 0; i < cb.get_items(); i++) {
		if(P(cb[i])){
			std::cout << "[" << i << "]: true" << std::endl;
		} else {
			std::cout << "[" << i << "]: false" << std::endl;
		}
	
	}
	
}

#endif