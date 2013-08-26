#ifndef PROBLEMA_H
#define PROBLEMA_H

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <cassert>
#include <algorithm>

using namespace std;

struct Problema{

	vector< vector<int> > _matriz;
	vector< pair<int,int> > _casilleros;
	vector< pair<int,int> > _casillerosImportantes;
	vector< vector<int> > _matrizRes;
	int _costo;
	
	void resolver();
	Problema (istream&);
	void insertarSensor(int);
	bool leApuntaUnLaserHorizontal(pair<int,int>);
	bool leApuntaUnLaserVertical(pair<int,int>);
	void mostrarCasilleros(ostream&);
	void cargarCasilleros();
	void mostrarMatriz(ostream&);
	bool leApuntanDosLasers(pair<int,int>);
	bool puedoColocarSensor(pair<int,int>, int);
	void backtrack(vector< pair<int,int> >&,int);
	bool esSolucion();
};

#endif
