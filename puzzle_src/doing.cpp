#include <iostream>
#include <cstring>
#include "puzzle.h"
using namespace std;
int main()
{
	//char* sen=new char[100];
	//cout<<"your string should have n^2-1 character :D"<<endl;
	int n;
	cout<<"enter the dimension of the puzzle: ";
	cin>>n;
	puzzle a(n);
	
	return 0;
}
