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

void Problema::resolver(){
	mostrarMatriz(cout);
}
