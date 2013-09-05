#include <iostream>
#include <stdlib.h>     /* srand, rand */

using namespace std;

int main()
{
	int limite;
	cin>>limite;
	for (int i=1;i<=limite;++i){
		cout << 1 << " " << i <<endl;
		for (int j=1;j<=i;++j){
			if (j==i) cout <<1;
			else cout <<1<<" ";
		}
		cout <<endl;
	}
	cout <<"#"<<endl;
	return 0;
}

