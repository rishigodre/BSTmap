#include <iostream>
#include "my_map.h"
using namespace std;
int main()
{
	my_map<int,int>m;
	for(int i = 0; i < 1e4 ; i++)
		m[i] = i + 1;
	m.insert(1,70);
    m.print();
	cout<<m[1]<<endl;
	return 0;
}

