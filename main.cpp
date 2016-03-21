#include <iostream>
#include <random>
using namespace std;

int main(){
    
	default_random_engine generator;
	normal_distribution<double> distribution(50.0,25.0);

	int p[200]={};

	for(int i=0; i<5000; i++){
		double number = distribution(generator);
		++p[int(number)+50];
	}

	for(int i=0;i<200;i++){
		cout << i-50 << "-" << (i-50+1) << ": ";
		cout << std::string(p[i],'*') << endl;
	}

}
