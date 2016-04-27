#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <fstream>

#include "stock.h"
#include "User.h"
#include "SDL.h"
using namespace std;

double makeSP(vector<stock>);

int main( int argc, char* args[]  ){
		
        SDL mySDL;
        mySDL.handleEvents();

	//instantiate
	default_random_engine generator(time(0));
	vector<stock> stocks;
	vector<vector<double> > graphs;
	//User myUser(mySDL.getIncome(), mySDL.getState(), mySDL.getStatus()); 
	vector<string> stock_Names;

	string in;
	string response, buy_stock;
	double SP, stock_buy =0, stock_sell =0, total =0, number_Stock = 0;

	// read in the stock names
	string stock_names_file = "stock_names.txt";
	ifstream myfile;
	myfile.open(stock_names_file.c_str());
	if (myfile.is_open()){
		while(getline (myfile,in)){
			stock_Names.push_back(in);
		}
		myfile.close();
	}

	// generates the stocks 
	int change =0;
	for(int j=0;j<60;j++){
		if(change < 20){
			stock s (7.5,50.0, stock_Names[j],"High Volatility", generator);
			stocks.push_back(s);
		} else if(change < 40){
			stock s (5.0,50.0, stock_Names[j], "Medium Volatility", generator);
			stocks.push_back(s);
		} else if(change < 60){
			stock s (2.5,50.0, stock_Names[j], "Low Volatility" ,generator);
			stocks.push_back(s);
		}
		change++;
	}
/*
	// displays the stocks
	for(int i=0;i<60;i++){
		stocks[i].recalc_price();
		cout << stocks[i].get_stockName() << " " <<stocks[i].get_price() << ' ' <<endl;
	}
*/

	// Make S&P 500
	SP = makeSP(stocks);
//	cout << "S&P 500 " << SP << endl;

	
	//usleep(10000);

	cout << "Do you want to buy a stock?" << endl << "Y for yes, N for no." << endl;
	cin >> response;

	if (response == "y" || response == "Y"){
		cout << "What stock would you like to buy? It must match exactly." << endl;
		cin >> buy_stock;
	}else if( response == "n" || response == "N"){

	}else{
		cout << "Sorry that is not a correct response" << endl;
	}
	for(int i=0;i<60;i++){
		// cout << stock_Names[i] << " " << buy_stock << endl;
		if(stock_Names[i] == buy_stock){
			stock_buy = stocks[i].get_price();
		}
	}

	vector<double> temp;

	//graph stuff
	for (int i = 0; i < 60; ++i)
	{
		stocks[i].recalc_price();
		temp.push_back( stocks[i].get_price() );
		graphs.push_back(temp);
		temp.clear();
	}
	
	total = stock_buy - stock_sell; //amount of money made in stocks
    stock_buy = stock_buy * number_Stock; //amount of money currently in market

}

double makeSP(vector<stock> s){
	double total = 0;
	for(int i=0;i<60;i++){
		total += s[i].get_price();
	}
	return total = total / 60;
}
