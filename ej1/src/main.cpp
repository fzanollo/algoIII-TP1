#include <iostream>
#include "../include/problema.h"

using namespace std;

int main()
{
    char c;
    bool termino = false;
    vector<Problema> problemas;
    int cantProblemas = 0;
	bool existeEntrada = cin.good();
	assert(existeEntrada);
			cout << "cantidad de camiones es<< this->cant_camiones" << endl;

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
		cout << "cantidad de camiones es<< this->cant_camiones" << endl;

	for(int i = 0;i<cantProblemas;i++){
		problemas[i].resolver();
	}
    return 0;
}
