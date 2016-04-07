#define STOCK_H
#ifndef STOCK_H

#include string


class stock{

	public:
		stock(int, int, string);
		int get_bete();
		int get_price();
		string get_stockName();



	private:
		int beta;
		int stock_price;
		string stock_name;
};


stock::stock(int b, int price, string name){

	beta = b;
	stock_price = price;
	stock_name = name;

}

#endif