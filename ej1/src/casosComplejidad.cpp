#include <iostream>
#include <stdlib.h>     /* srand, rand */

using namespace std;

int main()
{
	int cantidad_max_paquetes;
	cin>>cantidad_max_paquetes;
	
	for (int i=1;i<=cantidad_max_paquetes;++i){
		int peso_limite = rand() % 100 + 1;
		cout << peso_limite << " ";
		cout << i << " ";
		
		for (int j=1; j<=i; j++){
			int peso_individual = rand() % peso_limite + 1;
			cout<< peso_individual;
			if(j!=i) cout<< " ";
		}
		
		cout <<endl;
	}
	cout <<"#"<<endl;
	return 0;
}

