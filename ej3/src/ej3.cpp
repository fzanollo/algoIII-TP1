#include "../include/problema.h"

Problema::Problema(istream& is){
	int n; int m;
	is >> n;
	is >> m;
	vector<int> vec (m);
	for (int i=0;i<n;++i){
		for (int j=0;j<m;++j){
			is >> vec[j];
		}
		_matriz.push_back(vec);
	}
}

void Problema::mostrarMatriz(ostream& os){
	for (int i=0;i<_matriz.size();++i){
		for (int j=0;j<_matriz[i].size();++j){
			os << _matriz[i][j] <<" ";
		}
		os<<endl;
	}
}

void Problema::mostrarCasilleros(ostream& os){
	cout<<"Casilleros"<<endl;
	for (int i=0;i<_casilleros.size();++i){
		os << "(" << _casilleros[i]._coord.first+1 << " " << _casilleros[i]._coord.second+1 << ") ";
	}
	cout<<endl;
	cout<<"Casilleros importantes"<<endl;
	for (int i=0;i<_casillerosImportantes.size();++i){
		os << "(" << _casillerosImportantes[i]._coord.first+1 << " " << _casillerosImportantes[i]._coord.second+1 << ") ";
	}
	os<<endl;
}

//carga _casilleros todos los casilleros en donde se puede colocar un sensor y en _casillerosImportantes los casilleros importantes.
void Problema::cargarCasilleros(){ 
	for (int i=0;i<_matriz.size();++i){
		for (int j=0;j<_matriz[i].size();++j){
			if (_matriz[i][j] == 1) _casilleros.push_back(Casillero(make_pair(i,j),0));
			if (_matriz[i][j] == 2) _casillerosImportantes.push_back(Casillero(make_pair(i,j),0));
		}
	}
}

bool Problema::leApuntaUnLaserHorizontal(Casillero& casillero){
//	cout<<"laser horizontal"<<endl;
	for (int j=casillero._coord.second+1; j<_matriz[casillero._coord.first].size();++j){
		if (_matriz[casillero._coord.first][j] == 3 || _matriz[casillero._coord.first][j] == 4) return true;
		if (_matriz[casillero._coord.first][j] == 0) break;
	}
	for (int j=casillero._coord.second-1; j>=0;--j){
		if (_matriz[casillero._coord.first][j] == 3 || _matriz[casillero._coord.first][j] == 4) return true;
		if (_matriz[casillero._coord.first][j] == 0) return false;
	}
	return false;
}

bool Problema::leApuntaUnLaserVertical(Casillero& casillero){
//	cout<<"laser vertical"<<endl;
//	cout<<"Casillero: "<<"("<<casillero._coord.first<<" "<<casillero._coord.second<<")"<<endl;
	for (int i=casillero._coord.first+1; i<_matriz.size();++i){
//		cout <<i<< " ";
		if (_matriz[i][casillero._coord.second] == 5 || _matriz[i][casillero._coord.second] == 4) return true;
		if (_matriz[i][casillero._coord.second] == 0)	break;
	}
	for (int i=casillero._coord.first-1; i>=0;--i){
//		cout <<i<< " ";
		if (_matriz[i][casillero._coord.second] == 5 || _matriz[i][casillero._coord.second] == 4) return true;
		if (_matriz[i][casillero._coord.second] == 0) return false;
	}
	return false;
}

bool Problema::leApuntanDosLasers(Casillero& casillero){
//	cout<<"dos lasers"<<endl;
	if (leApuntaUnLaserVertical(casillero) && leApuntaUnLaserHorizontal(casillero)) return true;
	else return false;
}

