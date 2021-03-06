#include "../include/problema.h"

using namespace std;

Problema::Problema(istream& is){
	is >> this->peso_limite;
	int n;
	is >> n;
	this->cant_paquetes= n;
	int p;
	for(int i=0;i<n;++i){
		is >> p;
		this->paquetes.push_back(p);
	}
}

void Problema:: resolver(){
	int k=-1;  //k es el indice de los camiones
	
	for(int i =0; i< cant_paquetes;i++){
		if(k>=0 && heap_camiones.top().peso + paquetes[i] <= peso_limite){ //si le entra
				camion auxc(heap_camiones.top()); //tomo el camion mas liviano del heap
				heap_camiones.pop(); //saco el mas liviano
				auxc.peso = auxc.peso + paquetes[i];
				heap_camiones.push(auxc);  //hay q sacarnos la duda de si se puede acceder al elemento una vez q lo metimos en el heap
				camiones[auxc.indice] = auxc.peso;
		}
		else{
				k++; //aumentamos el idice de camiones
				camion c(paquetes[i],k);
				heap_camiones.push(c);			//pusheamos el camion al heap
				camiones.push_back(c.peso);		//pusheamos el peso del paquete a la lista de pesos de camiones
		}
	}
	this->cant_camiones=k+1;
	mostrarResultado(cout);
	
}



void Problema::mostrarResultado(ostream& os){
	os<< this->cant_camiones;
	cout << " ";
	for (int i=0;i< this->cant_camiones; ++i){
		os<< this->camiones[i] <<" ";
	}
	os<<endl;
}
