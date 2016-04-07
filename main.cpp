#include <iostream>
#include <random>
#include "stock.h"
using namespace std;

int main(){

	cout << "Here" << endl;

	int array[90];

	stock test(1.0, 20.0, "test");

	

    
	/*default_random_engine generator;
	normal_distribution<double> distribution(50.0,25.0);

	int p[200]={};

	for(int i=0; i<5000; i++){
		double number = distribution(generator);
		++p[int(number)+50];
	}

	for(int i=0;i<200;i++){
		cout << i-50 << "-" << (i-50+1) << ": ";
		cout << std::string(p[i],'*') << endl;
	}*/

}