bool Problema::puedoColocarSensor(Casillero& casillero, int sensor){
	if (sensor==3){
		for (int j=casillero._coord.second+1; j<_matriz[casillero._coord.first].size();++j){
			if (_matriz[casillero._coord.first][j] == 3 || _matriz[casillero._coord.first][j] == 4 || _matriz[casillero._coord.first][j] == 5) return false;
			if (_matriz[casillero._coord.first][j] == 0) break;
		}
		for (int j=casillero._coord.second-1; j>=0;--j){
			if (_matriz[casillero._coord.first][j] == 3 || _matriz[casillero._coord.first][j] == 4 || _matriz[casillero._coord.first][j] == 5) return false;
			if (_matriz[casillero._coord.first][j] == 0) return true;
		}
		return true;
	}

	if (sensor==4){
		return (puedoColocarSensor(casillero,3) && puedoColocarSensor(casillero,5));
	}
	
	if (sensor==5){
		for (int i=casillero._coord.first+1; i<_matriz[i].size();++i){
			if (_matriz[i][casillero._coord.second] == 5 || _matriz[i][casillero._coord.second] == 4 || _matriz[i][casillero._coord.second] == 5) return false;
			if (_matriz[i][casillero._coord.second] == 0) break;
		}
		for (int i=casillero._coord.first-1; i>=0;--i){
			if (_matriz[i][casillero._coord.second] == 5 || _matriz[i][casillero._coord.second] == 4 || _matriz[i][casillero._coord.second] == 5) return false;
			if (_matriz[i][casillero._coord.second] == 0) return true;
		}
		return true;
	}
}


bool Problema::esSolucion(){
//	cout <<"es solucion con tamaño: "<<_casilleros.size()<<endl;
	for (int i=0;i<_casilleros.size();++i){
		if (!leApuntaUnLaserHorizontal(_casilleros[i]) && !leApuntaUnLaserVertical(_casilleros[i]) && _matriz[_casilleros[i]._coord.first][_casilleros[i]._coord.second] != 3 && _matriz[_casilleros[i]._coord.first][_casilleros[i]._coord.second] != 4 && _matriz[_casilleros[i]._coord.first][_casilleros[i]._coord.second] != 5) return false;
	}
	for (int i=0;i<_casillerosImportantes.size();++i){
		if (!leApuntanDosLasers(_casillerosImportantes[i])) return false;
	}
	return true;
}

void Problema::resolver(){
//	mostrarMatriz(cout);
	cargarCasilleros();
	mostrarCasilleros(cout);
	int costo=0;
	_costo=-1;
	vector< Casillero > casilleros = _casilleros;
	backtrack(casilleros,costo);
//	_matriz = _matrizRes;
//	mostrarMatriz(cout);
}

bool Problema::hayMas(vector<Casillero>& casilleros){
	for (int i=0;i<casilleros.size();++i){
		if (casilleros[i]._usado == 0) return true;
	}
	return false;
}

void Problema::backtrack(vector<Casillero>& casilleros,int costo){
	cout<<"backtrack"<<endl;
	/*for (int i=0;i<casilleros.size();++i){
		cout << "(" << casilleros[i]._coord.first+1 << " " << casilleros[i]._coord.second+1 << ") ";
	}
	cout<<endl;*/
	vector< Casillero > casillerosAux;
	if (!hayMas(casilleros)){
		if (esSolucion() && (costo<_costo || _costo==-1)){
			_matrizRes=_matriz;
			_costo=costo;
		}
	}
	else{
		if(costo<_costo || _costo==-1){
			casillerosAux = casilleros;
			for (int h=0;h<casilleros.size() && casilleros[h]._usado!=1 ;++h){
				for (int i=3;i<=5;++i){
					if (puedoColocarSensor(casilleros[0], i)){
						_matriz[casilleros[h]._coord.first][casilleros[h]._coord.second] = i;
						casilleros[h]._usado = 1;
						if (i==3 || i==5) backtrack(casilleros,costo+4000);
						else backtrack(casilleros,costo+6000);
						casilleros = casillerosAux;
					}
					casilleros[h]._usado = 1;
					backtrack(casilleros,costo);
					casilleros = casillerosAux;
				}
			}
		}
	}
}
