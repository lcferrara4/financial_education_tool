#include "stock.h"
#include <string>
using namespace std;

stock::stock(double b, double price, string name){

	beta = b;
	stock_price = price;
	stock_name = name;

}

double stock::get_beta(){

	return beta;
}

double stock::get_price(){

	return stock_price;
}

string stock::get_stockName(){

	return stock_name;
}