#include "../../tiempo.h"
#include <iostream>
#include "../include/problema.h"

using namespace std;

void mostrarCiclos(ostream& os, int cant_paquetes, unsigned long long int result){
	os << cant_paquetes << " " << result <<endl;
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
	
	int cantRepeticiones= 1000;
	for(int i = 0;i<cantProblemas;i++){
		for(int j=0; j<cantRepeticiones; j++){
			MEDIR_TIEMPO_START(start);
			problemas[i].resolver();
			MEDIR_TIEMPO_STOP(end);
			result+= (end-start);
		}	
			result= result / cantRepeticiones;
			result= result/1000;
			mostrarCiclos(cout, problemas[i].cant_paquetes, result);
	}
    
    return 0;
}
