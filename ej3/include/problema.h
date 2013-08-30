#ifndef PROBLEMA_H
#define PROBLEMA_H

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <cassert>
#include <algorithm>

using namespace std;

typedef pair<int,int> Casillero;

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
	void backtrack(vector<bool>&,int);
	bool esSolucion();
	bool hayMas(vector<bool>&);
	void marcarCasilleros(Casillero,int,vector<bool>&);
	bool hayLaser(int);
	bool cumpleHastaElMomento(vector<bool>&);
	bool filaCubierta(Casillero,vector<bool>&);
	bool columnaCubierta(Casillero,vector<bool>&);
	bool hayParedEnElMedio(Casillero&,Casillero&);
};

#endif
