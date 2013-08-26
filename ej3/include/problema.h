#ifndef PROBLEMA_H
#define PROBLEMA_H

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <cassert>
#include <algorithm>

using namespace std;

struct Casillero{
	Casillero(pair<int,int> coord,int usado){
		_coord = coord;
		_usado = usado;
	}
	pair<int,int> _coord;
	bool _usado;
};

struct Problema{

	vector< vector<int> > _matriz;
	vector< Casillero > _casilleros;
	vector< Casillero > _casillerosImportantes;
	vector< vector<int> > _matrizRes;
	int _costo;
	
	void resolver();
	Problema (istream&);
	void insertarSensor(int);
	bool leApuntaUnLaserHorizontal(Casillero&);
	bool leApuntaUnLaserVertical(Casillero&);
	void mostrarCasilleros(ostream&);
	void cargarCasilleros();
	void mostrarMatriz(ostream&);
	bool leApuntanDosLasers(Casillero&);
	bool puedoColocarSensor(Casillero&, int);
	void backtrack(vector<Casillero>&,int);
	bool esSolucion();
	bool hayMas(vector<Casillero>&);
};

#endif
