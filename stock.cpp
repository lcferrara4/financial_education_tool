#include "stock.h"
#include <string>
using namespace std;

stock::stock(int b, int price, string name){

	beta = b;
	stock_price = price;
	stock_name = name;

}

int stock::get_beta(){

	return beta;
}

int stock::get_price(){

	return stock_price;
}

string stock::get_stockName(){

	return stock_name;
}