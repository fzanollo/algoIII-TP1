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

void Problema::cargarCasilleros(){
	for (int i=0;i<_matriz.size();++i){
		for (int j=0;j<_matriz[i].size();++j){
			if (_matriz[i][j] == 1) _casilleros.push_back(make_pair(i,j));
			if (_matriz[i][j] == 2) _casillerosImportantes.push_back(make_pair(i,j));
		}
	}
}

bool Problema::leApuntaUnLaserHorizontal(pair<int,int> casillero){
	for (int j=casillero.second; j<_matriz[casillero.first].size();++j){
		if (_matriz[casillero.first][j] == 3 || _matriz[casillero.first][j] == 4) return true;
		if (_matriz[casillero.first][j] == 0){
			for (int j=casillero.second; j>=0;--j){
				if (_matriz[casillero.first][j] == 3 || _matriz[casillero.first][j] == 4) return true;
				if (_matriz[casillero.first][j] == 0) return false;
			}
			return false;
		}
	}
}

bool Problema::leApuntaUnLaserVertical(pair<int,int> casillero){
	for (int i=casillero.first; i<_matriz[i].size();++i){
		if (_matriz[i][casillero.second] == 5 || _matriz[i][casillero.second] == 4) return true;
		if (_matriz[i][casillero.second] == 0){
			for (int i=casillero.first; i>=0;--i){
				if (_matriz[i][casillero.second] == 5 || _matriz[i][casillero.second] == 4) return true;
				if (_matriz[i][casillero.second] == 0) return false;
			}
			return false;
		}
	}
}

bool Problema::leApuntanDosLasers(pair<int,int> casillero){
	if (leApuntaUnLaserVertical(casillero) && leApuntaUnLaserHorizontal(casillero)) return true;
	else return false;
}

void Problema::resolver(){
	mostrarMatriz(cout);
	cargarCasilleros();
	mostrarCasilleros(cout);
	_matriz[1][2] = 5;
	cout<<endl;
	cout<<leApuntaUnLaserVertical(make_pair(2,2))<<endl;
}
