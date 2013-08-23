#include "../include/problema.h"

using namespace std;

void Problema::mostrarResultado(ostream& os){
	for (int i=0;i<_cursosRes.size();++i){
		os<<_cursosRes[i].second<<" ";
	}
	os<<endl;
}

void Problema::verGraficamente(ostream& os){
	for (int i=0;i<_cursos.size();++i){
		for (int h=1;h<_cursos[i].first.first;++h){
			os<<0;
		}
		for (int j=_cursos[i].first.first;j<=_cursos[i].first.second;++j){
			os<<1;
		}
		os<<endl;
	}
}

void Problema::mostrarCursos(ostream& os){
	if (_cursosRes.size()!=0){
		cout<<"Cursos elegidos:"<<endl;
		for (int i=0;i<_cursosRes.size();++i){
			os<<"("<<_cursosRes[i].first.first<<" "<<_cursosRes[i].first.second<<") ";
		}
		os<<endl;
	}
	else{
		cout<<"Cursos:"<<endl;
		for (int i=0;i<_cursos.size();++i){
			os<<"("<<_cursos[i].first.first<<" "<<_cursos[i].first.second<<") ";
		}
		os<<endl;
	}
}

bool myfunction (pair< pair<int,int>, int > i,pair< pair<int,int>, int > j){
	return (i.first.second < j.first.second);
}

Problema::Problema(istream& is){
	int cantCursos;
	is >> cantCursos;
	pair<int,int> p;
	pair< pair<int,int>, int > ps;
	for(int i=0;i<cantCursos;++i){
		is >> p.first;
		is >> p.second;
		ps = make_pair(p,i+1);
		_cursos.push_back(ps);
	}
}

void Problema::resolver(){
	mostrarCursos(cout);
	cout<<endl;
	verGraficamente(cout);
	cout<<endl;
	sort (_cursos.begin(), _cursos.end(), myfunction); // O(nlog(n)
//	mostrarCursos(cout);
	int final=0;
	for (int i=0;i<_cursos.size();++i){
		if (_cursos[i].first.first > final){
			_cursosRes.push_back(_cursos[i]);
			final = _cursos[i].first.second;
		}
	}
//	mostrarCursos(cout);
	mostrarResultado(cout);
}

