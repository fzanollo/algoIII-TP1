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
		os << "(" << _casilleros[i].first+1 << " " << _casilleros[i].second+1 << ") ";
	}
	cout<<endl;
	cout<<"Casilleros importantes"<<endl;
	for (int i=0;i<_casillerosImportantes.size();++i){
		os << "(" << _casillerosImportantes[i].first+1 << " " << _casillerosImportantes[i].second+1 << ") ";
	}
}

//carga _casilleros todos los casilleros en donde se puede colocar un sensor y en _casillerosImportantes los casilleros importantes.
void Problema::cargarCasilleros(){ 
	for (int i=0;i<_matriz.size();++i){
		for (int j=0;j<_matriz[i].size();++j){
			if (_matriz[i][j] == 1) _casilleros.push_back(make_pair(i,j));
			if (_matriz[i][j] == 2) _casillerosImportantes.push_back(make_pair(i,j));
		}
	}
}

bool Problema::leApuntaUnLaserHorizontal(pair<int,int> casillero){
	cout<<"laser horizontal"<<endl;
	for (int j=casillero.second+1; j<_matriz[casillero.first].size();++j){
		if (_matriz[casillero.first][j] == 3 || _matriz[casillero.first][j] == 4) return true;
		if (_matriz[casillero.first][j] == 0) break;
	}
	for (int j=casillero.second-1; j>=0;--j){
		if (_matriz[casillero.first][j] == 3 || _matriz[casillero.first][j] == 4) return true;
		if (_matriz[casillero.first][j] == 0) return false;
	}
	return false;
}

bool Problema::leApuntaUnLaserVertical(pair<int,int> casillero){
	cout<<"laser vertical"<<endl;
	cout<<"Casillero: "<<"("<<casillero.first<<" "<<casillero.second<<")"<<endl;
	for (int i=casillero.first+1; i<_matriz.size();++i){
		cout <<i<< " ";
		if (_matriz[i][casillero.second] == 5 || _matriz[i][casillero.second] == 4) return true;
		if (_matriz[i][casillero.second] == 0)	break;
	}
	for (int i=casillero.first-1; i>=0;--i){
		cout <<i<< " ";
		if (_matriz[i][casillero.second] == 5 || _matriz[i][casillero.second] == 4) return true;
		if (_matriz[i][casillero.second] == 0) return false;
	}
	return false;
}

bool Problema::leApuntanDosLasers(pair<int,int> casillero){
	cout<<"dos lasers"<<endl;
	if (leApuntaUnLaserVertical(casillero) && leApuntaUnLaserHorizontal(casillero)) return true;
	else return false;
}

bool Problema::puedoColocarSensor(pair<int,int> casillero, int sensor){
	if (sensor==3){
		for (int j=casillero.second+1; j<_matriz[casillero.first].size();++j){
			if (_matriz[casillero.first][j] == 3 || _matriz[casillero.first][j] == 4 || _matriz[casillero.first][j] == 5) return false;
			if (_matriz[casillero.first][j] == 0) break;
		}
		for (int j=casillero.second-1; j>=0;--j){
			if (_matriz[casillero.first][j] == 3 || _matriz[casillero.first][j] == 4 || _matriz[casillero.first][j] == 5) return false;
			if (_matriz[casillero.first][j] == 0) return true;
		}
		return true;
	}

	if (sensor==4){
		return (puedoColocarSensor(casillero,3) && puedoColocarSensor(casillero,5));
	}
	
	if (sensor==5){
		for (int i=casillero.first+1; i<_matriz[i].size();++i){
			if (_matriz[i][casillero.second] == 5 || _matriz[i][casillero.second] == 4 || _matriz[i][casillero.second] == 5) return false;
			if (_matriz[i][casillero.second] == 0) break;
		}
		for (int i=casillero.first-1; i>=0;--i){
			if (_matriz[i][casillero.second] == 5 || _matriz[i][casillero.second] == 4 || _matriz[i][casillero.second] == 5) return false;
			if (_matriz[i][casillero.second] == 0) return true;
		}
		return true;
	}
}


bool Problema::esSolucion(){
	cout <<"es solucion con tamaño: "<<_casilleros.size()<<endl;
	for (int i=0;i<_casilleros.size();++i){
		//if (!leApuntaUnLaserHorizontal(_casilleros[i]) && !leApuntaUnLaserVertical(_casilleros[i]) && _matriz[_casilleros[i].first][_casilleros[i].second] != 3 && _matriz[_casilleros[i].first][_casilleros[i].second] != 4 && _matriz[_casilleros[i].first][_casilleros[i].second] != 5) return false;
	}
	for (int i=0;i<_casillerosImportantes.size();++i){
		//if (!leApuntanDosLasers(_casillerosImportantes[i])) return false;
	}
	return true;
}

void Problema::resolver(){
//	mostrarMatriz(cout);
	cargarCasilleros();
	mostrarCasilleros(cout);
	int costo=0;
	_costo=-1;
	vector< pair<int,int> > casilleros = _casilleros;
	backtrack(casilleros,costo);
}

void Problema::backtrack(vector< pair<int,int> >& casilleros,int costo){
	cout<<"backtrack"<<endl;
	for (int i=0;i<casilleros.size();++i){
		cout << "(" << casilleros[i].first+1 << " " << casilleros[i].second+1 << ") ";
	}
	cout<<endl;
	vector< pair<int,int> > casillerosAux;
	if (casilleros.size()==0){
		if (/*esSolucion() && */(costo<_costo || _costo==-1)){
			_matrizRes=_matriz;
			_costo=costo;
		}
	}
	else{
		if(costo<_costo || _costo==-1){
			casillerosAux = casilleros;
			for (int i=3;i<=5;++i){
				if (puedoColocarSensor(casilleros[0], i)){
					_matriz[casilleros[0].first][casilleros[0].second] = i;
					casilleros.erase(casilleros.begin());
					if (i==3 || i==5) backtrack(casilleros,costo+4000);
					else backtrack(casilleros,costo+6000);
					casilleros = casillerosAux;
				}
				casilleros.erase(casilleros.begin());
				backtrack(casilleros,costo);
				casilleros = casillerosAux;
			}
		}
	}
}
