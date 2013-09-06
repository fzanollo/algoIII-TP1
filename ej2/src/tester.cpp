#include "../../tiempo.h"
#include <iostream>
#include "../include/problema.h"

using namespace std;

void mostrarCiclos(ostream& os, int cant_cursos, unsigned long long int result){
	os << cant_cursos << " " << result <<endl;
}

int main()
{
	char c;
    bool termino = false;
    vector<Problema> problemas;
    int cantProblemas = 0;
	bool existeEntrada = cin.good();
	assert(existeEntrada);
	while(!termino){
        problemas.push_back(Problema(cin));
        cantProblemas++;
        cin >> c;
        if (c =='#'){
            termino = true;
        }else{
            cin.putback(c);
        }
	}
	unsigned long long int start=0, end=0, result=0;
	
	int cant_repeticiones= 1000;
	for(int i = 0;i<cantProblemas;i++){
		for(int j=0; j<cant_repeticiones; j++){
			MEDIR_TIEMPO_START(start);
			problemas[i].resolver();
			MEDIR_TIEMPO_STOP(end);
			result+= (end-start);	
		}
		result= result / cant_repeticiones;
		result= result / 1000;
		mostrarCiclos(cout,problemas[i]._cursos.size(),result);
	}
    return 0;
}
