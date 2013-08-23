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

	vector< pair< pair<int,int>, int > > _cursos;
	vector< pair< pair<int,int>, int > > _cursosRes;
	void resolver();
	Problema (istream&);
	void mostrarResultado (ostream&);
	void mostrarCursos (ostream&);
	void verGraficamente (ostream&);
};

#endif
