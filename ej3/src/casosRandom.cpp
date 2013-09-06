#include <iostream>
#include <stdlib.h>     /* srand, rand */

using namespace std;

int main()
{
	int cant_casos;
	cin>>cant_casos;
	for(int x=0; x<cant_casos ;x++){
		int n, m;
		n=rand()%10+1;
		m=rand()%10+1;
		cout<< n << " " << m << endl;
		for (int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				int casillero= rand()%100+1; //para q haya casilleros importantes y paredes pero no tantos
				if(casillero>90) casillero=2;
				else if(casillero>60) casillero=0;
				else casillero=1;
				cout<< casillero;
				if(j!=(m-1)) cout<< " ";
			}
			cout<<endl;
		}
	}
	cout <<"#"<<endl;
	return 0;
}
