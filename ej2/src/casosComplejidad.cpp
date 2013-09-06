#include <iostream>
#include <stdlib.h>     /* srand, rand */

using namespace std;

int main()
{
	int cant_max_cursos;
	cin>>cant_max_cursos;
	
	for (int i=1;i<=cant_max_cursos;++i){
		cout<< i << " ";
		int hasta_dia=20;
		
		for(int j=1; j<=i; j++){
			int inicio= rand() % hasta_dia +1; //elige un comienzo entre [1 ... hasta_dia]
			int fin= rand() % hasta_dia +inicio; //elige un fin entre [inicio ... hasta_dia]
			if(fin>hasta_dia) fin=hasta_dia;
			
			cout<< inicio << " " << fin;
			if(j!=i) cout<< " ";
		}
		cout<< endl;
	}
	cout <<"#"<<endl;
	return 0;
}

