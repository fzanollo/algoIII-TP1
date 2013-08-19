#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main () {
	int myints[] = {10,20,30,5,15};
	std::vector<int> v(myints,myints+5);

	std::make_heap (v.begin(),v.end());
	std::cout << "initial max heap   : " << v.front() << '\n';
	



return 0;
}

