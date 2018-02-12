#include <iostream>
#include <cassert>
#include "cbuffer.h"

void test_metodi_fondamentali() {
	cbuffer<int> ol;
	cbuffer<int> lo(28);
	
	ol.insert(1);
	ol.insert(1);
	ol.insert(3);
	ol.insert(5);
	ol.insert(7);
	ol.insert(11);
	
	std::cout<<"******** Test metodi fondamentali <int> ********"<<std::endl;
	std::cout << std::endl;
	
	std::cout << "Creazione di cbuffer ol e lo" << std::endl;
	std::cout << std::endl;
	
	std::cout << "ol.get_size(): " << ol.get_size() << std::endl;
	std::cout << "ol.get_items(): " << ol.get_items() << std::endl;
	std::cout << std::endl;
	
	std::cout << "lo.get_size(): " << lo.get_size() << std::endl;
	std::cout << "lo.get_items(): " << lo.get_items() << std::endl;
	std::cout << std::endl;
	
	std::cout << "Insertimento valori in ol: 1, 1, 3, 5, 7, 11" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Stampa dei valori ol:" <<std::endl<< ol << std::endl;
	
	cbuffer<int> ol2(ol);
	std::cout << "Costruttore di copia ol2(ol)" <<std::endl;
	std::cout << std::endl;

	std::cout << "ol2.get_size(): " << ol2.get_size() << std::endl;
	std::cout << "ol2.get_items(): " << ol2.get_items() << std::endl;
	std::cout << std::endl;

	std::cout << "Stampa dei valori ol2:" << std::endl << ol2 << std::endl;

	lo = ol2;	
	std::cout << "Assegnameto lo = ol2" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Stampa dei valori lo:" << std::endl << lo << std::endl;
		
	std::cout << "lo.get_size(): " << lo.get_size() << std::endl;
	std::cout << "lo.get_items(): " << lo.get_items() << std::endl;
	std::cout << std::endl;
	
}

void test_custom() {
	struct rub {
		std::string nome;
		std::string cognome;
		
	} a, b, c, d, e, f;
		
	cbuffer<rub> ol;
	cbuffer<rub> lo(28);
	
	a.nome = "Umberto"; a.cognome = "Cocca";
	b.nome = "Albert"; b.cognome = "Einstein";
	c.nome = "Galileo"; c.cognome = "Galilei";
	d.nome = "Isaac"; d.cognome = "Newton";
	e.nome = "Enrico"; e.cognome = "Fermi";
	f.nome = "Niels"; f.cognome = "Bohr";
	
	ol.insert(a);
	ol.insert(b);
	ol.insert(c);
	ol.insert(d);
	ol.insert(e);
	ol.insert(f);
	

	std::cout<<"******** Test metodi fondamentali <custom> ********"<<std::endl;
	std::cout << std::endl;
	
	std::cout << "Creazione di cbuffer ol e lo" << std::endl;
	std::cout << std::endl;
	
	std::cout << "ol.get_size(): " << ol.get_size() << std::endl;
	std::cout << "ol.get_items(): " << ol.get_items() << std::endl;
	std::cout << std::endl;
	
	std::cout << "lo.get_size(): " << lo.get_size() << std::endl;
	std::cout << "lo.get_items(): " << lo.get_items() << std::endl;
	std::cout << std::endl;
	
	std::cout << "Stampa dei valori ol:" << std::endl;
	std::cout << ol[0].nome << " " << ol[0].cognome << std::endl;
	std::cout << ol[1].nome << " " << ol[1].cognome << std::endl;
	std::cout << ol[2].nome << " " << ol[2].cognome << std::endl;
	std::cout << ol[3].nome << " " << ol[3].cognome << std::endl;
	std::cout << ol[4].nome << " " << ol[4].cognome << std::endl;
	std::cout << std::endl;
	
}

void test_uso() {	
	int a[5] = {13, 17, 19, 23, 29};
	
	cbuffer<int> ol(4,a,a+4);
	std::cout<<"******** Test uso ********"<<std::endl;
	std::cout << std::endl;
	
	std::cout << "Stampa di ol costruito con gli iteratori:" 
		<< std::endl << ol << std::endl;

	std::cout << "ol.get_size(): " << ol.get_size() << std::endl;
	std::cout << "ol.get_items(): " << ol.get_items() << std::endl;
	std::cout << std::endl;
	
	assert(ol.get_size() == 4);
	
}

