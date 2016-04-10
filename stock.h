#ifndef STOCK_H
#define STOCK_H

#include <string>
using namespace std;

class stock{

	public:
		stock(double, double, string);
		double get_beta();
		double get_price();
		string get_stockName();



	private:
		double beta;
		double stock_price;
		string stock_name;
};

#endif