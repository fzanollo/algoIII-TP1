#ifndef PROBLEMA_H
#define PROBLEMA_H

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <queue>

using namespace std;

struct camion {
	int peso;
	int indice;
	camion(int peso, int indice){
		this->peso=peso;
		this->indice=indice;
	}
	camion(const camion& c){
		this->peso=c.peso;
		this->indice=c.indice;
	}
};

class comparar{
	public:
	bool operator() (const camion& c1, const camion& c2){
	return (c1.peso > c2.peso);		//aca hay que ver si va al reves
	}
};

struct Problema{
	
	int peso_limite;
	int cant_paquetes;
	vector< int > paquetes;
	vector< int > camiones;
	int cant_camiones;
	priority_queue< camion, vector<camion>, comparar> heap_camiones;
	void resolver();
	Problema (istream&);
	void mostrarResultado(ostream&);
	

	
};

#endif
