#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include "stock.h"
using namespace std;

int main(){
	//instatniate
	default_random_engine generator(time(0));
	vector<stock> stocks;
    
	for(int j=0;j<60;j++){
		stock s (10.0,50.0,"Alumni Hall", generator);
		stocks.push_back(s);
	}

	for(int i=0;i<60;i++){
		stocks[i].recalc_price();
		cout << stocks[i].get_price() << endl;
		cout << "Stock number" << i << endl;
	}
}
