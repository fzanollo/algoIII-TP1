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
	os<<endl;
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

bool Problema::leApuntaUnLaserHorizontal(Casillero& casillero){
//	cout<<"laser horizontal"<<endl;
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

bool Problema::leApuntaUnLaserVertical(Casillero& casillero){
//	cout<<"laser vertical"<<endl;
	for (int i=casillero.first+1; i<_matriz.size();++i){
		if (_matriz[i][casillero.second] == 5 || _matriz[i][casillero.second] == 4) return true;
		if (_matriz[i][casillero.second] == 0)	break;
	}
	for (int i=casillero.first-1; i>=0;--i){
		if (_matriz[i][casillero.second] == 5 || _matriz[i][casillero.second] == 4) return true;
		if (_matriz[i][casillero.second] == 0) return false;
	}
	return false;
}

bool Problema::leApuntanDosLasers(Casillero& casillero){
	if (leApuntaUnLaserVertical(casillero) && leApuntaUnLaserHorizontal(casillero)) return true;
	else return false;
}

bool Problema::puedoColocarSensor(Casillero& casillero, int sensor){ //chequea que no haya un sensor en su camino
//	cout<<"puedoColocar"<<endl;
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
		for (int i=casillero.first+1; i<_matriz[casillero.first].size();++i){
			if (_matriz[i][casillero.second] == 3 || _matriz[i][casillero.second] == 4 || _matriz[i][casillero.second] == 5) return false;
			if (_matriz[i][casillero.second] == 0) break;
		}
		for (int i=casillero.first-1; i>=0;--i){
			if (_matriz[i][casillero.second] == 3 || _matriz[i][casillero.second] == 4 || _matriz[i][casillero.second] == 5) return false;
			if (_matriz[i][casillero.second] == 0) return true;
		}
		return true;
	}
}

bool Problema::hayLaser(int i){
	 return (_matriz[_casilleros[i].first][_casilleros[i].second] == 3 || _matriz[_casilleros[i].first][_casilleros[i].second] == 4 || _matriz[_casilleros[i].first][_casilleros[i].second] == 5);
}

bool Problema::esSolucion(){
	for (int i=0;i<_casilleros.size();++i){
		if (!leApuntaUnLaserHorizontal(_casilleros[i]) && !leApuntaUnLaserVertical(_casilleros[i]) && !hayLaser(i)) return false;
	}
	for (int i=0;i<_casillerosImportantes.size();++i){
		if (!leApuntanDosLasers(_casillerosImportantes[i])) return false;
	}
	return true;
}

void Problema::resolver(){
	cargarCasilleros();
	mostrarCasilleros(cout);
	vector<bool> casillerosUsados(_casilleros.size()); //vector que lleva registro de qué casilleros fueron usados. 0=no fue usado, 1=fue usado.
	int costo=0; //el costo antes de comenzar a colocar sensores es 0.
	_costo=-1;
	backtrack(casillerosUsados,costo);
	_matriz = _matrizRes;
	mostrarMatriz(cout);
}

bool Problema::hayMas(vector<bool>& casillerosUsados){
	for (int i=0;i<casillerosUsados.size();++i){
		if (casillerosUsados[i] == 0) return true;
	}
	return false;
}

bool Problema::hayParedEnElMedio(Casillero& c, Casillero& s){
	if (c.first==s.first){
		if (c.second<s.second){
			for (int j=c.second;j<=s.second;++j){
				if (_matriz[c.first][j]==0) return true;
			}
		}
		else{
			for (int j=s.second;j<=c.second;++j){
				if (_matriz[c.first][j]==0) return true;
			}			
		}
	}
	else{
		if (c.first<s.first){
			for (int i=c.first;i<=s.first;++i){
				if (_matriz[i][c.second]==0) return true;
			}
		}
		else{
			for (int i=s.first;i<=c.first;++i){
				if (_matriz[i][c.second]==0) return true;
			}
		}
	}
	return false;
}

void Problema::marcarCasilleros(Casillero c,int s, vector<bool>& casillerosUsados){
	if(s==3){	
		for (int i=0;i<_casilleros.size();++i){
			if(_casilleros[i].first==c.first && !hayParedEnElMedio(c,_casilleros[i])) casillerosUsados[i] = 1;
		}	
	}
	if(s==4){
		for (int i=0;i<_casilleros.size();++i){
			if( (_casilleros[i].first==c.first || _casilleros[i].second==c.second) && !hayParedEnElMedio(c,_casilleros[i]) ) casillerosUsados[i] = 1;
		}
	}
	if(s==5){
		for(int i=0;i<_casilleros.size();++i){
			if(_casilleros[i].second==c.second && !hayParedEnElMedio(c,_casilleros[i])) casillerosUsados[i] = 1;
		}
	}
}

bool Problema::cumpleHastaElMomento(vector<bool>& casillerosUsados){
	for (int i=0;i<_casillerosImportantes.size();++i){
		if (filaCubierta(_casillerosImportantes[i],casillerosUsados)){
			if (!leApuntaUnLaserHorizontal(_casillerosImportantes[i]))	return false;	 
		}
		if (columnaCubierta(_casillerosImportantes[i],casillerosUsados)){
			if (!leApuntaUnLaserVertical(_casillerosImportantes[i]))	return false;	 
		}
	}
	return true;	
}

bool Problema::filaCubierta(Casillero casillero, vector<bool>& casillerosUsados){
	for (int i=0;i<_casilleros.size();++i){
		if (_casilleros[i].first==casillero.first && !hayParedEnElMedio(_casilleros[i],casillero)){
			if (casillerosUsados[i]!=1) return false;
		}
	}
	return true;
}

bool Problema::columnaCubierta(Casillero casillero, vector<bool>& casillerosUsados){
	for (int i=0;i<_casilleros.size();++i){
		if (_casilleros[i].second==casillero.second && !hayParedEnElMedio(_casilleros[i],casillero)){
			if (casillerosUsados[i]!=1) return false;
		}
	}
	return true;
}

/**
3=sensor bidireccional horizontal
4=sensor cuatridireccional
5=sensor bidireccional vertical
**/

void Problema::backtrack(vector<bool>& casillerosUsados,int costo){
	vector<bool> casillerosUsadosViejo;
	int aux;
	if (!hayMas(casillerosUsados)){
		if (esSolucion() && (costo<_costo || _costo==-1)){
			cout<<costo<<endl;
			_matrizRes=_matriz;
			_costo=costo;
		}
	}
	else{
		if((costo<_costo || _costo==-1) && cumpleHastaElMomento(casillerosUsados)){
			casillerosUsadosViejo = casillerosUsados;
			for (int h=0;h<_casilleros.size();++h){
				if (casillerosUsados[h] == 0){
					for (int i=3;i<=5;++i){
						if (puedoColocarSensor(_casilleros[h], i)){
							aux = _matriz[_casilleros[h].first][_casilleros[h].second];
							_matriz[_casilleros[h].first][_casilleros[h].second] = i;
							marcarCasilleros(_casilleros[h],i,casillerosUsados);
							casillerosUsados[h]=1;
							if (i==3 || i==5) backtrack(casillerosUsados,costo+4000);
							else backtrack(casillerosUsados,costo+6000);
							_matriz[_casilleros[h].first][_casilleros[h].second] = aux;
							casillerosUsados=casillerosUsadosViejo;
						}
					}
					casillerosUsados[h] = 1;
					backtrack(casillerosUsados,costo);
					casillerosUsados[h] = 0;
				}
			}
		}
	}
}
