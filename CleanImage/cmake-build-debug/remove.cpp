#include<iostream>
#include<string>
#include<limits>
using namespace std;

int main()
{
	double temp = numeric_limits<double>::max();
	cout << "max value is " << temp << endl;
}
