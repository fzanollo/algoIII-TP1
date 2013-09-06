#include <iostream>
#include <stdlib.h>     /* srand, rand */

using namespace std;

int main()
{
	int cant_casos;
	cin>>cant_casos;
	for(int x=0; x<cant_casos ;x++){
		int n, m;
		cin>>n;
		cin>>m;
		cout<< n << " " << m << endl;
		for (int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cout<< (i+j)%2;
				if(j!=(m-1)) cout<< " ";
			}
			cout<<endl;
		}
	}
	cout <<"#"<<endl;
	return 0;
}