void test_cbuffer_int(cbuffer<int> &other) {
	std::cout << "******** Test cbuffer interi ********" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Insertimento valori in other: 31, 37, 41, 42" << std::endl;
	other.insert(31);
	other.insert(37);
	other.insert(41);
	other.insert(42);

	std::cout << "other.get_size(): " << other.get_size() << std::endl;
	std::cout << "other.get_items(): " << other.get_items() << std::endl;
	std::cout << std::endl;
	
	std::cout<<"Stampa con iteratore costante:"<<std::endl;
	cbuffer<int>::const_iterator i,ie;
	for(i=other.begin(),ie=other.end(); i!=ie; ++i)
		std::cout<<*i<<std::endl;
	std::cout << std::endl;
	
	std::cout << "Stampa con iteratore non costante:" << std::endl;
	cbuffer<int>::iterator ci,cie;	
	for(ci=other.begin(),cie=other.end(); ci!=cie; ++ci)
		std::cout<<*ci<<std::endl;
	std::cout << std::endl;
	
	other.clear();
	std::cout << "Dopo il clear(): " <<std::endl;
	std::cout << "other.get_size(): " << other.get_size() << std::endl;
	std::cout << "other.get_items(): " << other.get_items() << std::endl;
	std::cout << std::endl;
	
	other.insert(43);
	
}

void test_const_cbuffer_int(const cbuffer<int> &other) {
	std::cout<<"******** Test cbuffer costante di interi ********"<<std::endl;
	std::cout << std::endl;
	
	// insert non e' chiamabile su un oggetto const
	
	std::cout << "other.get_size(): " << other.get_size() << std::endl;
	std::cout << "other.get_items(): " << other.get_items() << std::endl;
	std::cout << std::endl;

	std::cout<<"Stampa con iteratore costante:"<<std::endl;
	cbuffer<int>::const_iterator i,ie;
	for(i=other.begin(),ie=other.end(); i!=ie; ++i)
		std::cout<<*i<<std::endl;
	std::cout<<" "<<std::endl;
	
	// clear non e' chiamabile su un oggetto const
	
}

void test_funtori() {
	std::cout<<"******** Test evaluate_if ********"<<std::endl;
	std::cout << std::endl;
	
	cbuffer<int> ol;

	ol.insert(47);
	ol.insert(53);
	ol.insert(59);
	ol.insert(61);
	ol.insert(0);

	std::cout << "Creazione di cbuffer ol" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Insertimento valori in ol: 47, 53, 59, 61, 0" << std::endl;
	std::cout << std::endl;

	std::cout << "ol.get_size(): " << ol.get_size() << std::endl;
	std::cout << "ol.get_items(): " << ol.get_items() << std::endl;
	std::cout << std::endl;
	
	ol.del_head();
	
	std::cout << "Cancelliamo la testa" << std::endl;
	std::cout << std::endl;
	
	std::cout << "ol.get_size(): " << ol.get_size() << std::endl;
	std::cout << "ol.get_items(): " << ol.get_items() << std::endl;
	std::cout << std::endl;
	
	std::cout << "Stampa dei valori ol:" <<std::endl<< ol << std::endl;
	
	isDec trig;
	std::cout << "Evaluate if numero > 9 in ol[i]:" << std::endl;
	evaluate_if(ol,trig);
	std::cout << std::endl;
	
	cbuffer<std::string> li;
	li.insert("p");
	li.insert("in");
	li.insert("apple");
	li.insert("pen?");
	
	std::cout << "Stampa dei valori li:" <<std::endl<< li << std::endl;
	
	is_long_four hope;
	std::cout << "Evaluate if stringhe lunghe 4 caratteri:" << std::endl;
	evaluate_if(li,hope);
	std::cout << std::endl;
	
	point a;
	point b;
	
	a.x = 1; a.y=0;
	b.x = 0; b.y=1;
	
	cbuffer<point> lu;
	lu.insert(a);
	lu.insert(b);
	
	is_x_greater_y pl;
	std::cout << "Evaluate if punto.x > punto.y" << std::endl;
	evaluate_if(lu,pl);
	std::cout << std::endl;
	
	std::cout << "*ol.begin() & operatore cbuffer[1]:" 
		<< std::endl << *ol.begin() << " " << ol[1] << std::endl;
	std::cout << std::endl;

} 	

int main() {
	test_metodi_fondamentali();
	
	test_custom();
	
	test_uso();

	cbuffer<int> oli;
	test_cbuffer_int(oli);
	test_const_cbuffer_int(oli);
		
	test_funtori();
	
	return 0;
	
}