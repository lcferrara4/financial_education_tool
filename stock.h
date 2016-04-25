#ifndef STOCK_H
#define STOCK_H
#include <random>
#include <string>
using namespace std;

class stock{

	public:
		stock(double, double, string, default_random_engine &);
		double get_beta();
		double get_price();
		string get_stockName();
		void recalc_price();



	private:
		double beta;
		double stock_price;
		string stock_name;
		default_random_engine& generator;
};

#endif